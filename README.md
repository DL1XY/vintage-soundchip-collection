# 8 Bit Sound Chips
This is my personal collection of 8 Bit sound chips. I put some information together like datasheets etc., maybe it's useful for someone.


* [KiCAD 7.x Symbols](#kicad-7x-symbols)
* [Chips](#chips)
  + [AY-3-8910](#AY-3-8910)   
  + [CO10444 TIA](#CO10444)   
  + [CO12294 POKEY](#CO12294)
  + [MOS 6560 VIC](#MOS6560)
  + [MOS 6581 SID](#MOS6581)
  + [MOS 7360/8360 TED](#MOS8360)
  + [MOS 8364 PAULA](#MOS8364)
  + [SAA1099](#SAA1099)
  + [SN76489](#SN76489)
  + [SP0256A](#SP0256A)
  + [YM2151](#YM2151)
  + [YM2203](#YM2203)
  + [YM2413](#YM2413)
  + [YM2610](#YM2610)
  + [YM3812](#YM3812)


## KiCAD 7.x Symbols
[8_bit_soundchips.kicad_sym](8_bit_soundchips.kicad_sym) contains some KiCAD symbols you can use for your own circuits.

## Chips

<a name="AY-3-8910"></a>
### [AY-3-8910](AY-3-8910)

<img src="AY-3-8910/AY-3-8910.png" width="600">

<img src="AY-3-8910/kicad_Yamaha_YM2149.png" width="600" height="400">

#### General

- Vectrex
- Amstrad CPC
- ZX Spectrum

Other versions: YM2149 (used in Atari ST), YMZ284 (DIP-16)

Differences between AY and YM are listed [here](https://maidavale.org/blog/ay-ym-differences/)

DIP-40

#### Channels

The noise does not have its own channel, but is optionally mixed into any combination of square wave channels. Consequently, all noises share the same pitch, and each noise shares the volume of the square wave it accompanies or replaces. Some arrangers have mixed short noise drums over a square wave bass.

On each of channels A, B and C, you can choose:

- Whether a square wave plays.
- Whether the single white noise plays.
- Square wave pitch from 1 to 4095. The highest possible frequency is the sound chip's clock frequency divided by 16. Further divided by 4095, it equals the minimum frequency.
- Volume, either from 0 to 15, or fed by the single envelope generator.

On the whole chip, you can choose:

- **Noise pitch** from 1 to 31.
- **Envelope**. You can enable attack (volume up from 0 to 15) and/or decay (volume down from 15 to 0), at the end optionally reversed and/or looped. However, you can only choose one speed for both, and all channels get the same envelope. Due to those limits, many people generated envelopes themselves in software and set all three volumes manually.

Changing a volume produces a click; the greater the change, the louder. This allows to play unsigned 4-bit PCM samples. Changing all three volumes even allows 8-bit on mono. On stereo, 8-bit samples hiss loudly.

#### Links/Sources
- [AY-3-8910 at VGMPF](http://www.vgmpf.com/Wiki/index.php/AY-3-8910)
- [Wikipedia](https://en.wikipedia.org/wiki/General_Instrument_AY-3-8910)

<a name="CO10444"></a>
### [CO10444 TIA](CO10444_TIA)

<img src="CO10444_TIA/UM6526P1.png" width="600" height="400">

<img src="CO10444_TIA/kicad_Atari_TIA_CO11903.png" width="600" height="400">

#### General
- Atari 2600

Other names: UM6526, UM6532, VF4013, CO11903, E4002

#### Channels
On each of two channels AUD0/1, you can choose:

- **Waveform**: 50% or 58% pulse wave, 4 other waves, or white noise.
- **Pitch**: Range dependent on waveform.
- **Volume** from 0 to 15.

The TIA can produce PCM music, but it takes a lot of RAM (while Atari 2600 doesn't have much), usually forcing developers to use it with static images or completely black screen. It seems there weren't any official games to ever utilize the PCM music or speech.

Each oscillator has a 5-bit frequency divider and a 4-bit audio control register which manipulates the waveform. There is also a 4-bit volume control register per channel.

##### Frequency Divider (AUDF0/1)
Frequencies are generated by taking 30 kHz and dividing by the 5-bit value supplied. The result is a cheap frequency divider capable of detuned notes and the odd tuned frequency. The TIA is not a musical chip unless the composer works within the frequency limits or modulates between two detuned frequencies to create a vibrato tuned note.

##### Audio Control (AUDC0/1)
The Audio Control register generates and manipulates a pulse wave to create complex pulses or noise. The following table (with designed duplicates) explains how its tones are generated:

| HEX | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | Type of noise or division |
|-----|----|----|----|----|----|----|----|----|---------------------------|
| 0   |    |    |    |    | 0  | 0  | 0  | 0  | Set to 1 (volume only)    |
| 1   |    |    |    |    | 0  | 0  | 0  | 1  | 4 bit poly                |
| 2   |    |    |    |    | 0  | 0  | 1  | 0  | div 15 → 4 bit poly       |
| 3   |    |    |    |    | 0  | 0  | 1  | 1  | 5 bit poly → 4 bit poly   |
| 4   |    |    |    |    | 0  | 1  | 0  | 0  | div 2                     |
| 5   |    |    |    |    | 0  | 1  | 0  | 1  | div 2                     |
| 6   |    |    |    |    | 0  | 1  | 1  | 0  | div 31                    |
| 7   |    |    |    |    | 0  | 1  | 1  | 1  | 5 bit poly → div 2        |
| 8   |    |    |    |    | 1  | 0  | 0  | 0  | 9-bit poly (white noise)  |
| 9   |    |    |    |    | 1  | 0  | 0  | 1  | 5-bit poly                |
| A   |    |    |    |    | 1  | 0  | 1  | 0  | div 31                    |
| B   |    |    |    |    | 1  | 0  | 1  | 1  | Set last 4 bits to 1      |
| C   |    |    |    |    | 1  | 1  | 0  | 0  | div 6                     |
| D   |    |    |    |    | 1  | 1  | 0  | 1  | div 6                     |
| E   |    |    |    |    | 1  | 1  | 1  | 0  | div 93                    |
| F   |    |    |    |    | 1  | 1  | 1  | 1  | 5-bit poly div 6          |


#### Links/Sources
- [TIA at VGMPF](http://www.vgmpf.com/Wiki/index.php?title=Television_Interface_Adaptor)
- [Wikipedia](https://en.wikipedia.org/wiki/Television_Interface_Adaptor)

<a name="CO12294"></a>
### [CO12294 POKEY](CO12294_POKEY)

<img src="CO12294_POKEY/CO12294.png" width="600" height="400">	

<img src="CO12294_POKEY/kicad_Atari_POKEY_C012294.png" width="600" height="400">

#### General
- Atari 400/800
- Atari XL/XE
- later Atari 5200
- Atari 7800 game cartridges (Ballblazer and Commando)
- Atari arcade systems

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/POKEY)

<a name="MOS6560"></a>
### [MOS 6560/6561 VIC](MOS6560_VIC)

<img src="MOS6560_VIC/MOS6561.png" width="600">	

<img src="MOS6560_VIC/kicad_MOS6561-101.png" width="600" height="400">

#### General
The VIC (Video Interface Chip), specifically known as the MOS Technology 6560 (NTSC version) / 6561 (PAL version), is the integrated circuit chip responsible for generating video graphics and sound in the VIC-20 home computer from Commodore,

- Commodore VC20

DIP-40

#### Channels
- 4 channel sound system
- 3 square wave
- "white" noise
- global volume setting

#### Registers

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

#### Links/Source
- [Area 51 DEV description of MOS6560](https://area51.dev/electronics/chipref/65/6560/)
- [Wikipedia](https://en.wikipedia.org/wiki/MOS_Technology_VIC)

<a name="MOS6581"></a>
### [MOS 6581 SID](MOS6581_SID)

<img src="MOS6581_SID/MOS6581_2.png" width="600">

<img src="MOS6581_SID/kicad_6581_SID.png" width="600" height="400">

#### General
- Commodore C64
- Commodore C128

One of the most famous 8-bit sound chips. Many DIY and commercial synthesizer projects are builded around this chip.

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/MOS_Technology_6581)
- [MIDIbox SID V2](http://www.ucapps.de/index.html?page=midibox_sid.html)
- [Elektron SIDStation](https://www.elektron.se/en/legacy)

<a name="MOS8360"></a>
### [MOS 7360/8360 TED](MOS8360_TED)

<img src="MOS8360_TED/MOS8360.png" width="600">

#### General
- Commodore C16
- Commodore C116
- Commodore Plus/4

#### Channels
On each of two channels, you can choose a pitch in 1024 steps. Compared to the VIC, high notes are in tune, but the bass does not get below A2 (110 Hz). Low noise actually sounds like noise, although you may notice a pattern as it gets higher.

For both channels together, you can only choose one volume, from 0 to 8. Changing this volume, while either channel is on, produces a click; the greater the change, the louder. This allows to play unsigned PCM samples on a third channel.

Several games play only one melody with a chorus effect (using two slightly detuned channels). Very few drivers generate envelopes.

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/MOS_Technology_TED)

<a name="MOS8364"></a>
### [MOS 8364 (PAULA)](MOS8364_PAULA)

<img src="MOS8364_PAULA/MOS8364.png" width="600">

#### General
- Commodore Amiga 500/1000/2000/CDTV

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Original_Chip_Set#Paula)

<a name="SAA1099"></a>
### [SAA1099](SAA1099)

<img src="SAA1099/SAA1099.png" width="600">

<img src="SAA1099/kicad_SAA1099.png" width="600" height="400">

#### General
- Soundblaster 1.0
- SAM Coupé
- some Silicon Graphics boards

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Philips_SAA1099)

<a name="SN76489"></a>
### [SN76489](SN76489)

<img src="SN76489/SN76489AN.png" width="600">

<img src="SN76489/kicad_SN76489.png" width="600" height="400">

#### General
- TI 99/4A
- ColecoVision
- BBC Micro
- Tandy 1000
- Sega SG-1000 

Clones where integrated in the vedio display processor of

- Sega Master System/Game Gear/Genesis

Other names: SN76496N

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Texas_Instruments_SN76489)

<a name="SP0256A"></a>
### [SP0256A](SP0256A-AL2)

<img src="SP0256A-AL2/SP0256A_FAKE.png" width="600">

#### General
Speech synthesis, avalaible as cartridge for

- Commodore VC20
- Atari 8-bit family
- TRS-80

DIP-28

**Attention**: There are a lot of fake chips around ! I bought one from the Bay and seems to be just a cheap rebrandend DIP-28 IC !

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/General_Instrument_SP0256)

<a name="YM2151"></a>
### [YM2151](YM2151)

<img src="YM2151/YM2151_2.png" width="600">

#### General

- Arcade systems (Sega, Konami, Capcom, ...)

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Yamaha_YM2151)

<a name="YM2203"></a>
### [YM2203](YM2203)

<img src="YM2203/YM2203.png" width="600">

#### General
- Arcade systems

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Yamaha_YM2203)

<a name="YM2413"></a>
### [YM2413](YM2413)

<img src="YM2413/YM2413_2.png" width="600">

#### General
FM synthesis

- Arcade systems (Sega, SNK, Atari, ...)
- Keyboards

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Yamaha_OPL#OPL2)

<a name="YM2610"></a>
### [YM2610](YM2610)

<img src="YM2610/YM2610_2.png" width="600">

#### General
- SNK Neo Geo

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Yamaha_YM2610)

<a name="YM3812"></a>
## [YM3812](YM3812)

<img src="YM3812/YM3812_2.png" width="600">

<img src="YM3812/kicad_Yamaha_YM3812.png" width="600" height="400">

#### General
FM synthesis

- Synthesizers

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Yamaha_OPL#OPL2)
