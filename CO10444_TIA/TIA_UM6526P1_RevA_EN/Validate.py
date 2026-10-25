from pathlib import Path
import json,re,itertools,math,csv
from fractions import Fraction
R=Path(__file__).resolve().parent.parent
P=Path(__file__).resolve().parent
D=json.loads((P/'design.json').read_text(encoding='utf8')); parts={x['ref']:x for x in D['parts']}
checks=[]
def check(name,v):
    assert v,name
    checks.append(name)
def net(r,n):return next(x['net'] for x in parts[r]['pins'] if x['n']==str(n))
expected={1:'GND',2:None,3:None,4:'PHI0',5:None,6:None,7:None,8:'PAL_AUX8',9:None,10:'DEL_UNUSED',11:'TIA_OSC',12:'TIA12',13:'AUD_RAW',14:'D0',15:'D1',16:'D2',17:'D3',18:'D4',19:'D5',20:'5V',21:'GND',22:'GND',23:'CS1',24:'CS0_N',25:'GND',26:'PHI2',27:'GND',28:'A4',29:'A3',30:'A2',31:'A1',32:'A0',33:'D7',34:'D6',35:'I5',36:'I4',37:'I3',38:'I2',39:'I1',40:'I0'}
check('PAL-family socket: all 40 contacts match independent expected map',all(net('U1',n)==v for n,v in expected.items()))
check('Supply changed to TIA pins20/1',net('U1',20)=='5V' and net('U1',1)=='GND')
check('PAL audio is pin13; pin12 isolated through an explicitly DNP link',net('U1',13)=='AUD_RAW' and net('U1',12)=='TIA12' and 'DNP PAL' in parts['JP1']['value'])
check('CS2/CS3/RW grounded; A5 grounded; CS1 controlled',all(net('U1',n)=='GND' for n in [21,22,25,27]) and net('U1',23)=='CS1')
check('U3.QE=A4 and QF=CS1',net('U3',4)=='A4' and net('U3',5)=='CS1')
check('TIA master and bus clock are distinct nets with correct socket contacts',net('U1',11)=='TIA_OSC' and net('U1',26)=='PHI2' and net('U1',4)=='PHI0')
check('Clock module VIN and I2C are in ESP32 3.3-V domain',net('M3','VIN')=='3V3_ESP' and net('M2','J2.1')=='3V3_ESP')
check('Audio pull-up is 1k, not the POKEY 10k load',parts['R12']['value']=='1k 1%')
for r,c,o,ac,lim,hp in [('R33','C22','AMP_L','L_AC','L_LIMIT','HP_L'),('R35','C23','AMP_R','R_AC','R_LIMIT','HP_R')]:
    check('DC-block and current-limiting chain '+hp,net(c,1)==o and net(c,2)==ac and net(r,1)==ac and net(r,2)==lim)
check('Left and right amplifier outputs are separate',net('U9',1)!=net('U9',7))
check('Sleeve is actual ground',net('J2','S')=='GND')
# Reuse serialization parser from the prior independently checked project.
parser="# Parse serialized KiCad symbols and placed pin locations, independent of renderer.\nlib=(P/'schematic/POKEY.lib').read_text(encoding='utf8')\nsymbols={}\nfor b in re.findall(r'DEF (.*?)\\n(.*?)ENDDEF',lib,re.S):\n    name=b[0].split()[0]; pins={}\n    for m in re.finditer(r'^X (\\S+) (\\S+) (-?\\d+) (-?\\d+) ',b[1],re.M): pins[m[2]]=(int(m[3]),int(m[4]))\n    symbols[name]=pins\nseen={}\nfor f in sorted((P/'schematic').glob('0*.sch')):\n    t=f.read_text(encoding='utf8')\n    labels={}\n    for m in re.finditer(r'Text GLabel (\\d+) (\\d+)[^\\n]*\\n([^\\n]+)',t): labels[(int(m[1]),int(m[2]))]=m[3]\n    wires={}\n    for m in re.finditer(r'Wire Wire Line\\n\\s*(\\d+) (\\d+) (\\d+) (\\d+)',t):\n        a=(int(m[1]),int(m[2]));b=(int(m[3]),int(m[4]));wires[a]=b;wires[b]=a\n    nc={(int(m[1]),int(m[2])) for m in re.finditer(r'NoConn ~ (\\d+) (\\d+)',t)}\n    for body in re.findall(r'\\$Comp\\n(.*?)\\$EndComp',t,re.S):\n        m=re.search(r'L POKEY:(\\S+) (\\S+)',body);name,ref=m.groups()\n        xy=re.search(r'^P (\\d+) (\\d+)',body,re.M);x,y=map(int,xy.groups())\n        for num,(dx,dy) in symbols[name].items():\n            coord=(x+dx,y-dy); n=net(ref,num)\n            check('KiCad contact '+ref+'.'+num,(coord in nc) if n is None else labels.get(wires.get(coord))==n)\n            seen[(ref,num)]=n\ncheck('All 343 serialized KiCad contacts present',len(seen)==sum(len(p['pins']) for p in parts.values()))\n\n"
parser=parser.replace('343 serialized KiCad contacts','349 serialized KiCad contacts')
parser=parser.replace('POKEY','TIA')
exec(parser)
for a,d in itertools.product(range(32),range(256)):
    q1=q2=0
    for byte in [0x20|a,d]:
        for bit in range(7,-1,-1):
            last=q1>>7;q1=((q1<<1)|((byte>>bit)&1))&255;q2=((q2<<1)|last)&255
    assert q1==d and q2==0x20|a
