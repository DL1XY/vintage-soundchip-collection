# 8 Bit Sound Chips
This is my personal collection of 8 Bit sound chips. I put some information together like datasheets etc., maybe it's useful for someone.

## KiCAD 7.x Symbols
[8_bit_soundchips.kicad_sym](8_bit_soundchips.kicad_sym) contains some KiCAD symbols you can use for your own circuits.

## Chips

### [AY-3-8910](AY-3-8910)

<img src="AY-3-8910/YM2149F.png" width="600" height="400">

<img src="AY-3-8910/kicad_Yamaha_YM2149.png" width="600" height="400">

#### General

- Vectrex
- Amstrad CPC
- ZX Spectrum

Other versions: YM2149 (used in Atari ST)

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

- Noise pitch from 1 to 31.
- Envelope. You can enable attack (volume up from 0 to 15) and/or decay (volume down from 15 to 0), at the end optionally reversed and/or looped. However, you can only choose one speed for both, and all channels get the same envelope. Due to those limits, many people generated envelopes themselves in software and set all three volumes manually.

Changing a volume produces a click; the greater the change, the louder. This allows to play unsigned 4-bit PCM samples. Changing all three volumes even allows 8-bit on mono. On stereo, 8-bit samples hiss loudly.

#### Links/Sources
- [AY-3-8910 at Video Game Music Preservation Foundation](http://www.vgmpf.com/Wiki/index.php/AY-3-8910)
- [Wikipedia](https://en.wikipedia.org/wiki/General_Instrument_AY-3-8910)

### [CO10444 (TIA)](CO10444_TIA)

<img src="CO10444_TIA/UM6526P1.png" width="600" height="400">

<img src="CO10444_TIA/kicad_Atari_TIA_CO11903.png" width="600" height="400">

#### General
- Atari 2600

Other names: UM6526, UM6532, VF4013, CO11903, E4002

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Television_Interface_Adaptor)

### [CO12294 (POKEY)](CO12294_POKEY)

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

### [MOS 6560 (VIC)](MOS6560_VIC)

<img src="MOS6560_VIC/MOS6561-101.png" width="600" height="400">	

<img src="MOS6560_VIC/kicad_MOS6561-101.png" width="600" height="400">

#### General
- Commodore VC20

Other names: MOS6561-101

#### Links/Source
- [Wikipedia](https://en.wikipedia.org/wiki/MOS_Technology_VIC)

### [MOS 6581 (SID)](MOS6581_SID)

<img src="MOS6581_SID/MOS6581.png" width="600" height="400">

<img src="MOS6581_SID/kicad_6581_SID.png" width="600" height="400">

#### General
- Commodore C64
- Commodore C128

One of the most famous 8-bit sound chips. Many DIY and commercial synthesizer projects are builded around this chip.

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/MOS_Technology_6581)
- [MIDIbox SID V2](http://www.ucapps.de/index.html?page=midibox_sid.html)
- [Elektron SIDStation](https://www.elektron.se/en/legacy)

### [MOS 8360 (TED)](MOS8360_TED)

<img src="MOS8360_TED/MOS8360R2.png" width="600" height="400">

#### General
- Commodore C16
- Commodore C116
- Commodore Plus/4

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/MOS_Technology_TED)

### [MOS 8364 (PAULA)](MOS8364_PAULA)

<img src="MOS8364_PAULA/MOS8364R7.png" width="600" height="400">

#### General
- Commodore Amiga 500/1000/2000/CDTV

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Original_Chip_Set#Paula)

### [SAA1099](SAA1099)

<img src="SAA1099/SAA1099P.png" width="600" height="400">

<img src="SAA1099/kicad_SAA1099.png" width="600" height="400">

#### General
- Soundblaster 1.0
- SAM Coupé
- some Silicon Graphics boards

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Philips_SAA1099)

### [SN76489](SN76489)

<img src="SN76489/SN76489AN.png" width="600" height="400">

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

### [SP0256A-AL2](SP0256A-AL2)

<img src="SP0256A-AL2/SP0256A-AL2.png" width="600" height="400">

#### General
Speech synthesis, avalaible as cartridge for

- Commodore VC20
- Atari 8-bit family
- TRS-80

DIL-28

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/General_Instrument_SP0256)

### [YM2151](YM2151)

<img src="YM2151/YM2151.png" width="600" height="400">

#### General

- Arcade systems (Sega, Konami, Capcom, ...)

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Yamaha_YM2151)

### [YM2203](YM2203)

<img src="YM2203/YM2203C.png" width="600" height="400">

#### General
- Arcade systems

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Yamaha_YM2203)

### [YM2413](YM2413)

<img src="YM2413/YM2413.png" width="600" height="400">

#### General
FM synthesis

- Arcade systems (Sega, SNK, Atari, ...)
- Keyboards

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Yamaha_OPL#OPL2)

### [YM2610](YM2610)

<img src="YM2610/YM2610.png" width="600" height="400">

#### General
- SNK Neo Geo

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Yamaha_YM2610)

## [YM3812](YM3812)

<img src="YM3812/YM3812.png" width="600" height="400">

<img src="YM3812/kicad_Yamaha_YM3812.png" width="600" height="400">

#### General
FM synthesis

- Synthesizers

#### Links/Sources
- [Wikipedia](https://en.wikipedia.org/wiki/Yamaha_OPL#OPL2)
