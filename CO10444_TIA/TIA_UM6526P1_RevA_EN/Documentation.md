# TIA / ESP32 - Rev. A (English)

2026-10-25. Document-reviewed prototype design.


## 1. Scope, chip identity and verification limits


This package adapts the previous POKEY audio controller to the exact chip marking confirmed by the user: UM6526P1, PAL TIA. The supplier cross-reference associates this marking with Atari C011903 PAL. C010444 normally denotes the NTSC TIA family; these labels must not be treated as one interchangeable pinout. A MOS/CSG6526 CIA is a different device and must never be substituted. [T3]


The intended function remains USB-C-powered, ESP32 Wi-Fi-controlled sound with a logarithmic volume potentiometer, manual mute and6.35-mm TRS headphones receiving mono on both channels. This is an audio-only standalone board, not a complete Atari console or PAL/NTSC video generator.


Included: six A3 schematic sheets, editable KiCad legacy project, full BOM and net list, source list, clock-profile calculations, component-reuse comparison and example Wi-Fi firmware. There are85 reference positions, including the unpopulated PAL link JP1;84 positions are assembled in the default PAL build.77 positions retain the POKEY part type/value.


Verified documentary information: Atari register functions and common interface, supply-contact locations, write edge, audio output pull-down principle, manufacturer pinouts for the modern components, and clock-module API. The user's UM6526P1 identity is corroborated by the supplier catalog. A standalone UMC UM6526P1 pin/electrical datasheet was not found. PAL auxiliary pads are therefore isolated or weakly terminated and not assigned a manufacturer-guaranteed electrical role.


The supplied socket mapping is explicitly a PAL-family engineering mapping conditional on compatibility of the actual UM6526P1. It is not a claim that every clone-specific pin, DC limit or timing limit was verified. Confirm the part/donor mapping and perform the documented bench checks before insertion or release. No unlocated UMC limits are replaced with POKEY limits.


Structural/model checks cover349 serialized contacts,76 nets,8192 SPI address/data combinations and60 ideal request starting phases. No KiCad import/ERC, firmware compile, SPICE simulation, assembly, oscilloscope test, EMC/ESD test or acoustic calibration was performed. This remains a document-reviewed prototype proposal, not a hardware-tested or production-approved device.


Nominal design environment: regulated5V, indoor0...70degreesC. These are operating assumptions for the overall prototype; they are not a recovered UMC temperature/DC specification. The module internals are purchased assemblies, not discrete circuitry included in the schematic.


| File | Purpose |
|---|---|

| schematic/TIA_ESP32.sch | Root schematic; six subsheets and local libraries |

| Bill_of_Materials.csv / Nets.csv | Assembly values, PAL/NTSC fit notes and every net/contact |

| POKEY_Component_Reuse.csv | Per-reference comparison against the English POKEY design |

| Clock_Profiles.json / Verification_Report.txt | Calculated frequencies and explicit verification limits |

| firmware/TIA_Control/TIA_Control.ino | Two-voice Wi-Fi example; PAL default; uncompiled |



## 2. Socket mapping and unused contacts


DIP-40 mapping below is conditional on the standard PAL TIA family. Check the notch/pin1 marking and actual donor-device mapping. TIA uses VCC pin20 and GND pin1; POKEY used VDD pin17. The two sockets are not interchangeable. Common interface: master OSC11, clock output PHI0 at4, bus clock PHI2 at26, R/W25. [T1,T7]


The four selects require /CS0,/CS2,/CS3 Low and CS1 High for selection. Here /CS2,/CS3 and R/W are grounded; /CS0 is the hardware pulse and CS1 is the latched software enable. A5 is grounded; A0...A4 are driven. D0...D7 are driven only for writes; D6/D7 can otherwise be TIA outputs, so read mode is not supported.


PAL audio is taken from pin13 as the combined signal. JP1 between pin12 and AUD_RAW MUST be unpopulated for the PAL UM6526P1. It exists solely for the documented NTSC option. Auxiliary pads8/12 are commonly reported as PAL-I/PAL-S, but their UMC-specific direction/thresholds are not independently verified here; neither receives an external clock drive. The schematic uses neutral auxiliary labels rather than an asserted UMC input/output type.


