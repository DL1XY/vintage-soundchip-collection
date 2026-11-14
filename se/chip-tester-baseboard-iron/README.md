# USB-C sound chip tester baseboard · Rev B

Open [ChipTester_Baseboard_Iron.kicad_pro](ChipTester_Baseboard_Iron.kicad_pro) in KiCad 8 or newer. This revision is designed for assembly with a fine-tip soldering iron. The four-layer carrier measures 112 × 86 mm. [Rev A](../chip-tester-baseboard/README.md) uses a bare RP2350B and has its own layout.

## Assembly

1. Solder **D1 and U4** first. These are the two surface-mount parts on the carrier. Both have exposed SOT-23-6 leads at 0.95 mm pitch and extended solder pads. Tack one corner, align the remaining pins, then use flux and a fine tip to finish them. Inspect under magnification.
2. Install the axial resistors, radial capacitors, buttons, DIP sockets and through-hole connectors. The square pad and plus mark identify the positive side of the electrolytic capacitors. The ground zone uses thermal reliefs to make iron soldering easier.
3. Fit a **Pimoroni PGA2350 PIM722** on 2.54 mm pins. Align its A1 corner with the carrier's A1 mark. The layout uses the PIM722 pinout, including its USB data pins and 5 V supply input. Check alignment against the vendor drawing before soldering the full grid. [PGA2350 hardware documentation](https://shop.pimoroni.com/products/pga2350)
4. Fit an **Adafruit 4090** USB-C breakout, with its receptacle facing the edge marked USB-C. Use the 1×8 pin header and both mounting holes. Use spacers of the same height as the pin header support so plugging in the cable loads the hardware. Check that the plug seats fully. [Adafruit 4090 board files](https://github.com/adafruit/Adafruit-USB-C-Downstream-Breakout)

The module and USB-C breakout arrive with their fine-pitch components already soldered. The baseboard carries the USB data ESD clamp. The two USB series resistors are on the PGA2350.

## Parts for one baseboard

| Refs | Qty | Part |
| --- | ---: | --- |
| U1 | 1 | Pimoroni **PIM722** PGA2350 and 2.54 mm male pins for the 64-hole grid |
| J1 | 1 | Adafruit **4090** breakout, 1×8 2.54 mm pins and two M2.5 spacers with screws |
| D1, U4 | 1 each | **USBLC6-2SC6** ESD clamp and **TPS2553DBVR** current-limit switch |
| U5, U7 | 2 | **MCP6002-I/P** PDIP-8, with sockets if desired |
| U6 | 1 | **CD74HC4053E** PDIP-16, with socket if desired |
| F1 | 1 | **MF-R075** resettable fuse, 5.08 mm pitch |
| SW1, SW2 | 2 | **Omron B3F-1000** through-hole tactile switches |
| J2, J3 | 1 each | **WSL 40G** keyed 2×20 IDC header and 1×3 2.54 mm SWD header |
| J4, J5 | 2 | **SJ1-3523N** through-hole audio jacks |
| R1–R20 | 20 | Axial 1% resistors, 7.62 mm lead spacing. See schematic for values. |
| C1–C11 | 11 | Five 100 nF radial ceramics at 2.54 mm, two 1 µF film at 5.08 mm, one 47 µF and three 10 µF electrolytics with 5 mm body and 2 mm lead spacing |
| TP1–TP6 | 6 | 2.54 mm header pins or suitable wire loops |

Kamami listed PIM722 in stock and ships to Germany. Check availability before ordering the carrier. The older batch workbook prices Rev A. [Kamami PIM722](https://kamami.pl/en/base-boards-with-rp2040-and-rp235x/1199008-pga2350-mini-development-board-with-rp2350-microcontroller-769894025840.html) · [Kamami shipping](https://kamami.pl/en/content/6-delivery-and-payment)

Other sourcing references include [BerryBase for ADA4090](https://www.berrybase.de/en/adafruit-usb-type-c-breakout-board-downstream-connection), [Mouser Germany for CD74HC4053E](https://www.mouser.de/de/ProductDetail/Texas-Instruments/CD74HC4053E), and [Reichelt for WSL 40G](https://www.reichelt.de/de/de/shop/produkt/wannenstecker_40-polig_gerade-22834).

## Operation

The 40-pin adapter pinout and RP2350B firmware GPIO assignments match [Rev A](../chip-tester-baseboard/README.md#rp2350b-firmware-pin-assignments). The carrier uses the same clock and bus signals. USB CDC chip control and adapter profiles require firmware. To enter BOOTSEL, hold BOOTSEL while applying USB power. The RESET button grounds the module RUN pin.

The current-limited 5 V adapter supply defaults off. Allow adapter power only after USB configuration and identification. Budget the adapter's startup and steady-state current against the measured host current and minimum voltage at the chip. Switch off adapter power on suspend or fault, and disconnect USB before swapping.

Both outputs are AC-coupled and fixed gain. The analog section uses a filtered 3.3 V rail and an approximately 1.65 V midpoint. Start adapter calibration at **0.85 Vrms maximum** into a line input of 10 kΩ or higher, then measure clipping headroom. Mono adapters use L/MONO. Firmware can leave R muted independently.

## Verification before ordering

The schematic and board were checked independently for connector pinout, schematic-to-PCB net agreement and copper geometry. In KiCad, open the board, press **B** to fill the In1.Cu ground zone, then run native ERC and DRC and inspect the mountings. Native KiCad checks and hardware bring-up are pending. Confirm the USB-C data path in both cable orientations and measure adapter voltage, current limit, audio noise and startup transitions on the first build.
