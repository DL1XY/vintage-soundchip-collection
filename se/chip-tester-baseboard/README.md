# USB-C Sound Chip Tester Baseboard · Rev A

Open [ChipTester_Baseboard.kicad_pro](ChipTester_Baseboard.kicad_pro) in KiCad 8 or newer. The project has five schematic sheets and an 82 × 69 mm four-layer PCB. Keep the schematic sheets, library tables, symbol library and `Baseboard.pretty` folder together. The PCB includes routed copper and an In1.Cu ground zone. Press **B** in the PCB Editor to fill the zone before running DRC.

| Sheet | Circuit |
| --- | --- |
| USB-C | GCT USB4105 receptacle, separate CC pull-downs, flow-through USBLC6 data ESD clamp and 27 Ω series resistors |
| Power | AP2112K 3.3 V supply and firmware-enabled TPS2553 adapter supply. Pull-down on the enable input defaults the adapter supply off. |
| RP2350B | QSPI flash, 12 MHz crystal, 1.1 V core buck, BOOTSEL, reset and SWD |
| Adapter | One keyed 2×20 IDC connector with the pin numbering from the [architecture](../chip-tester-design.md). Disconnect USB to swap adapters. |
| Audio | Independent, AC-coupled L/MONO and R line outputs. Fixed unity-gain buffers and default mute. Use line inputs of 10 kΩ or higher. |

The layout uses an internal ground plane and places the audio buffers, analog switch and filter components next to the output jacks. Two buffered controls drive the analog switch at its 5 V logic levels. The adapter supplies the chip-specific signal conditioning and output level. A mono adapter connects to `AUDIO_L`. Leave the right channel muted in firmware.

## RP2350B firmware pin assignments

| GPIO | Signal |
| --- | --- |
| GP4–GP11 | D0–D7, contiguous for PIO |
| GP12–GP17 | A0–A5 |
| GP18–GP21 | CTRL0–CTRL3 |
| GP22, GP23 | CLK_OUT, RESET_N |
| GP24, GP25 | ID_SDA, ID_SCL |
| GP26, GP27 | BUS_EN, DATA_DIR |
| GP28, GP29–GP31 | READY_IRQ, AUX0–AUX2 |
| GP32, GP33 | ADAPTER_EN, ADAPTER_FAULT_N |
| GP34, GP35 | AUDIO_L_EN, AUDIO_R_EN |

Adapter ID runs on the always-on 3.3 V pin and dedicated ID bus. Keep the adapter's 5 V supply and bus drivers disabled through USB configuration and profile identification. On suspend or fault, mute the outputs, disable the bus and remove adapter power. This project contains the hardware. USB CDC commands and chip profiles require firmware.

## Prototype verification

The schematic and PCB were checked for footprint linkage, pin-to-net agreement and routed connectivity. KiCad ERC, filled-zone DRC and native import remain to be run. Before sending Gerbers, review the USB pair and chosen PCB stack-up, ground fill, component land patterns and fab limits. The layout uses 0.40 mm signal vias with 0.20 mm finished drills and 0.12 mm minimum design clearance. The RP2350B exposed pad requires reflow assembly. Review stencil apertures and exposed-pad via treatment with the board supplier.

On initial power-up, measure protected VBUS, 3.3 V, 1.1 V and the audio midpoint. Check USB enumeration and BOOTSEL with the adapter supply off, then verify the TPS2553 current limit with a dummy load. The 82.5 kΩ limit resistor is provisional pending measurements of baseboard current, adapter inrush and total USB current. Measure audio noise, output level and power-transition transients before using the line outputs for comparisons.

The [batch workbook](../chip-tester-bom/Chip%20Tester%20BOM.xlsx) is the earlier cost estimate. Extract the baseboard purchase list from the schematic. This revision adds an SN74AHCT125 buffer and uses 0402 passives near the RP2350B and analog switch.

## Design references

- [Raspberry Pi RP2350 hardware design guide](https://pip-assets.raspberrypi.com/categories/1214-rp2350/documents/RP-008280-DS-1-hardware-design-with-rp2350.pdf)
- [GCT USB4105 mechanical drawing](https://gct.co/files/drawings/usb4105.pdf)
- [ST USBLC6-2SC6 datasheet](https://www.st.com/resource/en/datasheet/usblc6-2sc6.pdf)
- [TI TPS2553 datasheet](https://www.ti.com/lit/ds/symlink/tps2553.pdf)
- [TI TS5A23157 datasheet](https://www.ti.com/lit/ds/symlink/ts5a23157.pdf)
- [Same Sky SJ1-3523N mechanical drawing](https://www.sameskydevices.com/product/resource/sj1-352xn.pdf)
