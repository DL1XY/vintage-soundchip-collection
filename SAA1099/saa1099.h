#ifndef SAA1099_H
#define SAA1099_H

#define SAA1099_REG_AMPLITUDE_CH_0      0x00
#define SAA1099_REG_AMPLITUDE_CH_1      0x01
#define SAA1099_REG_AMPLITUDE_CH_2      0x02
#define SAA1099_REG_AMPLITUDE_CH_3      0x03
#define SAA1099_REG_AMPLITUDE_CH_4      0x04
#define SAA1099_REG_AMPLITUDE_CH_5      0x05

#define SAA1099_REG_FREQ_CH_0           0x08
#define SAA1099_REG_FREQ_CH_1           0x09
#define SAA1099_REG_FREQ_CH_2           0x0A
#define SAA1099_REG_FREQ_CH_3           0x0B
#define SAA1099_REG_FREQ_CH_4           0x0C
#define SAA1099_REG_FREQ_CH_5           0x0D

#define SAA1099_REG_OCTAVE_CH_1_0       0x10
#define SAA1099_REG_OCTAVE_CH_3_2       0x11
#define SAA1099_REG_OCTAVE_CH_5_4       0x12

#define SAA1099_REG_FREQ_ENABLE         0x14
#define SAA1099_REG_NOISE_ENABLE        0x15
#define SAA1099_REG_NOISE_GENERATOR     0x16
#define SAA1099_REG_ENV0_GENERATOR      0x18
#define SAA1099_REG_ENV1_GENERATOR      0x19
#define SAA1099_REG_RST_SE              0x1C

struct SAA1099_AUDIO_REGISTER_VALUES
{
     unsigned int amplitude0_left:      4;
     unsigned int amplitude0_right:     4;
     unsigned int amplitude1_left:      4;
     unsigned int amplitude1_right:     4;
     unsigned int amplitude2_left:      4;
     unsigned int amplitude2_right:     4;
     unsigned int amplitude3_left:      4;
     unsigned int amplitude3_right:     4;
     unsigned int amplitude4_left:      4;
     unsigned int amplitude4_right:     4;
     unsigned int amplitude5_left:      4;
     unsigned int amplitude5_right:     4;

     unsigned int frequency0:           8;
     unsigned int frequency1:           8;
     unsigned int frequency2:           8;
     unsigned int frequency3:           8;
     unsigned int frequency4:           8;
     unsigned int frequency5:           8;

     unsigned int octave0:              3;
     unsigned int octave1:              3;
     unsigned int octave2:              3;
     unsigned int octave3:              3;
     unsigned int octave4:              3;
     unsigned int octave5:              3;

     unsigned int frequencyEnabled:     6;
     unsigned int noiseEnabled:         6;

     unsigned int noiseGenerator0:      2;
     unsigned int noiseGenerator1:      2;

     unsigned int envelopeGenerator0:   7;
     unsigned int envelopeGenerator1:   7;

     unsigned int freqencyReset:        2;
};

#endif // SAA1099_H