R13...R16 weakly terminate dumped inputs I0...I3 to GND at100k, avoiding a hard short if their dump transistors act. R21/R22 pull unused triggers I4/I5 up through10k. R17 gives unused DEL a weak100k ground reference; this is not the original high-voltage console color-delay bias. R18 weakly terminates auxiliary8 through100k. Unused video outputs and /RDY remain open.


No PAL4.433618-MHz color oscillator, color trimming or composite-video network is implemented. Audio operation without those color circuits is an explicit prototype assumption to be checked on the actual clone. Do not use this board as a video-output design.


| Pin | PAL-family role / connection | Pin | PAL-family role / connection |
|---|---|---|---|

| 1 | VSS / GND | 21 | /CS3 / GND |

| 2 | SYNC / open | 22 | /CS2 / GND |

| 3 | /RDY / open | 23 | CS1 / CS1 |

| 4 | PHI0 / PHI0 | 24 | /CS0 / CS0_N |

| 5 | LUM1 / open | 25 | R/W / GND |

| 6 | PAL LUM2 / open | 26 | PHI2 / PHI2 |

| 7 | PAL LUM0 / open | 27 | A5 / GND |

| 8 | PAL auxiliary* / PAL_AUX8 | 28 | A4 / A4 |

| 9 | COL / open | 29 | A3 / A3 |

| 10 | DEL (unused) / DEL_UNUSED | 30 | A2 / A2 |

| 11 | OSC / TIA_OSC | 31 | A1 / A1 |

| 12 | PAL auxiliary* / TIA12 | 32 | A0 / A0 |

| 13 | PAL combined AUDIO / AUD_RAW | 33 | D7 / D7 |

| 14 | D0 / D0 | 34 | D6 / D6 |

| 15 | D1 / D1 | 35 | I5 / I5 |

| 16 | D2 / D2 | 36 | I4 / I4 |

| 17 | D3 / D3 | 37 | I3 / I3 |

| 18 | D4 / D4 | 38 | I2 / I2 |

| 19 | D5 / D5 | 39 | I1 / I1 |

| 20 | VCC / 5V | 40 | I0 / I0 |



## 3. Reuse of POKEY components


77 reference positions retain the same part type/value. That count means reusable components, not identical whole-board wiring. The per-reference CSV identifies changed, added and removed positions; the schematic remains the authoritative wiring description.


The USB-C current-permission circuit and regulated5-V supply are retained. ESP32 DevKitC V4 WROOM-32E, both HCT595s, OE transistor, request synchronizer and NAND are retained. The entire MCP6002/LM4808 headphone chain, potentiometer, output capacitors,100-ohm series resistors, mute switch and TRS socket retain their values.


U3 wiring and firmware encoding change: QE now carries A4; QF now carries CS1. Reusing the POKEY control byte0x10 would enable the wrong function. U4 changes from SN74HCT74 to SN74HCT14; these are not pin-compatible substitutes. The POKEY4-MHz oscillator is removed, not reconnected to TIA OSC or PHI2.


R12 changes from10k to1k as the TIA audio pull-up design choice. Its actual swing and dissipation must be measured with the clone. The values of C19/C20/C21, feedback resistors, volume control and headphone protection remain unchanged because U8 buffers the raw chip output.


| Assembly | Reuse / change | Reason |
|---|---|---|

| USB-C /5V | Same J1,U10,U11,U12,M1 and values | Current permission and cable-drop compensation still apply |

| ESP32 / SPI | Same M2,U2,U3,Q1 | Add3V3/SDA/SCL for M3; remap fifth address bit and enable |

| Clock | Remove X1; replace U4; add M3,R40,C27,R41 | PAL/NTSC master synthesis and TIA-derived bus timing |

| TIA socket / load | New U1 map; R12=1k; JP1 DNP PAL | Different supply/bus pins and regional audio outputs |

