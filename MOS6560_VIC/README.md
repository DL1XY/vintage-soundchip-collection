# MOS6560 (VIC)

<img src="MOS6561.png" width="600">	

<img src="kicad_MOS6561-101.png" width="600" height="400">

## General
The VIC (Video Interface Chip), specifically known as the MOS Technology 6560 (NTSC version) / 6561 (PAL version), is the integrated circuit chip responsible for generating video graphics and sound in the VIC-20 home computer from Commodore,

- Commodore VC20

DIP-40

## Channels
- 4 channel sound system
- 3 square wave
- "white" noise
- global volume setting

## Registers

| **Name** | **Address** | **B7** | **B6** | **B5** | **B4** | **B3** | **B2** | **B1** | **B0** | **Description**            |
|----------|-------------|--------|--------|--------|--------|--------|--------|--------|--------|----------------------------|
| CR0      | 00          | I      | SX6    | SX5    | SX4    | SX3    | SX2    | SX1    | SX0    | Screen Origin X            |
| CR1      | 01          | SY7    | SY6    | SY5    | SY4    | SY3    | SY2    | SY1    | SY0    | Screen Origin Y            |
| CR2      | 02          | Bv9    | M6     | M5     | M4     | M3     | M2     | M1     | M0     | No of Video Matrix Columns |
| CR3      | 03          | R0     | N5     | N4     | N3     | N2     | N1     | N0     | D      | No of Video Matrix Rows    |
| CR4      | 04          | R8     | R7     | R6     | R5     | R4     | R3     | R2     | R1     | Raster Value               |
| CR5      | 05          | BV13   | BV12   | BV11   | BV10   | BC13   | BC12   | BC11   | BC10   | Base Address Control       |
| CR6      | 06          | LH7    | LH6    | LH5    | LH4    | LH3    | LH2    | LH1    | LH0    | Light Pen Horizontal       |
| CR7      | 07          | LV7    | LV6    | LV5    | LV4    | LV3    | LV2    | LV1    | LV0    | Light Pen Vertical         |
| CR8      | 08          | PX7    | PX6    | PX5    | PX4    | PX3    | PX2    | PX1    | PX0    | POT X                      |
| CR9      | 09          | PY7    | PY6    | PY5    | PY4    | PY3    | PY2    | PY1    | PY0    | POT Y                      |
| CR10     | 0A          | S1     | F16    | F15    | F14    | F13    | F12    | F11    | F10    | FIN1                       |
| CR11     | 0B          | S2     | F26    | F25    | F24    | F23    | F22    | F21    | F20    | FIN2                       |
| CR12     | 0C          | S3     | F36    | F35    | F34    | F33    | F32    | F31    | F30    | FIN3                       |
| CR12     | 0D          | S4     | F46    | F45    | F44    | F43    | F42    | F41    | F40    | FIN4                       |
| CR14     | 0E          | CA3    | CA2    | CA1    | CA0    | A3     | A2     | A1     | A0     | Amplitude                  |
| CR15     | 0F          | CB3    | CB2    | CB1    | CB0    | R      | CE2    | CE1    | CE0    | Color Control              |


- **CR10**	Bits 0-6 set the frequency of the first audio oscillator. Bit 7 turns the oscillator on ( = 1) or off ( = 0)
- **CR11**	Same as CR10 for second audio oscillator
- **CR12**	Same as CR10 for third audio oscillator.
- **CR13**	Same as CR10, but sets frequency of noise source.
- **CR14**	Bits 0-3 set the volume of the composite audio signal (Note that at least one sound generator must be turned on for any sound to be produced). Bits 4-7 contain the Auxiliary color code used in conjunction with the “Multicolor” mode of operation.

## Links/Source
- [Area 51 DEV description of MOS6560](https://area51.dev/electronics/chipref/65/6560/)
- [Wikipedia](https://en.wikipedia.org/wiki/MOS_Technology_VIC)
