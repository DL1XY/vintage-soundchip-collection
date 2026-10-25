# POKEY / ESP32 Rev. A - English edition

2026-10-25. Document-reviewed prototype design; no hardware testing.

- Schematic: open schematic/POKEY_ESP32.sch in KiCad. Keep all subsheets and libraries together. Save to convert to the current .kicad_sch format. No import test/ERC was performed here.
- PDF: the separately supplied PDF contains five A3 schematic sheets followed by A4 documentation, sources and bill of materials.
- Bill of materials: Bill_of_Materials.csv. Nets: Nets.csv. UTF-8, semicolon-delimited.
- Verification status and limitations: read Documentation.md and Verification_Report.txt.
- Firmware example: firmware/POKEY_Control/POKEY_Control.ino. Not compiled or hardware-tested. Remove the DevKit from the carrier circuit for USB programming.
- Re-run the structural checks with Python 3: python Validate.py. Only the Python standard library is required.

Requires USB-C 5 V with at least a 1.5-A current advertisement and a C-to-C cable. Default USB and A-to-C cables are unsupported. PHI2=1 MHz, write-only bus. POKEY DIP-40, ESP32-DevKitC V4 WROOM-32E and Pololu S13V15F5.

Before using headphones: open MUTE, set the potentiometer to minimum, and verify DC, audio levels and startup behavior using load resistors. The design has no certified hearing-protection level limit.

The project uses complete functional pin/net symbols. No PCB layout or footprint release is included. Map module, potentiometer, switch and socket functional contacts to actual physical pads before manufacturing.

This English edition preserves the original circuit values, reference designators, net names, source identifiers and verification limitations. Firmware comments and web-interface text are also in English.