| Analog headphones | Same U8,U9,RV1,SW1,J2 and values | Buffered mono source, separate DC-blocked channels |



## 4. Write bus and firmware transaction


Two SN74HCT595PW shift registers at5V translate3.3-V SPI signals and hold data/address stable. Use HCT rather than HC: the input thresholds are TTL-compatible. No5-V data line returns to an ESP32 input. Q1 isolates the5-V OE pull-up from GPIO25. [S2,S12]


SPI Mode0, MSB first,1MHz: send control=(0x20 | (address &0x1F)), then data. U2 holds the data byte. U3.QA...QE hold A0...A4 and U3.QF holds CS1. Wait at least1us after the last SPI edge, pulse LATCH High for1us, return Low and wait at least2us before REQ.


Hold REQ Low for20us before a transaction; after latching, drive REQ High for20us, then Low for20us. Data/address remain unchanged throughout. U5 has two synchronizer stages; U6 stores the old synchronized value. U7 computes NAND(REQ_SYNC, /REQ_OLD), producing one selected bus period in the ideal model. Wi-Fi delays may lengthen the waits without generating extra edges.


Only audio addresses0x15...0x1A are exposed by the web UI: AUDC0/1=0x15/0x16 (4bits), AUDF0/1=0x17/0x18 (5bits), AUDV0/1=0x19/0x1A (4bits). Frequency divider is0...31, waveform code0...15 and digital volume0...15. The POKEY AUDF/AUDC layout, AUDCTL, SKCTL and STIMER sequence do not apply. [T1]


Do not issue WSYNC/RSYNC or other video strobes from a generic raw-register endpoint. This firmware initializes both volumes to0, both sound codes to4 and both dividers to0; it accesses only the six audio registers. Changing one voice temporarily mutes it, updates code/divider, then restores volume. No input, collision or register readback is implemented.


| Function | ESP32 GPIO | DevKit header |
|---|---|---|

| SPI MOSI / clock | 23 /18 | J3.2 /J3.9 |

| LATCH /REQ | 27 /32 | J2.11 /J2.7 |

| Request CLR_N /BUS_EN | 26 /25 | J2.10 /J2.9 |

| I2C SDA /SCL | 21 /22 | J3.6 /J3.3 |

| M3 power | 3V3_ESP | J2.1 |

| Main power /ground | 5V /GND | J2.19 /J2.14 and J3.1 |



## 5. Master clock and timing assumptions


M3 is the original Adafruit Si5351A breakout#2045 with25-MHz reference crystal. Power VIN from the ESP32 DevKit3V3 output, not from5V: the module I2C pull-ups then remain in the3.3-V domain. CLK0 is approximately3V logic; two SN74HCT14 inverters translate it to a5-V master clock at TIA pin11. CLK1/CLK2 remain unconnected. [T4,T5]


Default PAL nominal master is3,546,894Hz. The TIA divides this by3 to produce PHI0, nominally1,182,298Hz. Two further HCT14 inverters buffer PHI0 into PHI2 at pin26. The POKEY independent1-MHz PHI2 generator is not reused. This audio-only clock loop substitutes for the console CPU clock path and must be tested for duty cycle/phase on the actual chip. [T1,D]


Firmware sets PLLA=25MHz x36=900MHz. PAL multisynth ratio is253+439303/591149; NTSC ratio is251+306841/715909. Both denominators fit the20-bit divider field, giving the requested nominal average frequency exactly in rational arithmetic. Actual crystal tolerance, fractional-divider jitter, propagation and startup remain physical quantities requiring measurement. No clock calibration or jitter limit is claimed. [T4,T6,D]


R40=1k/1% and C27=33pF/C0G/5% delay the falling PHI2 edge; U4 inverter5 converts this into a rising synchronizer clock. Count U4 input and wiring capacitance in a maximum total50pF. A simple ideal-step calculation spans approximately35.5...169.9ns using HCT14 threshold and rail bounds. Slew, output impedance and logic delays affect the real select transition. This is not an end-to-end guaranteed timing proof.


