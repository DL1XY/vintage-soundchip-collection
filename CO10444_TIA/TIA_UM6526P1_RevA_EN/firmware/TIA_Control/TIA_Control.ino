// UM6526P1 PAL TIA RevA: Arduino-ESP32 example. Not compiled or tested on hardware.
// ESP32-DevKitC V4 / WROOM-32E. Write-only bus, external PHI2 clock.
#include <Arduino.h>
#include <initializer_list>
#include <WiFi.h>
#include <WebServer.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SI5351.h>

constexpr int PIN_SCK=18, PIN_MOSI=23, PIN_LATCH=27;
constexpr int PIN_REQ=32, PIN_CLR_N=26, PIN_BUS_EN=25;
const char *AP_NAME="TIA-Control";
const char *AP_PASS="Tia-Setup-1234"; // Change to a personal password before use.
WebServer server(80);
uint8_t shadow[32]={0};
constexpr bool TIA_NTSC=false; // PAL UM6526P1: false, JP1 unpopulated.
constexpr uint32_t MASTER_HZ=TIA_NTSC?3579545UL:3546894UL;
Adafruit_SI5351 clockgen;

void latchWord(uint8_t control, uint8_t value) {
  // Arduino SPI.transfer() is synchronous; allow a guard interval before latching.
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(control); // shifts into U3, the second register
  SPI.transfer(value);   // remains in U2, the data register
  SPI.endTransaction();
  delayMicroseconds(1);
  digitalWrite(PIN_LATCH,HIGH);
  delayMicroseconds(1);
  digitalWrite(PIN_LATCH,LOW);
}
void tiaWrite(uint8_t address,uint8_t value) {
  // Call from one task only. No concurrent writes or ISR access.
  digitalWrite(PIN_REQ,LOW);
  delayMicroseconds(20);
  latchWord(0x20 | (address & 31),value); // CS1 High, address A0..A4
  delayMicroseconds(2);                  // data/address stable before REQ
  digitalWrite(PIN_REQ,HIGH);
  delayMicroseconds(20);                 // hardware produces exactly one pulse
  digitalWrite(PIN_REQ,LOW);
  delayMicroseconds(20);                 // fully clear the request pipeline
  shadow[address & 31]=value;
}
bool numberArg(const String &key,int lo,int hi,int &result) {
  if(!server.hasArg(key)) return false;
  String s=server.arg(key);
  if(s.length()==0 || s.length()>3) return false;
  int n=0;
  for(size_t i=0;i<s.length();++i) {
    if(s[i]<'0' || s[i]>'9') return false;
    n=n*10+s[i]-'0';
  }
  if(n<lo || n>hi) return false;
  result=n; return true;
}
void home() {
  String h=F("<!doctype html><html lang='en'><meta charset='utf-8'>"
    "<meta name='viewport' content='width=device-width,initial-scale=1'>"
    "<title>TIA</title><style>body{font:18px system-ui;max-width:720px;margin:32px auto;padding:16px}"
    "fieldset{margin:16px 0}input,select,button{font:inherit;margin:6px;width:110px}</style>"
    "<h1>TIA</h1><p>Mono on both channels. Set the volume to minimum before PLAY.</p>"
    "<p>TIA has two voices. Frequency values are 5-bit dividers, not hertz.</p>");
  for(int ch=0;ch<2;ch++) {
    h+="<form action='/channel' method='post'><fieldset><legend>Channel "+String(ch+1)+"</legend>";
    h+="<input type='hidden' name='ch' value='"+String(ch)+"'>Divider ";
    h+="<input name='div' type='number' min='0' max='31' value='"+String(shadow[0x17+ch])+"'><br>";
    h+="Volume <input name='vol' type='number' min='0' max='15' value='"+String(shadow[0x19+ch]&15)+"'><br>";
    h+="Sound code <input name='dist' type='number' min='0' max='15' value='"+String(shadow[0x15+ch]&15)+"'> (4 or 5 = pure tone)<br>";
    h+="<button>Apply</button></fieldset></form>";
  }
  h+=F("<form action='/silence' method='post'><button>All off</button></form>"
       "<p>Display shows transmitted values; this bus has no readback channel.</p></html>");
  server.send(200,"text/html; charset=utf-8",h);
}
uint32_t gcd32(uint32_t a,uint32_t b) {
  while(b){uint32_t n=a%b;a=b;b=n;} return a;
}
bool startMasterClock() {
  if(clockgen.begin(&Wire)!=ERROR_NONE) return false;
  if(clockgen.enableOutputs(false)!=ERROR_NONE) return false;
  if(clockgen.setupPLLInt(SI5351_PLL_A,36)!=ERROR_NONE) return false;
  const uint32_t pll=900000000UL; // 25-MHz module crystal x36
  uint32_t a=pll/MASTER_HZ, rem=pll%MASTER_HZ;
  uint32_t g=gcd32(rem,MASTER_HZ), b=rem/g, c=MASTER_HZ/g;
  if(c>1048575UL || a<4 || a>900) return false;
  if(clockgen.setupMultisynth(0,SI5351_PLL_A,a,b,c)!=ERROR_NONE) return false;
  if(clockgen.setupRdiv(0,SI5351_R_DIV_1)!=ERROR_NONE) return false;
  if(clockgen.resetPLL(SI5351_PLL_A)!=ERROR_NONE) return false;
  delay(100);
  uint8_t status=0;
  if(clockgen.readDeviceStatus(&status)!=ERROR_NONE || (status&0xA0)) return false;
  return clockgen.enableOutputs(true)==ERROR_NONE;
}
void setup() {
  // Set output latches Low before enabling GPIO outputs.
  for(int p:{PIN_BUS_EN,PIN_REQ,PIN_LATCH,PIN_CLR_N}) {
    digitalWrite(p,LOW); pinMode(p,OUTPUT);
  }
  SPI.begin(PIN_SCK,-1,PIN_MOSI,-1);
  // M3 VIN is supplied from DevKit 3V3, not from the 5-V rail.
  Wire.begin(21,22);
  Wire.setClock(100000);
  if(!startMasterClock()) {
    // Leave BUS_EN Low and the request pipeline reset on a clock/I2C fault.
    while(true) delay(1000);
  }
  delay(100);
  digitalWrite(PIN_CLR_N,HIGH); // release request synchronizer only
  delay(50);
  latchWord(0,0); // CS1 remains Low until defined latch contents are enabled
  digitalWrite(PIN_BUS_EN,HIGH);
  delayMicroseconds(20);
  // Only the six level-controlled audio registers are written. No strobes.
  tiaWrite(0x19,0); tiaWrite(0x1A,0);
  tiaWrite(0x15,4); tiaWrite(0x16,4);
  tiaWrite(0x17,0); tiaWrite(0x18,0);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_NAME,AP_PASS);
  server.on("/",HTTP_GET,home);
  server.on("/channel",HTTP_POST,[](){
    int ch,d,v,n;
    if(!numberArg("ch",0,1,ch)||!numberArg("div",0,31,d)||
       !numberArg("vol",0,15,v)||!numberArg("dist",0,15,n)) {
      server.send(400,"text/plain","Invalid value"); return;
    }
    tiaWrite(0x19+ch,0); tiaWrite(0x15+ch,n); tiaWrite(0x17+ch,d); tiaWrite(0x19+ch,v);
    server.sendHeader("Location","/"); server.send(303);
  });
  server.on("/silence",HTTP_POST,[](){
    for(int ch=0;ch<2;ch++) tiaWrite(0x19+ch,0);
    server.sendHeader("Location","/"); server.send(303);
  });
  server.begin();
}
void loop(){ server.handleClient(); delay(1); }
