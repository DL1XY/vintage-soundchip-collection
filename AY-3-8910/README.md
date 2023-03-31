# AY-3-8910

<img src="AY-3-8910.png" width="600">

<img src="kicad_Yamaha_YM2149.png" width="600" height="400">

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