The reviewed Atari write diagram identifies leading setup, trailing hold and data setup relative to PHI2, and describes writes on its falling edge. It does not provide numeric UMC setup/hold limits. Therefore the following are engineering acceptance targets, not attributed manufacturer limits: measured PHI2 Low>=400ns, select setup>=50ns before rising and hold>=30ns after falling; address/data stable for the full transaction. If measurements fail, revise the delay/layout; do not assume the POKEY timing certificate applies.


The two-stage synchronizer reduces asynchronous request risk but has no calculated MTBF guarantee. Small NAND transition glitches may occur while the delayed Low-phase pipeline changes; confirm they settle before the next PHI2 rising edge. Digital model tests do not establish analog metastability or clock integrity.


## 6. Audio topology and headphone output


The Atari TIA description controls volume by changing audio-output pull-down impedance. Treat this as a sink-type output needing an external pull-up, not as a line-level source. R12=1k to5V is the TIA console-style load choice; this is changed from the POKEY10k load. The UM6526P1 analog transfer curve and maximum audio-output current were not recovered from a UMC datasheet, so verify the actual waveforms/current before release. [T1,T7,D]


PAL uses the already combined audio signal at pin13. JP1 stays unpopulated. For the verified NTSC option, pin12 and pin13 are the two sink-type audio outputs; fitting JP1 combines them into the same raw node and retains mono on both headphones. This permitted open-drain summing is distinct from tying amplifier outputs together. Never fit JP1 to a PAL auxiliary output.


U8A MCP6002 buffers AUD_RAW with high impedance. C19=1uF film removes DC; R27=22k and RV1=10k log provide attenuation and volume adjustment. U8B buffers the slowly ramped half-supply reference from R25/R26/C18. C18 is on VREF_RAW, not directly on the op-amp output.


U9 is LM4808M/NOPB SOIC-8, not the differently pinned WSON version. Each inverting channel has Ri=Rf=20k, giving gain=-1. C20/C21=1uF feed the same mono signal separately. R37/R38=20k retain the TI reference output loads. R39=2.2ohms, C24=100uF and C25=100nF filter/decouple its supply. [S11,S13]


C22/C23=470uF/10V block output bias: POSITIVE to AMP_L/AMP_R, NEGATIVE to L_AC/R_AC. The100k bleeders discharge the socket side. Each channel has its own100-ohm/0.25-W series resistor; SW1 is a mechanically linked DPST mute. Tip is left, Ring right, Sleeve actual GND. Never join AMP_L and AMP_R.


For16...300-ohm passive headphones, the output high-pass corner is approximately2.9Hz at16ohms,2.6Hz at32ohms and0.85Hz at300ohms. Nominal maximum pre-attenuation remains0.1844. A stationary0...5.25-V square-wave assumption gives approximately0.117V RMS/0.43mW into32ohms per channel. This is an estimate, not a certified transient or hearing-protection limit.


Use MUTE before power changes; after at least2s, with the potentiometer at minimum, select PLAY. Check DC and audio with load resistors before headphones. Protection assumes correct normal assembly; a failed output capacitor can pass DC. No automatic power-up mute, single-fault protection or dB-SPL certification is provided.


## 7. USB-C, power and assembly conventions


The POKEY USB-C supply is retained. TUSB320 has internal Rd; do not add external5.1k resistors. PORT=GND selects sink, ADDR open selects GPIO mode. TLV75533 powers only the CC controller at3.3V. TUSB320 OUT1 permits the main TPS2552 branch only when a1.5-A or3-A current advertisement is present. [S5,S7]


A5-V USB-C source advertising at least1.5A and a C-to-C cable are required. Default USB, unenumerated PC ports and A-to-C cables are unsupported. No PD voltage above5V is requested. TPS2552 active-Low enable is mandatory; TPS2553 is not equivalent. R3=21.5k/1% gives approximately1.106...1.297A input limiting per the TI table. [S5,S6]


