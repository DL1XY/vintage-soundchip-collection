# 8244/8245

<img src="8245.png" width="600">

#### General
The 8245 is a general purpose graphics display device that operates in conjunction with raster scan type displays. Its primary purpose is to provide a means for generating and moving objects on a TV screen for use in the customer game market.

- Magnavox Odyssey 2 (US)
- Philips Videopac G7000 (EU)

#### Sound System

The sound system generates a duty cycle modulated square wave from which an audio
signal is extracted by means of an external low pass filter. The control of the
duty cycle is effected by information that is transferred from the microprocessor
to the 8245. This information consists of triple byte groups that determine the
audio frequency and an accompanying 4 bits that determine volume.

The triple byte groups are loaded into three-eight bit shift registers located
on the 8245. Each byte in the group is loaded sequentially into its respective
register during a load interval. All three bytes are loaded in between conse
cutive shift clock pulses. The concatenation of the three registers results
in a 24 bit string that is shifted out by this shift clock. The resulting
serial pattern of ones and zeroes contains a fundamental band of frequency
components that lie in the audio range. This particular signal is further
“chopped” by a higher frequency that is a multiple of the shift clock. By
duty cycle modulation of this “chopping” signal, the amplitude of the audio
component is varied. There are four control bits that are used to control the
audio level. These bits are loaded into a four bit down counter that is shifted
by the high frequency shift clock. The resulting output is ANDED with the output
from the three concatenated shift registers to produce the composite audio output.
In addition to the four volume control bits, three other control bits are used
to augment the overall operation of the sound system. A noise enable bit enables
a feedback path in the output eight bit shift register, in the 25 bit shift path
to produce the noise component. Simultaneously, the noise is added to the audio
component that is progressing down the shift register.

The shift frequency for the register may be varied between two values by another
control bit. This expedient allows low audio frequencies to be produced with
fewer refresh cycles from the microprocessor than for high frequencies thus, 
reducing the load on the processor.

For the reproduction of certain audio tones that are subharmonically related to
the shift clock, the need for microprocessor refresh is totally eliminated by
recirculation of the 24 bit shift path.

The format of the sound control word is described below:

| 7  | 6 | 5 | 4 | 3  | 2  | 1  | 0  |
|----|---|---|---|----|----|----|----|
| EN | X | S | N | V3 | V2 | V1 | V0 |

Bits 0 – 3 – Volume Bits, collectively as a 4 bit word, these bits define the
output audio level.

Bit – 4 – Noise Enable; controls noise generation and mixing with the audio
signal. Bit 4 = 1, noise on; Bit = 0, noise off.

Bit 5 – Shift Frequency; determines frequency of shift clock.

Bit 5 = 1, f = 3933Hz. Bit 5 = 0, f = 983Hz.

Bit 7 – Enable sound; 0 = No sound, 1 = sound.

For those modes of operation requiring sound refresh data from the microprocessor,
an interrupt is generated each time that the 24 sound bits have been shifted through
the three eight bit shift registers. A 5 bit counter set to module 24 counts shift
clocks and determines when the interrupt should occur.

The sound shift registers, volume counter and sound control word register are all
individually addressed by the microprocessor for the purpose of loading data. The
address of these elements is shown under the topic of “Address Structure”.

$3933Hz = \frac{H}{4} = \frac{15,734}{4}$

$983Hz = \frac{H}{16} = \frac{15,734}{16}$

#### Links/Sources
- [Magnavox Odyssey 2 on Wikipedia](https://en.wikipedia.org/wiki/Magnavox_Odyssey_20)
