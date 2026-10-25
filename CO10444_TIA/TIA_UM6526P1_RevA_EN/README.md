# UM6526P1 PAL TIA / ESP32 - Rev. A (English)

Conditional prototype design, 2026-10-25. Read Documentation.md before assembly.

Open schematic/TIA_ESP32.sch in KiCad with all local sheets and libraries together; save to convert the legacy format. No KiCad import/ERC test was possible. No PCB layout is supplied.

The separate PDF contains six A3 schematic sheets followed by English documentation, sources and BOM. The editable package includes the schematic, design.json, Nets.csv, Bill_of_Materials.csv, clock profiles and an Arduino WiFi example.

PAL default: UM6526P1 is mapped to the Atari C011903 PAL family using the cited sources. A standalone UMC electrical datasheet was not found. This is not a manufacturer-verified clone pinout or guaranteed timing design. Auxiliary pins are conservatively labelled; their clone-specific functions remain unconfirmed.

JP1 MUST NOT be fitted for PAL. Its optional pads are present in the netlist. The C010444 NTSC conversion requires a verified NTSC chip, the NTSC clock profile and JP1; see sheet 6 and section 8. The design is audio-only; full PAL color circuitry is not included.

77 component reference positions retain the POKEY type/value. See POKEY_Component_Reuse.csv. The TIA socket, clocks, write pulse, pull-up and firmware differ.

Firmware: firmware/TIA_Control/TIA_Control.ino; Arduino-ESP32, Adafruit Si5351 and Adafruit BusIO dependencies. Not compiled or hardware tested. Change the AP password. Set TIA_NTSC only for an actual NTSC chip. Disconnect the DevKit from this carrier when programming via USB.

Validate.py runs structural/model checks with Python 3 and the bundled reference JSON; it does not perform ERC, analog simulation or electrical validation. Verification_Report.txt records 366 checks, including serialized contacts and ideal bus models.

Before headphones, measure supplies, clocks, timing and audio with dummy loads. Engineering timing targets are not recovered UMC specifications. Keep manual MUTE open during power transitions; start volume at minimum. Neither acoustic safety nor fault protection is certified.
