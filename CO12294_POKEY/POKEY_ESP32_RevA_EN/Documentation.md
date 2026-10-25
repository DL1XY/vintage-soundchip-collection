# POKEY / ESP32 - Rev. A (English)

2026-10-25. Document-reviewed prototype design.


## 1. Deliverables and verification status


This design connects an original Atari C012294 in DIP-40 to an ESP32-DevKitC V4 (WROOM-32E), a Wi-Fi web interface and a stereo headphone output carrying the same mono signal on both channels. The part number contains the digit zero: C012294. The intended operating temperature is 0...70 degrees C, limited by the original chip and oscillator.


Included: five A3 schematic sheets, an editable KiCad legacy project with local symbol libraries, a bill of materials, a complete net/contact list, machine-readable design data and a verification report. Wiring is complete at assembly level; the ESP32 DevKit and Pololu regulator are purchased modules. No PCB layout or manufacturing release is included.


The POKEY pin assignments and electrical output topology were verified against the original Atari datasheet; the pinout was cross-checked against the Atari service manual. Other IC pin assignments were checked against the manufacturer documents for the selected package variants. Values marked with source D are design choices or calculated design quantities.


The generated KiCad files were structurally checked for every contact and net. KiCad is not installed in this environment: no import test or KiCad ERC was performed. Also not performed: firmware compilation, SPICE simulation, assembly, oscilloscope measurements, EMC/ESD testing or acoustic calibration. This is therefore a document-reviewed prototype design, not a claim of a laboratory-proven safe device.


Deliberate limitation: the bus is write-only. All audio control registers are accessible, but RANDOM, POT and status registers cannot be read. PHI2 is fixed at 1 MHz, so pitch is not identical to PAL/NTSC Atari systems. The particular vintage chip must be tested at this clock frequency before release; the reviewed datasheet does not provide a defensible minimum PHI2 frequency here. This assumption is not presented as a guaranteed manufacturer specification.


VIN/GND/VOUT, T/R/S and H/W/L are intentionally functional contact identifiers. They do not invent pin numbers for modules, the socket or the potentiometer. Wire them using manufacturer markings and continuity measurements. ESP32 header contacts not shown are unused.


| File | Purpose |
|---|---|

| schematic/POKEY_ESP32.sch | Open in KiCad, then save in the current format |

| Bill_of_Materials.csv / Nets.csv | All 85 parts / all 71 nets with contact assignments |

| firmware/POKEY_Control/POKEY_Control.ino | Wi-Fi AP and web control as an untested starting point |

| Verification_Report.txt / design.json | Reproducible structural checks and design data |



## 2. POKEY: verified contact assignments


Source S1, sheet 33, cross-checked against S1b page 13. Pin numbers refer to the DIP-40 package; check the notch and pin-1 marking before insertion. A slash means active Low; _N is the corresponding net/symbol notation.


Supply range: 4.75...5.25 V; ICC up to 125 mA. PHI2 and ordinary bus inputs are TTL-compatible. Pin 37 is a multiple open-drain audio output, not a low-impedance voltage output. The Atari test load is 10 kohms to +4.75 V; R12 uses this load resistance on the regulated 5-V rail. Never connect headphones directly to pin 37. [S1, sheets 25-27]


Potentiometer contacts and BCLK are electrically bidirectional, although the pin list simplifies the potentiometer function as an input. Use resistors rather than hard ties to 5 V. Leave unused K, serial and IRQ outputs open. POKEY has no separate RESET contact; startup uses register initialization. [S1, sheets 26,32-33]


| Pin | Signal / connection | Pin | Signal / connection |
|---|---|---|---|

| 1 | VSS / GND | 21 | /K2 / open |

| 2 | D3 / D3 | 22 | /K1 / open |

| 3 | D4 / D4 | 23 | /K0 / open |

| 4 | D5 / D5 | 24 | SID / SID |

| 5 | D6 / D6 | 25 | /KR1 / KR1_N |

| 6 | D7 / D7 | 26 | BCLK / BCLK |

| 7 | PHI2 / PHI2 | 27 | OCLK / open |

| 8 | P6 / P6 | 28 | SOD / open |

| 9 | P7 / P7 | 29 | /IRQ / open |

