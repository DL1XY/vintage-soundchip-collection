#ifndef SN76489_H
#define SN76489_H

/*
 * 				SN 76489 AN
         ------------------------  
 	  1 -| D2				Vcc |- 16
 	  2 -| D1				 D3 |- 15
 	  3 -| D0			  CLOCK |- 14
 	  4 -| READY			 D4 |- 13
 	  5 -| ~WE				 D5 |- 12
 	  6 -| ~OE				 D6 |- 11	
 	  7 -| AUDIO OUT		 D7 |- 10
 	  8 -| GND 	   	   	   N.C. |- 9
 	     ------------------------  
 */

#define SN76489_REG_TONE_1_FREQUENCY    0b000;
#define SN76489_REG_TONE_1_ATTENUATION  0b001;
#define SN76489_REG_TONE_2_FREQUENCY    0b010;
#define SN76489_REG_TONE_2_ATTENUATION  0b011;
#define SN76489_REG_TONE_3_FREQUENCY    0b100;
#define SN76489_REG_TONE_3_ATTENUATION  0b101;
#define SN76489_REG_NOISE_CONTROL       0b110;
#define SN76489_REG_NOISE_ATTENUATION   0b111;

struct SN76489_AUDIO_REGISTER_VALUES
{
    unsigned int tone_1_frequency:          10;
    unsigned int tone_1_attenuation:        4;
    unsigned int tone_2_frequency:          10;
    unsigned int tone_2_attenuation:        4;
    unsigned int tone_3_frequency:          10;
    unsigned int tone_3_attenuation:        4;
    unsigned int noise_feedback:            1;
    unsigned int noise_frequency_src:       2;
    unsigned int noise_attenuation:         4;
};

#endif // SN76489_H