check('SPI bit order: all 8192 five-bit-address/data combinations',True)
for phase in range(60):
    a=b=c=0; selected=0
    for tick in range(180):
        req=int(phase<=tick<phase+25)
        a,b,c=req,a,b
        selected+=int(b and not c)
    assert selected==1
check('Two synchronizer stages/edge detector: one ideal write pulse in 60 phases',True)
freqs={}
for name,hz in [('PAL',3546894),('NTSC',3579545)]:
    div=Fraction(900000000,hz);a=div.numerator//div.denominator;b=div.numerator%div.denominator;c=div.denominator
    check(name+' fractional-divider representability',4<=a<=900 and c<=1048575 and Fraction(900000000,1)/(a+Fraction(b,c))==hz)
    freqs[name]={'master_hz':hz,'phi0_hz':hz/3,'audio_tick_hz':hz/114,'multisynth_a':a,'multisynth_b':b,'multisynth_c':c}
old=json.loads((P/'Reference_POKEY.json').read_text(encoding='utf8'))
oldparts={p['ref']:p for p in old['parts']}; reuse=[]
for ref in sorted(set(oldparts)|set(parts)):
    a=oldparts.get(ref);b=parts.get(ref)
    state='unchanged part/value' if a and b and a['value']==b['value'] else 'changed part/value' if a and b else 'added' if b else 'removed'
    reuse.append([ref,a['value'] if a else '',b['value'] if b else '',state,b['note'] if b else 'POKEY-only component removed'])
with (P/'POKEY_Component_Reuse.csv').open('w',newline='',encoding='utf-8-sig') as f:
    wr=csv.writer(f,delimiter=';');wr.writerow(['Reference','POKEY value','TIA value','Status','TIA note']);wr.writerows(reuse)
same=sum(x[3]=='unchanged part/value' for x in reuse)
rc_min=990*33e-12*.95*math.log(4.4/1.4)*1e9
rc_max=1010*50e-12*math.log((5.25-.33)/(.5-.33))*1e9
report=f'''UM6526P1 PAL TIA / ESP32 Rev. A - structural verification

{len(parts)} parts; {len(D['nets'])} nets; {len(seen)} serialized contacts.
{len(checks)} structural/model checks passed.
SPI: 8192 combinations. Request pipeline: 60 ideal starting phases.
{same} reference positions retain the POKEY component type/value.
JP1 is NOT POPULATED in PAL; the netlist includes its optional pads only.

The socket map is a PAL-family engineering mapping, not a found UMC manufacturer datasheet.
No KiCad import/ERC, firmware compilation, SPICE, hardware or acoustic test was performed.
Numeric TIA setup/hold limits and UMC-specific DC limits were NOT verified.

RC illustration (not an end-to-end timing proof):
Ideal-step threshold delay approximately {rc_min:.1f}...{rc_max:.1f} ns using
R40=1k/1%, C27=33pF/5%, total C<=50pF and stated HCT14 thresholds/levels.
Clock slew, output impedance and load change these values.
Measure PHI2 Low>=400ns; select setup>=50ns and hold>=30ns are DESIGN TARGETS,
not claimed TIA manufacturer limits. Change delay/layout if measurements fail.

Computed nominal clock profiles (actual crystal error/jitter not included):
'''
report+=json.dumps(freqs,indent=2)+'\n\n'+'\n'.join('PASS '+x for x in checks)+'\n'
(P/'Verification_Report.txt').write_text(report,encoding='utf8')
(P/'Clock_Profiles.json').write_text(json.dumps(freqs,indent=2),encoding='utf8')
print(report[:1700])