| 10 | P4 / P4 | 30 | /CS0 / CS0_N |

| 11 | P5 / P5 | 31 | CS1 / CS1 |

| 12 | P2 / P2 | 32 | R/W / GND |

| 13 | P3 / P3 | 33 | A3 / A3 |

| 14 | P0 / P0 | 34 | A2 / A2 |

| 15 | P1 / P1 | 35 | A1 / A1 |

| 16 | /KR2 / KR2_N | 36 | A0 / A0 |

| 17 | VDD / 5V | 37 | AUDIO / AUD_RAW |

| 18 | /K5 / open | 38 | D0 / D0 |

| 19 | /K4 / open | 39 | D1 / D1 |

| 20 | /K3 / open | 40 | D2 / D2 |



## 3. Level translation and transactions


U2 and U3 are SN74HCT595PW devices powered from 5 V. Their High input threshold is 2 V, so 3.3-V ESP32 outputs can drive them. HC is not an equivalent substitute for HCT. The 5-V parallel side connects only to POKEY. Q1 isolates the 5-V OE_N pull-up from the ESP32 contact. Do not use MOSFET I2C level shifters on the fast push-pull bus. [S2,S12,D]


Use SPI Mode 0, MSB first, at 1 MHz. Send the control byte (0x10 | address) followed by the data byte. U2 holds D0...D7; U3 holds A0...A3 and CS1 on QE. Leave unused U3 outputs open. The LATCH pulse transfers both bytes simultaneously; trigger REQ only afterwards. Do not update the latches while REQ/the request pipeline is active.


Sequence: hold REQ Low for at least 10 us; shift two bytes; wait at least 1 us after the last SPI clock; hold LATCH High for at least 1 us, then Low; wait at least 2 us; hold REQ High for 10 us, then Low for 10 us. Do not change address/data during this interval. Wi-Fi may extend these delays because the external clock continues and hardware produces the single write pulse.


Startup: BUS_EN=0, REQ=0, LATCH=0 and LOGIC_CLR_N=0. Wait at least 100 ms; set CLR_N High; allow at least 50 ms of clock operation. First latch 0x0000, then set BUS_EN=1. Initialize SKCTL=0, AUDF/AUDC and AUDCTL=0, IRQEN=0, SKCTL=3 and STIMER=0. Keep the potentiometer at minimum and MUTE active throughout. R6=10 kohms holds all flip-flop clear inputs Low during an ESP32 reset.


Pull-downs on REQ, LATCH and SPI define startup states; CS1=Low while U3 is high-impedance prevents chip selection. R/W then remains permanently Low. Only one task may issue transactions; the example web server handles them serially.


| ESP32 function | GPIO | DevKit header |
|---|---|---|

| MOSI / SPI_DATA | 23 | J3.2 |

| SCK / SPI_CLK | 18 | J3.9 |

| LATCH | 27 | J2.11 |

| REQ | 32 | J2.7 |

| LOGIC_CLR_N | 26 | J2.10 |

| BUS_EN | 25 | J2.9 |

| Power | 5V / GND | J2.19 / J2.14 and J3.1 |



## 4. PHI2 and timing analysis


X1 supplies 4 MHz. U4 is a two-stage Johnson counter: (Q1,Q2) = 00 -> 10 -> 11 -> 01 -> 00. Q2 supplies PHI2=1 MHz with nominal 500-ns High and Low intervals. Q1=MIDLOW rises nominally 250 ns before PHI2 rises and 250 ns after PHI2 falls. The original chip therefore runs independently of Wi-Fi and operating-system interruptions.


U5A samples asynchronous REQ. U5B is the second synchronizer stage; U6A stores the previous state. NAND(REQ_SYNC, /REQ_OLD) produces a Low pulse lasting one PHI2 period. CS0_N changes in the middle of PHI2 Low. This meets select setup and hold requirements, unlike a flip-flop clocked directly on the relevant PHI2 transition. Any brief NAND transition glitches occur during this Low phase and must settle before the next rising edge.