Pololu S13V15F5 supplies nominal5V +/-3% to compensate for cable/switch losses. Set a prototype acceptance window of4.75...5.25V at TIA pins20/1; this is a conservative5-V design window, not an asserted UMC limit. At4.85-V module output only100mV remains for wiring drop to the lower target. [S8,D]


Allow500mA for the ESP32,150mA as an unverified TIA design reserve and100mA for module/logic/analog/pull-ups:750mA total at5V. This is an allowance, not a recovered TIA maximum. At5.15V output,4.5V input and assumed85% efficiency the main input is approximately1.01A plus module quiescent current. Typical efficiency is not a guaranteed lower bound; verify startup and Wi-Fi peaks against current limiting.


C1/C4 total2.3uF before the load switch. Larger reservoir capacitors remain downstream. C11 moves to3V3_ESP at M3; C12 bypasses the new HCT14. C16 must be directly across TIA pins20/1. Verify effective MLCC capacitance under bias. Inrush, thermal behavior and EMC/ESD remain test items.


Power the DevKit only through its5-V header in normal use. Remove the entire DevKit from the carrier for Micro-USB programming, disconnect programming USB and then reinstall it. Merely removing main USB-C does not isolate possible backfeed into the regulator. [S9]


Unless otherwise stated: resistors1%, >=0.125W; R33/R35/R39 >=0.25W. X7R ceramics >=10V; electrolytics >=10V/105degreesC; output electrolytics low leakage. C27 is specifically33pF C0G/5%, not a general X7R decoupler. Potentiometer10k logarithmic, usual +/-20%. DPST switch rated >=12V/100mA and suitable for small audio signals.


## 8. Required PAL-to-NTSC changes


Convert only with power removed. Replace the PAL UM6526P1 with a positively identified NTSC C010444-family TIA. Change the firmware TIA_NTSC constant from false to true. Fit JP1 only after confirming NTSC pin12 is an open-drain audio output. These chip/clock/link choices form one configuration; changing only the frequency does not convert a PAL chip into an NTSC device.


The nominal NTSC master is3.579545MHz instead of PAL3.546894MHz. PHI0 changes from1.182298MHz to about1.193182MHz. Derived audio tick master/114 changes from31.113105kHz to31.399518kHz. Their ratio is approximately1.009206, so unchanged divider settings raise pitch about0.921% or15.86cents. This is not the50/60-Hz frame-rate ratio.


For pure-tone codes4/5, the approximate tone relation is master/(114 x2 x(AUDF+1)). Integer AUDF values0...31 limit exact retuning. Other sound codes include additional dividers and polynomial sequences and must not be treated as pure-tone formulas. A full video/music-frame implementation would additionally need regional frame pacing, which this web controller does not use.


No analog headphone-stage or power-component change is required by the NTSC audio-only option. Recheck mixed raw audio amplitude with both voices because the load is now shared by two sink outputs. Video pin differences below remain electrically unused. A full video conversion requires appropriate regional color/video circuitry and cannot be inferred from this audio design.


| Item | PAL default | NTSC option |
|---|---|---|

| U1 identity | UM6526P1 /C011903 PAL family | Verified C010444 NTSC family |

| M3 CLK0 /firmware | 3.546894MHz /TIA_NTSC=false | 3.579545MHz /TIA_NTSC=true |

| Audio /JP1 | Pin13 combined; JP1 NOT FITTED | Pins12+13 summed; fit JP1 |

| Pins6/7/8 | LUM2 /LUM0 /PAL auxiliary | BLK /LUM2 /LUM0 |

| Pin12 | PAL auxiliary, never audio-bridged | Second audio pad |

| Pins5/9 | LUM1 /COL, unused | LUM1 /COL, unused |

| Color/video circuits | Not implemented; full color typically needs4.433618MHz network | Not implemented; full video requires NTSC network |

| USB/audio protection | Unchanged | Unchanged; repeat bench checks |



## 9. Commissioning and release checks


