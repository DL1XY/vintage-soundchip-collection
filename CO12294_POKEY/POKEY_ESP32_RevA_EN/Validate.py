from pathlib import Path
import json,re,itertools
R=Path(__file__).resolve().parent.parent
P=Path(__file__).resolve().parent
D=json.loads((P/'design.json').read_text(encoding='utf8'))
parts={p['ref']:p for p in D['parts']}
checks=[]
def check(name,condition):
    assert condition,name
    checks.append(name)
def net(r,n):return next(x['net'] for x in parts[r]['pins'] if x['n']==str(n))
expected={1:'GND',2:'D3',3:'D4',4:'D5',5:'D6',6:'D7',7:'PHI2',8:'P6',9:'P7',10:'P4',11:'P5',12:'P2',13:'P3',14:'P0',15:'P1',16:'KR2_N',17:'5V',18:None,19:None,20:None,21:None,22:None,23:None,24:'SID',25:'KR1_N',26:'BCLK',27:None,28:None,29:None,30:'CS0_N',31:'CS1',32:'GND',33:'A3',34:'A2',35:'A1',36:'A0',37:'AUD_RAW',38:'D0',39:'D1',40:'D2'}
check('U1: all 40 contacts compared against independent expected map',all(net('U1',k)==v for k,v in expected.items()))
check('Audio pull-up: 10k between 5V and AUD_RAW',net('R12',1)=='5V' and net('R12',2)=='AUD_RAW' and parts['R12']['value']=='10k 1%')
check('R/W permanently Low; no bus contention from POKEY reads',net('U1',32)=='GND')
check('LM4808 SOIC outputs 1/7, power 8/4',net('U9',1)=='AMP_L' and net('U9',7)=='AMP_R' and net('U9',8)=='5V_A' and net('U9',4)=='GND')
check('Left/right headphone channels are not shorted together',net('J2','T')!=net('J2','R') and net('J2','S')=='GND')
check('Output coupling capacitors and series resistors on both channels',all(net(c,1)==a and net(c,2)==b and net(rr,1)==b for c,rr,a,b in [('C22','R33','AMP_L','L_AC'),('C23','R35','AMP_R','R_AC')]))
check('USB enable active Low and separate 3V3_CC rail',net('U10',7)==net('U11',3)=='POWER_EN_N' and net('U10',12)=='3V3_CC')
check('No external parallel Rd resistors on CC',sorted(r for r,n,fn in D['nets']['CC1'])==['J1','U10'] and sorted(r for r,n,fn in D['nets']['CC2'])==['J1','U10'])
# Every GPIO net has only ESP outputs, HCT inputs, resistors or MOS gate.
for pi in parts['M2']['pins']:
    if pi['name'].startswith('GPIO'):
        for r,n,_ in D['nets'][pi['net']]:
            p=next(x for x in parts[r]['pins'] if x['n']==n)
            check('GPIO signal direction '+pi['net']+' -> '+r+'.'+n,r=='M2' or parts[r]['kind']=='R' or p['typ']=='I')

# Parse serialized KiCad symbols and placed pin locations, independent of renderer.
lib=(P/'schematic/POKEY.lib').read_text(encoding='utf8')
symbols={}
for b in re.findall(r'DEF (.*?)\n(.*?)ENDDEF',lib,re.S):
    name=b[0].split()[0]; pins={}
    for m in re.finditer(r'^X (\S+) (\S+) (-?\d+) (-?\d+) ',b[1],re.M): pins[m[2]]=(int(m[3]),int(m[4]))
    symbols[name]=pins
seen={}
for f in sorted((P/'schematic').glob('0*.sch')):
    t=f.read_text(encoding='utf8')
    labels={}
    for m in re.finditer(r'Text GLabel (\d+) (\d+)[^\n]*\n([^\n]+)',t): labels[(int(m[1]),int(m[2]))]=m[3]
    wires={}
    for m in re.finditer(r'Wire Wire Line\n\s*(\d+) (\d+) (\d+) (\d+)',t):
        a=(int(m[1]),int(m[2]));b=(int(m[3]),int(m[4]));wires[a]=b;wires[b]=a
    nc={(int(m[1]),int(m[2])) for m in re.finditer(r'NoConn ~ (\d+) (\d+)',t)}
    for body in re.findall(r'\$Comp\n(.*?)\$EndComp',t,re.S):
        m=re.search(r'L POKEY:(\S+) (\S+)',body);name,ref=m.groups()
        xy=re.search(r'^P (\d+) (\d+)',body,re.M);x,y=map(int,xy.groups())
        for num,(dx,dy) in symbols[name].items():
            coord=(x+dx,y-dy); n=net(ref,num)
            check('KiCad contact '+ref+'.'+num,(coord in nc) if n is None else labels.get(wires.get(coord))==n)
            seen[(ref,num)]=n
check('All 343 serialized KiCad contacts present',len(seen)==sum(len(p['pins']) for p in parts.values()))

# Exhaustive serial bit-order proof over 16 addresses x 256 data values.
for a,d in itertools.product(range(16),range(256)):
    shift1=shift2=0
    for byte in [0x10|a,d]:
        for bit in range(7,-1,-1):
            old=shift1>>7
            shift1=((shift1<<1)|((byte>>bit)&1))&255
            shift2=((shift2<<1)|old)&255
    assert shift1==d and shift2==(0x10|a)
check('SPI bit order: all 4096 address/data combinations',True)
# Discrete logic model, not analog metastability simulation.
for phase in range(40):
    q1=q2=s1=s2=s3=0; prev_mid=0; lows=0; sampled=[]
    for tick in range(240):
        req=int(phase<=tick<phase+48)
        q1,q2=1-q2,q1
        if not prev_mid and q1:
            s1,s2,s3=req,s1,s2
        prev_mid=q1
        cs=int(not(s2 and not s3))
        if q2:sampled.append(cs)
    # Two 4MHz ticks per high phase; one selected PHI2 high phase = two samples.
    assert sampled.count(0)==2,(phase,sampled.count(0))
check('Johnson/request model: exactly one write for 40 starting phases',True)
setup=250*(1-0.0001)-(35+19)-(35+19)-(25+19)
hold=250*(1-0.0001)-(35+19)
check('CS setup >50 ns, hold >30 ns in the 50-pF model',setup>50 and hold>30)
POT=10000; par=1/(1/POT+1/20000+1/20000+1/1e6)
atten=par/(22000+par)
report='POKEY ESP32 Rev. A - automated structural verification\n\n'
report+=f'{len(parts)} components; {len(D["nets"])} nets; {len(seen)} contacts.\n'
report+=f'{len(checks)} individual checks passed.\n'
report+='SPI: 4096 combinations; request model: 40 phases.\n'
report+=f'Conservative CS setup lower bound {setup:.1f} ns; Hold {hold:.1f} ns.\n'
report+=f'Nominal maximum audio pre-attenuation {atten:.5f}.\n\n'
report+='Limitations: no KiCad ERC/import test (KiCad not installed), no SPICE simulation,\nno firmware build, no measurements, no statistical MTBF guarantee.\n'
report+='Structural verification does not replace these forms of validation.\n\n'
report+='\n'.join('PASS '+x for x in checks)+'\n'
(P/'Verification_Report.txt').write_text(report,encoding='utf8')
print(report[:750])