The estimate assumes VCC>=4.75 V, 0...70 degrees C, and no more than 50 pF load per HCT output. Conservative bounds: HCT74 CLK->Q maximum 35 ns plus 19 ns output transition; NAND maximum 25 ns plus 19 ns transition; X1 +/-100 ppm. Setup lower bound: 249.975 - 54 - 54 - 44 = 97.975 ns. Select hold lower bound: 249.975 - 54 = 195.975 ns. This is a digital limit calculation with an explicit load assumption, not measured signal integrity. [S3,S3b,S4,D]


MIDLOW drives four HCT inputs: U4.12, U5.3, U5.11 and U6.3. At a maximum of 10 pF each, approximately 10 pF remains for traces and instruments. Use short connections, a compact PCB and active/low-capacitance probes. Long breadboard wires can invalidate the calculation. Measure edges, voltage levels and setup/hold directly at U1 before release.


Two synchronizer stages reduce metastability risk. The datasheet provides no parameters supporting a numerical MTBF guarantee for this particular arrangement; none is asserted. Structural checks model ideal digital logic and do not replace analog timing measurements.


| POKEY requirement [S1 sheet 28] | Reference edge | Design |
|---|---|---|

| R/W setup >=130 ns | Before PHI2 rising edge | Permanently Low |

| R/W hold >=30 ns | After falling edge | Permanently Low |

| Address setup >=130 ns / hold >=30 ns | Before/after rising edge | Latched >=2 us before REQ; stable throughout transaction |

| Chip-select setup >=50 ns | Before rising edge | Calculated >=97.9 ns |

| Chip-select hold >=30 ns | After falling edge | Calculated >=195.9 ns |

| Data setup >=130 ns / hold >=10 ns | Before/after falling edge | Latched >=2 us before REQ; stable throughout transaction |



## 5. USB-C, current budget and power


J1 connects both CC contacts to TUSB320. Its internal Rd resistors are used; do not add parallel external 5.1-kohm resistors. PORT=GND selects sink mode; leaving ADDR open selects GPIO mode. TLV75533 supplies only the CC controller at 3.3 V, because the recommended TUSB320 VDD range does not permit direct connection to an arbitrary 5.25-V VBUS. [S5,S7]


TUSB320 OUT1 is Low only after detecting a 1.5-A or 3-A current advertisement. TPS2552 active-Low enable connects directly to it. The main load remains off with default USB current or no connection. A USB-C 5-V source advertising at least 1.5 A and a C-to-C cable are therefore required. A-to-C cables, unenumerated PC ports and default-current-only sources are intentionally unsupported. No USB PD request for a voltage above 5 V is made. [S5 Table 7-3]


R3=21.5 kohms/1% limits the main input branch to approximately 1.106...1.297 A according to the TI table. The CC controller and LDO are upstream and require only a small additional current. TPS2552, not TPS2553, is mandatory because of active-Low enable polarity. Loss of the current advertisement turns off the main load. [S6]


M1 is a complete S13V15F5 buck-boost module. It compensates for input voltage above or below 5 V and supplies nominal 5 V +/-3% (4.85...5.15 V). At 4.85 V, only 100 mV of wiring loss remains before the POKEY minimum of 4.75 V is reached. Use low-resistance supply and return paths and measure at the IC. The regulator internal circuit and parts belong to the purchased product, not this bill of materials. [S8]


Budget at the 5-V output: ESP32 DevKit up to 500 mA as a design allowance, not a guaranteed consumption specification; POKEY 125 mA datasheet maximum; X1 15 mA; logic/analog/pull-ups up to 40 mA design allowance: total 680 mA. At 4.5-V input, assumed 85% efficiency and 5.15-V output, input current is about 0.92 A plus regulator quiescent current. Efficiency is typical, not a guaranteed worst case: verify Wi-Fi peaks, regulator startup and current limiting on the prototype. [S1,S4,S8,D]


C1/C4 total 2.3 uF nominal upstream of the load switch. C5 and larger reservoirs are downstream of U11; inrush and startup still require measurement. Use X7R MLCCs rated at least 10 V and check effective capacitance under DC bias. This design is not USB-certified and does not demonstrate immunity to all fault voltages or ESD events.


Power the ESP32 only through its 5-V header. For programming, remove the entire DevKit from its socket and flash it separately using Micro-USB; disconnect Micro-USB before reinstalling it. Merely disconnecting the main USB-C source is not sufficient isolation, because programming USB could back-power the rest of the circuit. [S9,D]