1) With U1 removed, verify all supply nets, socket orientation, electrolytic polarity and DNP status. JP1 must be physically absent for PAL. Confirm TIA pin20, not pin17, connects to5V. Confirm3V3_ESP powers M3 VIN and its I2C pull-ups; 3V3_CC is a separate rail.


2) Use an adequate C-to-C USB supply. Verify main load stays off with an insufficient current advertisement. Measure VBUS,3V3_CC,USB_LIMITED,5V and3V3_ESP. Check startup overshoot, current and Wi-Fi transients. Meet the stated supply acceptance window at socket20/1.


3) With TIA absent, configure M3 and verify master frequency/levels at socket11. Request logic must remain reset and CS1 Low until initialized. PHI0/PHI2 cannot be generated normally without U1: the clock loop depends on its internal divide-by-three output. Do not inject a5-V test signal into ESP32 I2C or M3 CLK0.


4) Power off, insert the confirmed PAL-family TIA, keep MUTE open and monitor current. Verify PHI0 at pin4, PHI2 at26 and master at11. Check actual Low/High levels and approximately1.182298-MHz bus clock. Measure PHI2 Low>=400ns before relying on the proposed delay circuit.


5) Capture PHI2,/CS0,CS1,address/data and REQ. Verify exactly one selected bus cycle per request. Engineering targets are select setup>=50ns and hold>=30ns; data/address must remain stable over the entire transaction and guard interval. These are explicit project targets because numeric UMC limits were unavailable, not a manufacturer compliance certificate.


6) Initialize both volumes to0. Test voice0 alone, voice1 alone and both together at PAL pin13. Confirm voice independence in register control but combined analog output. Investigate missing sound before adding clocks to unverified PAL auxiliary pads. Do not fit JP1 as a troubleshooting shortcut.


7) Use separate32-ohm/0.25-W dummy loads from Tip/Sleeve and Ring/Sleeve. After settling and with volume minimum, close PLAY and increase slowly. Require both channels to carry the same signal; check clipping and a project DC target |DC|<10mV after settling. This is not a datasheet limit. Observe power/plug transients and temperature using dummy loads before headphones.


Layout: continuous ground plane, short clock and SPI routes, very short BUS_DELAY node with known capacitance. Keep switching regulator, clock module and Wi-Fi antenna away from AUD_RAW. Preserve antenna clearance. Route headphone returns near amplifier/socket ground; place bypass and coupling components near their associated devices. Long breadboard wiring invalidates timing/load assumptions.


## 10. Editing and using the firmware


Extract the whole package. Open schematic/TIA_ESP32.sch in KiCad; keep the six subsheets, TIA.lib, TIA_ESP32-cache.lib and sym-lib-table together. Saving can convert legacy files to .kicad_sch with embedded symbols. Import was not tested here. Run KiCad ERC and recheck the generated netlist before layout. [S15]


Global net names connect all sheets; x marks an intentionally unconnected contact. JP1 has pads in the netlist but is not populated in PAL. Module pads VIN/GND/VOUT and0/1/2, socket T/R/S and potentiometer H/W/L are functional contact identifiers. No physical PCB footprints are released; map them to manufacturer pads before fabrication.


Firmware target: ESP32 Dev Module /DevKitC V4 WROOM-32E. Open firmware/TIA_Control/TIA_Control.ino. Install the Adafruit Si5351 library and its Adafruit BusIO dependency; WiFi/WebServer/SPI/Wire are supplied by Arduino-ESP32. The public APIs were checked, but no compilation or board test was performed. Change the AP password before use. [T6]


PAL startup holds BUS_EN Low and the request pipeline reset, initializes the clock module, checks PLLA lock/status, releases the pipeline, initializes the SPI latches and only then enables the bus and sets the six audio registers. If clock/I2C setup fails, firmware leaves the bus disabled. Do not interpret this as proof of TIA clock output or actual register acceptance: there is no chip readback.


