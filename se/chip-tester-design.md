AI: GPT-6.1 Sol Light Result - Use at your own risk

# USB-C sound chip tester

Use one USB-C baseboard and one keyed, replaceable chip adapter at a time. Put the socket, chip-specific power, bus translation, oscillator where needed, and audio conditioning on the adapter. The baseboard handles USB, deterministic bus timing, power switching, and two fixed-gain line outputs. Swap adapters with power disconnected.

## Baseboard signal path

```text
PC ── USB-C ── RP2350B ── 3.3 V bus ── adapter translator ── sound chip
         │         │                                          │
         │         └─ timed writes, reads, reset, clock        │
         └─ 5 V ── current-limited switch ── adapter power     │
                                                               ▼
Line out L/MONO and R ◀── fixed-gain buffer/mute ◀── adapter audio stage
```

- USB-C receptacle wired as a USB 2.0 device and 5 V sink. Use a 5.1 kΩ Rd on each CC pin, low-capacitance ESD protection on D+/D−, and route USB per the MCU reference design. Use native USB on the RP2350B and expose BOOTSEL, reset and SWD for firmware recovery and bring-up. PIO and DMA handle timing and queued transfers. [RP2350 datasheet](https://pip-assets.raspberrypi.com/categories/1214-rp2350/documents/RP-008373-DS-2-rp2350-datasheet.pdf?disposition=inline)
- Keep the adapter supply off during USB enumeration. Enable it after configuration and only if its startup and running current, including any converter losses, fit the port budget after accounting for baseboard consumption. Target a 500 mA total ceiling on a configured default USB 2.0 host connection, with the descriptor, current limit and inrush designed accordingly. Switch off the adapter on suspend or loss of configuration. For adapters that exceed the budget, use a separately engineered higher-current USB-C variant with CC current detection or PD. [USB-IF Type-C power overview](https://www.usb.org/sites/default/files/D1T1-2%20-%20USB%20Type-C%20System%20Overview.pdf)
- Provide a switched 5 V supply for the adapter and a small always-on 3.3 V budget for its ID EEPROM. The EEPROM identifies a firmware profile and hardware revision. Each profile defines current budget, bus direction and timing, clock source, output mapping and supported operations. Keep the main rails off for unknown profiles. Use keyed, voltage-specific SID adapters to prevent fitting a 9 V part into a 12 V socket.
- Hold the chip in reset where available and keep translators disabled through power-up and shutdown. Use pull resistors for inactive strobes and hardware-default bus disable. Once rails are valid, apply the profile clock and initialization sequence, then unmute. For 5 V bidirectional data, use an OE/DIR translator such as SN74LVC8T245 with chip-side default states and a high-impedance turnaround between reads and writes. Translate clock, address and control separately to match the chip’s input levels. [TI SN74LVC8T245](https://www.ti.com/product/SN74LVC8T245)

## Proposed adapter connector

Allocate a keyed 2×20 connector. All digital signals crossing it are 3.3 V. Pin numbers are a starting allocation for schematic capture. Check current capacity, ground placement and clock integrity with the chosen connector and layout.

| Odd pin | Function | Even pin | Function |
| --- | --- | --- | --- |
| 1 | GND | 2 | 5V_SW |
| 3 | 3V3_ID | 4 | 5V_SW |
| 5 | ID_SDA | 6 | GND |
| 7 | ID_SCL | 8 | D0 |
| 9 | D1 | 10 | D2 |
| 11 | D3 | 12 | D4 |
| 13 | D5 | 14 | D6 |
| 15 | D7 | 16 | GND |
| 17 | A0 | 18 | A1 |
| 19 | A2 | 20 | A3 |
| 21 | A4 | 22 | A5 |
| 23 | CTRL0 | 24 | CTRL1 |
| 25 | CTRL2 | 26 | CTRL3 |
| 27 | CLK_OUT | 28 | GND |
| 29 | RESET_N | 30 | BUS_EN |
| 31 | DATA_DIR | 32 | READY/IRQ |
| 33 | AUX0 | 34 | AUX1 |
| 35 | GND | 36 | AUX2 |
| 37 | AUDIO_L | 38 | GND |
| 39 | GND | 40 | AUDIO_R |

The adapter maps the four control lines to chip-specific signals such as write, read, select or AY bus control. The adapter can use a local oscillator when clock precision or phase relationships call for it. Keep the ID bus electrically separate from switched logic so EEPROM access cannot back-power the chip.

## Audio

- Put the chip’s required load, DAC, bias circuit or current-to-voltage stage next to the socket. Use fixed resistors for scaling and summing. Mono adapters drive L/MONO and leave R muted. Stereo adapters use both outputs. Preserve raw channel test pads on adapters with separate voice pins, such as AY and TIA.
- Target up to approximately 1 Vrms unclipped into a 10 kΩ or higher line input at the top of each adapter’s test range. Use a low-noise dual op-amp output buffer, AC coupling where required, and hardware-default mute during resets and power transitions. Choose gain per adapter after measuring its largest output. A small internal calibration trimmer is optional where part tolerances require it. Omit front-panel volume pots.
- Use a four-layer PCB with a continuous ground plane. Place USB, clocks and converters away from audio. Keep switcher current loops small, route analog signals away from clock and bus traces, and filter power locally at the analog stages. Use a post-regulator where voltage headroom allows. Keep analog outputs low impedance and place their return paths close to the signals across the adapter connector.
- Measure idle noise and clock or converter spurs with USB connected, during heavy bus activity and with the outputs terminated in 10 kΩ. Check output DC and power-cycle transients on both channels. Record conditions and measured levels for each adapter as its baseline.

## PC control

Expose USB CDC for a Python CLI on the PC, with commands for adapter info, reset, register writes, supported reads, and timestamped batches. Queue batches on the controller and execute them against its local clock. Chip profiles map this interface onto register writes, speech command streams or sample feeds, depending on the chip. Firmware updates use the same USB-C cable via BOOTSEL. For automated audio checks, connect the line outputs to an audio interface and capture them from the PC.

## First adapters

| Adapter | What it verifies |
| --- | --- |
| AY-3-8910 / YM2149 | Configurable parallel bus, clock and three analog voice pins. Use a fixed mono summing stage with individual voice test pads. |
| SAA1099 | Two independent line outputs and stereo routing. |
| POKEY | Reuse the existing socket/bus and audio circuitry as a reference. Verify its clocked register writes and check current on the new USB power path. |
| PAL TIA | Reuse the existing PAL chip and clock circuits as a reference. Validate the actual UMC part, its write timing and the two audio pins before finalizing the adapter. |
| YM3812 / YM2151 | Separate adapter designs with the corresponding Yamaha DACs and analog stages. |
| MOS6581 / MOS8580 | Separate adapter builds with 12 V or 9 V analog rails respectively, correct filter parts and a measured USB power budget. |

Start schematic capture with the baseboard, AY and SAA1099. These cover mono, stereo and two different bus interfaces. Use existing POKEY and TIA KiCad projects as chip-side references and verify their timing, current and audio levels on the new hardware. Speech and system chips need separate review for external ROM, sample streaming, or system timing.

This is a circuit architecture and proposed connector assignment. Component values, exact rail and clock designs, KiCad ERC, PCB layout and bench measurements are pending.
