// POKEY RevA: Arduino-ESP32 example. Not compiled or tested on hardware.
// ESP32-DevKitC V4 / WROOM-32E. Write-only bus, external PHI2 clock.
#include <Arduino.h>
#include <initializer_list>
#include <WiFi.h>
#include <WebServer.h>
#include <SPI.h>

constexpr int PIN_SCK=18, PIN_MOSI=23, PIN_LATCH=27;
constexpr int PIN_REQ=32, PIN_CLR_N=26, PIN_BUS_EN=25;
const char *AP_NAME="POKEY-Control";
const char *AP_PASS="Pokey-Setup-1234"; // Change to a personal password before use.
WebServer server(80);
uint8_t shadow[16]={0};

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
void pokeyWrite(uint8_t address,uint8_t value) {
  // Call from one task only. No concurrent writes or ISR access.
  digitalWrite(PIN_REQ,LOW);
  delayMicroseconds(10);
  latchWord(0x10 | (address & 15),value); // CS1 High, address A0..A3
  delayMicroseconds(2);                  // data/address stable before REQ
  digitalWrite(PIN_REQ,HIGH);
  delayMicroseconds(10);                 // hardware produces exactly one pulse
  digitalWrite(PIN_REQ,LOW);
  delayMicroseconds(10);                 // fully clear the request pipeline
  shadow[address & 15]=value;
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
    "<title>POKEY</title><style>body{font:18px system-ui;max-width:720px;margin:32px auto;padding:16px}"
    "fieldset{margin:16px 0}input,select,button{font:inherit;margin:6px;width:110px}</style>"
    "<h1>POKEY</h1><p>Mono on both channels. Set the volume to minimum before PLAY.</p>"
    "<p>PHI2 = 1 MHz. Frequency values are divider settings, not hertz.</p>");
  for(int ch=0;ch<4;ch++) {
    h+="<form action='/channel' method='post'><fieldset><legend>Channel "+String(ch+1)+"</legend>";
    h+="<input type='hidden' name='ch' value='"+String(ch)+"'>Divider ";
    h+="<input name='div' type='number' min='0' max='255' value='"+String(shadow[ch*2])+"'><br>";
    h+="Volume <input name='vol' type='number' min='0' max='15' value='"+String(shadow[ch*2+1]&15)+"'><br>";
    h+="Sound code <input name='dist' type='number' min='0' max='7' value='"+String(shadow[ch*2+1]>>5)+"'> (5 = pure tone)<br>";
    h+="<button>Apply</button></fieldset></form>";
  }
  h+=F("<form action='/silence' method='post'><button>All off</button></form>"
       "<p>Display shows transmitted values; this bus has no readback channel.</p></html>");
  server.send(200,"text/html; charset=utf-8",h);
}
void setup() {
  // Set output latches Low before enabling GPIO outputs.
  for(int p:{PIN_BUS_EN,PIN_REQ,PIN_LATCH,PIN_CLR_N}) {
    digitalWrite(p,LOW); pinMode(p,OUTPUT);
  }
  SPI.begin(PIN_SCK,-1,PIN_MOSI,-1);
  delay(100); // X1 may require up to 30 ms to start
  digitalWrite(PIN_CLR_N,HIGH); // release the Johnson clock and request pipeline
  delay(50);
  latchWord(0,0); // defined state, with CS1 still Low
  digitalWrite(PIN_BUS_EN,HIGH); // Q1 pulls OE_N Low on both 595 devices
  delayMicroseconds(10);
  pokeyWrite(15,0); // temporarily reset through SKCTL
  for(int a=0;a<=8;a++) pokeyWrite(a,0);
  pokeyWrite(14,0); // IRQEN disabled
  pokeyWrite(15,3); // SKCTL: enable generators
  pokeyWrite(9,0);  // STIMER
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_NAME,AP_PASS);
  server.on("/",HTTP_GET,home);
  server.on("/channel",HTTP_POST,[](){
    int ch,d,v,n;
    if(!numberArg("ch",0,3,ch)||!numberArg("div",0,255,d)||
       !numberArg("vol",0,15,v)||!numberArg("dist",0,7,n)) {
      server.send(400,"text/plain","Invalid value"); return;
    }
    pokeyWrite(2*ch,d); pokeyWrite(2*ch+1,(n<<5)|v); pokeyWrite(9,0);
    server.sendHeader("Location","/"); server.send(303);
  });
  server.on("/silence",HTTP_POST,[](){
    for(int ch=0;ch<4;ch++) pokeyWrite(ch*2+1,0);
    server.sendHeader("Location","/"); server.send(303);
  });
  server.begin();
}
void loop(){ server.handleClient(); delay(1); }