## 6. Audio output and headphone protection


R12=10 kohms pulls the multiple open-drain output up to 5 V. U8A buffers it with high input impedance so the potentiometer and input resistors do not significantly change the POKEY load characteristic. Do not add a filter capacitor directly to AUD_RAW; Atari specifies a 30-pF output load. Keep input, trace and probe capacitance low. The stages are nonlinear; the datasheet does not establish an exactly repeatable full-scale audio level for every vintage chip. [S1 sheet 27,S11]


C19 removes the DC component. R27=22 kohms and RV1=10 kohms logarithmic limit the level before amplification. U8B buffers the half-supply reference, which ramps slowly through R25/R26 and C18, for both LM4808 noninverting inputs. C18 connects to the reference divider, not directly to the op-amp output. [D]


C20/C21=1-uF film capacitors couple the same mono signal separately into the inverting branches. Ri=Rf=20 kohms gives gain=-1 for each channel. Both outputs are in phase but electrically separate. R37/R38 reproduce the TI reference circuit 20-kohm DC loads. U9 is LM4808M/NOPB in SOIC-8; WSON must not be substituted because its pin assignments differ. [S13 Figures 1,3]


C22/C23=470 uF/10 V block the nominal 2.5-V output bias. Connect POSITIVE to AMP_L/AMP_R and NEGATIVE to L_AC/R_AC. R34/R36=100 kohms discharge the socket side even without headphones. R33/R35=100 ohms/0.25 W limit current during insertion shorts; SW1 disconnects both channels as MUTE. Sleeve is GND. Never connect the amplifier outputs, or Tip and Ring, together.


In the audio passband, maximum nominal pre-attenuation is approximately (10k || 20k || 20k || 1M) / (22k + (10k || 20k || 20k || 1M)) = 0.1844. Conservatively assuming a stationary 0...5.25-V square wave centered around its mean gives about 0.484 V RMS before the 100-ohm resistors; a 32-ohm load receives approximately 0.117 V RMS or 0.43 mW per channel. This is a level estimate, not a bound on every startup transient. Resistor and potentiometer tolerances affect it. [D]


Target loads: passive headphones with 16...300 ohms per channel. The output high-pass corner set by 470 uF and (100 ohms + load) is nominally 2.9 Hz at 16 ohms, 2.6 Hz at 32 ohms and 0.85 Hz at 300 ohms. Attenuation and source impedance are intentionally high; frequency response and loudness can depend on headphone impedance. This is not a speaker, bridged or balanced headphone output.


Electrical protection here assumes correctly assembled normal operation, not arbitrary component failures. A failed output capacitor can pass DC. Turn-on/off clicks are avoided using the manual MUTE sequence, not an automatic speaker-protection circuit. Without headphone sensitivity, level cannot be bounded in dB SPL; no hearing-protection or standards-compliance claim is made. Test with load resistors first and start listening with the volume at minimum.


## 7. Assembly and measurable release criteria


1) With POKEY removed, check supply nets for shorts, socket orientation and electrolytic polarity. Place every 100-nF bypass directly at its IC supply pins: C8 U2, C9 U3, C11 X1, C12 U4, C13 U5, C14 U6, C15 U7, C16 U1, C25 U9 and C26 U8. Put C1/C4 at U11/U12 input and C2/C3 at U12 output/U10.


2) Use a USB-C supply advertising 1.5/3 A. Measure VBUS, 3V3_CC, USB_LIMITED and 5V. The main branch must not start with an inadequate current advertisement. At the POKEY socket, pin 17 relative to pin 1 must remain within 4.75...5.25 V under load. Check startup overshoot and Wi-Fi current peaks.


3) Initialize the DevKit with POKEY still removed. Measure PHI2 at socket pin 7: 1 MHz, approximately 50% duty cycle, Low <=0.8 V, High >=2.0 V and clean edges. After reset, CS1 must not go High until software enables it. Check LOGIC_CLR_N and OE behavior.


4) Capture write pulses simultaneously on PHI2, /CS0, CS1, address and data. Check the timing table: select stable at least 50 ns before the rising edge and until 30 ns after the falling edge; address 130 ns before/30 ns after the rising edge; data 130 ns before/10 ns after the falling edge. There must be exactly one selected PHI2 cycle per REQ. This is the decisive hardware verification still to be performed.