Connect to Wi-Fi TIA-Control and open http://192.168.4.1. Two voices provide divider0...31, volume0...15 and sound code0...15. Codes4/5 are typical pure tones. The UI displays software shadow values, not measured/read TIA state. All off writes both digital volumes to zero. Only manual SW1 provides the specified physical headphone mute.


The package deliberately retains open items: UMC-specific limits and auxiliary-pad direction; audio-only operation without a PAL color oscillator; PHI0-to-PHI2 loop phase/duty; RC delay across real loading; output transfer/summing level; clock jitter; supply/inrush/thermal margin and headphone transients. Resolve them at the bench before treating the prototype as a finished device.


## 11. Sources


### T1: Atari Stella Programmer's Guide / TIA Model 1A

https://www.qotile.net/minidig/docs/stella.pdf

Atari text reconstructed in 1993. TIA description, audio control and output pull-down impedance; audio diagram PDF p40 (printed35), write-register map PDF p50 (printed45), clock/write diagrams PDF pp52-53 (printed47-48). The diagrams do not supply a numeric UMC setup/hold table.


### T2: Atari PAL Model 2600 Field Service Manual, C018041, Sep.1981 Rev.1

https://pdfcoffee.com/service-manual-atari-2600-pal-pdf-free.html

Archived Atari manual; accessible OCR confirms PAL main clock near3.546MHz and PHI0/PHI2 socket checks. Original PDF download was unavailable. Do not treat unreadable/unavailable PAL diagram details as independently verified here.


### T3: Best Electronics Atari replacement-chip cross-reference

https://www.best-electronics-ca.com/custom-i.htm

Supplier's own catalog identifies UM6526P1 with Atari C011903 PAL, and a separate NTSC TIA family. This supports identification, not UMC electrical limits.


### T4: Adafruit Si5351A original breakout #2045 and pinout

https://learn.adafruit.com/adafruit-si5351-clock-generator-breakout/pinouts

Manufacturer instructions: supply VIN at MCU logic voltage; I2C has10k pull-ups and level shifting; clock outputs are approximately3V. Selected original board has25-MHz crystal. Product: https://www.adafruit.com/product/2045


### T5: TI SN74HCT14, SCLS225G

https://www.ti.com/lit/ds/symlink/sn74hct14.pdf

PDIP-14 pinout p3; threshold/output-level limits p5; maximum propagation40ns and transition19ns at4.5V,50pF p6. RC delay is an application calculation, not a fixed timing specification.


### T6: Adafruit Si5351 library public API

https://github.com/adafruit/Adafruit_Si5351_Library/blob/master/Adafruit_SI5351.h

Checked APIs: begin(TwoWire*), setupPLLInt, setupMultisynth, setupRdiv, resetPLL, readDeviceStatus and enableOutputs. Firmware uses these APIs but was not compiled.


### T7: Atari 2600/2600A domestic service manual

https://www.digitpress.com/library/techdocs/Atari_2600_VCS_Domestic_Field_Service_Manual.pdf

Atari NTSC console interface and pinout reference. Not a PAL/UMC datasheet. TIA audio load is treated as a console-derived design choice, not a guaranteed clone transfer curve.


### S2: TI SN74HCT595, SCLS880A

https://www.ti.com/lit/ds/symlink/sn74hct595.pdf

Page 3: pin functions; pages 4-6: levels, setup requirements and propagation delays. Selected package: PW/TSSOP-16.


### S3: TI SN74HCT74, SCLS169G

https://www.ti.com/lit/ds/symlink/sn74hct74.pdf

Page 3: pin diagram; pages 4-6: levels, setup/hold and maximum propagation delays. N/PDIP-14.


### S3b: TI SN74HCT00, SCLS062F

https://www.ti.com/lit/ds/symlink/sn74hct00.pdf

Pin diagram on page 2; electrical specifications and propagation delays on pages 4-5. N/PDIP-14.


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


### D: Design assumption / calculation



New wiring, weak termination of unused color pads, RC timing targets and current allowances are engineering choices. They are not asserted as verified UMC specifications.


## 12. Bill of materials

See Bill_of_Materials.csv for all parts and assembly notes.