5) Power off, set SW1=MUTE and insert POKEY. Monitor current consumption. Set all AUDC registers to zero and check the output stages without headphones: U9 outputs approximately VREF, AC outputs nearly 0 V DC after settling. Account for the 30-pF load assumption when probing pin 37.


6) Substitute one 32-ohm/0.25-W test resistor from Tip to Sleeve and one from Ring to Sleeve. After at least 2 s, with volume at minimum, set SW1=PLAY. Apply a test tone and increase volume slowly; check that both channels have the same signal and check clipping and DC. Project acceptance criterion after settling: |DC| <10 mV at each loaded output. Investigate larger deviations before use; this is a project criterion, not a datasheet limit.


7) Observe power cycling and plug insertion with load resistors; open MUTE before every power change. Perform any output-short test only under controlled bench conditions and monitor temperature. Connect headphones only afterwards. If clicks occur despite MUTE, check wiring and switch contact sequence.


Layout: use a continuous common ground plane and route audio returns to a star point near the amplifier/socket ground. Keep digital traces short. Keep the USB regulator, X1 and Wi-Fi antenna away from the high-impedance audio input; observe the DevKit antenna clearance. Place C22/C23 and output resistors close to the socket routing. Long cables and enclosure ESD require separate protection/EMC design.


## 8. Editing, firmware and open assumptions


KiCad: extract the complete folder. Open schematic/POKEY_ESP32.sch in the schematic editor. The local sym-lib-table references POKEY.lib; POKEY_ESP32-cache.lib is also included. KiCad can convert legacy files to .kicad_sch with embedded symbols when saving. If prompted about libraries, add the supplied POKEY.lib as a legacy library. Import was not performed here; run ERC and recheck the netlist after opening. [S15]


Rectangular symbols show fully labeled IC/module connections; identical global net names connect all sheets. An x indicates an intentionally open contact. No PCB footprints are supplied. In particular, do not transfer module, socket, switch or potentiometer functional contacts directly to a PCB without assigning actual pads. Check every physical pad against the manufacturer drawing before layout.


Firmware: open firmware/POKEY_Control/POKEY_Control.ino using Arduino-ESP32 and the ESP32 Dev Module target. Only the core WiFi, WebServer and SPI libraries are needed. The example has not been compiled. Change the password in the source before use. Remove the DevKit from the main circuit for USB programming.


After startup, connect to Wi-Fi POKEY-Control and open http://192.168.4.1 (the standard Arduino SoftAP address). The four channels have divider, volume and sound-code controls. The displayed values come from software shadow registers, not chip readback. Sound code 5 selects the usual pure tones (AUDC upper bits 101). Global special modes can be added through the write function; complete music/synthesizer firmware is outside the hardware verification scope.


Open items before practical release: behavior of the individual vintage chip at 1 MHz; analog full-scale audio; effective MLCC capacitance; settling and click behavior; capacitance of the actual wiring/layout; regulator startup under current limiting; Wi-Fi peaks and thermal margin. These are assumptions or measurement tasks, not pin assignments presented as confirmed.


Component conventions: unless stated otherwise, resistors are 1%, rated at least 0.125 W; R33/R35/R39 at least 0.25 W. Ceramic capacitors: X7R, at least 10 V. Electrolytics: at least 10 V, 105 degrees C; use low-leakage 470-uF output capacitors. Film capacitors: 1 uF, at least 10 V. Potentiometer: 10 kohms logarithmic, typical +/-20%. Switch: DPST, at least 12 V/100 mA, suitable for low-level audio. S1b is a historical Atari service-manual scan, not a current manufacturer datasheet.


## 9. Sources


### S1: Atari POKEY CHIP C012294 Rev. B, original scan

https://www.mikesarcade.com/estore/datasheets/pokey.pdf

Sheet 25: supply/ICC/logic levels; 26: PHI2 and mixed I/O; 27: audio; 28-31: timing; 32: registers; 33: pin list. In this scan, PDF page numbers match sheet numbers.


### S1b: Atari 800XL Service Manual

https://www.atarimania.com/documents/Atari%20800XL%20Service%20manual.pdf

POKEY pin diagram on printed page 13; independent cross-check of all 40 contacts.


### S2: TI SN74HCT595, SCLS880A

https://www.ti.com/lit/ds/symlink/sn74hct595.pdf

Page 3: pin functions; pages 4-6: levels, setup requirements and propagation delays. Selected package: PW/TSSOP-16.


### S3: TI SN74HCT74, SCLS169G

https://www.ti.com/lit/ds/symlink/sn74hct74.pdf

Page 3: pin diagram; pages 4-6: levels, setup/hold and maximum propagation delays. N/PDIP-14.


### S3b: TI SN74HCT00, SCLS062F

https://www.ti.com/lit/ds/symlink/sn74hct00.pdf

Pin diagram on page 2; electrical specifications and propagation delays on pages 4-5. N/PDIP-14.


### S4: ECS ECS-100X manufacturer datasheet

https://ecsxtal.com/store/pdf/ecs-100x.pdf

Pins: 1 NC, 7 GND, 8 OUT, 14 +5 V. The manufacturer product list includes the 4-MHz ECS-100AX-040. TTL output, +/-100 ppm; startup up to 30 ms.


### S5: TI TUSB320, SLLSEN9F

https://www.ti.com/lit/ds/symlink/tusb320.pdf

Page 4: pin functions. Table 7-3 on page 13: OUT1/OUT2 and current advertisement. EN_N tied to GND follows the application example.


### S6: TI TPS2552/3, SLVS841F

https://www.ti.com/lit/ds/symlink/tps2553.pdf

Pages 5-6: pinout and active polarity. Table 2, page 20: 21.5 kohms gives 1106...1297 mA including 1% resistor tolerance.


### S7: TI TLV755P, SBVS320D

https://www.ti.com/lit/ds/symlink/tlv755p.pdf

Page 3, DBV package only: 1 IN / 2 GND / 3 EN / 4 NC / 5 OUT. Selected part: TLV75533PDBVR.


### S8: Pololu S13V15F5, item 4084

https://www.pololu.com/product/4084

Manufacturer connections: VIN/GND/VOUT; output 5 V +/-3%; buck-boost; input 2.8...22 V. Complete module; its internal circuitry is outside this design.


### S9: Espressif ESP32-DevKitC V4

https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32/esp32-devkitc/user_guide.html

Header pinout and warning to use only one power input. WROOM-32E only, not WROVER.


### S10: GCT USB4105 manufacturer drawing

https://gct.co/files/drawings/usb4105.pdf

Contact identifiers A1/A4/A5... and B1/B4/B5...; selected part USB4105-GF-A. Connect all shell tabs to GND.


### S11: Microchip MCP6001/2/4, DS20001733L, mirrored manufacturer datasheet

https://download.mikroe.com/documents/datasheets/MCP6002_datasheet.pdf

Page 1 and Table 3-1 on page 11; MCP6002 PDIP-8. Original manufacturer product page: https://www.microchip.com/en-us/product/MCP6002


### S12: Nexperia 2N7002 manufacturer datasheet

https://assets.nexperia.com/documents/data-sheet/2N7002.pdf

Pinning: 1 Gate / 2 Source / 3 Drain. Used only as a slow OE switch at approximately 0.5 mA drain current.


### S13: TI LM4808, SNAS051D

https://www.ti.com/lit/ds/symlink/lm4808.pdf

Page 2, Figures 1 and 3: external reference, feedback and output capacitors; pages 14-15: component selection. SOIC/VSSOP and WSON pinouts differ.


### S14: Neutrik NJ3FP6C manufacturer page

https://www.neutrik.com/en/product/nj3fp6c

6.35-mm TRS socket with solder terminals. T/R/S in this design identify functional plug contacts, not asserted solder-lug numbers.


### S15: KiCad 9 Schematic Editor, legacy conversion

https://docs.kicad.org/9.0/en/eeschema/eeschema.html

Legacy section: open the .sch file with its cache library; saving produces .kicad_sch with embedded symbols.


### D: Design choice / calculation



Resistors, filters, bus architecture and protection measures are values developed for this design, not an asserted Atari reference circuit.


## 10. Bill of materials

See Bill_of_Materials.csv for all parts and assembly notes.
