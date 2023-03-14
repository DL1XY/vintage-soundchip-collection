#ifndef ATARI_TIA_H
#define ATARI_TIA_H
/*
 
 	 	 
 	 	     ATARI TIA
     -------------------------
  1 -| Vss				  I0 |- 40
  2 -| SYNC				  I1 |- 39
  3 -| ~RDY				  I2 |- 38
  4 -| 0O				  I3 |- 37
  5 -| LUM1				  I4 |- 36
  6 -| BLK				  I5 |- 35
  7 -| LUM2				  D6 |- 34
  8 -| LUM0				  D7 |- 33
  9 -| COL				  A0 |- 32
 10 -| DEL				  A1 |- 31
 11 -| OSC				  A2 |- 30
 12 -| AUD0				  A3 |- 29
 13 -| AUD1				  A4 |- 28
 14 -| D0				  A5 |- 27
 15 -| D1				  02 |- 26
 16 -| D2				R/~W |- 25
 17 -| D3				~CS0 |- 24
 18 -| D4				 CS1 |- 23
 19 -| D5				~CS2 |- 22
 20 -| Vcc 				~CS3 |- 21
     -------------------------
     
 */

/* AUDC0/1 Commands
 *
 * HEX	D7	D6	D5	D4	D3	D2	D1	D0	Type of noise or division
 * 0                    0	0	0	0	Set to 1 (volume only)
 * 1                    0	0	0	1	4 bit poly
 * 2                    0	0	1	0	÷ 15 -> 4 bit poly
 * 3                    0	0	1	1	5 bit poly -> 4 bit poly
 * 4                    0	1	0	0	÷ 2
 * 5                    0	1	0	1	÷ 2
 * 6                    0	1	1	0	÷ 31
 * 7                    0	1	1	1	5 bit poly -> ÷ 2
 * 8                    1	0	0	0	9-bit poly (white noise)
 * 9                    1	0	0	1	5-bit poly
 * A                    1	0	1	0	÷ 31
 * B                    1	0	1	1	Set last 4 bits to 1
 * C                    1	1	0	0	÷ 6
 * D                    1	1	0	1	÷ 6
 * E                    1	1	1	0	÷ 93
 * F                    1	1	1	1	5-bit poly ÷ 6
 *
*/
#define ATARI_TIA_AUDC_VOL_1						0x0
#define ATARI_TIA_AUDC_4BIT_POLY					0x1
#define ATARI_TIA_AUDC_DIV_15_TO_4BIT_POLY   		0x2
#define ATARI_TIA_AUDC_5BIT_POLY_TO_4BIT_POLY    	0x3
#define ATARI_TIA_AUDC_DIV_2						0x4
#define ATARI_TIA_AUDC_DIV_2_2  					0x5
#define ATARI_TIA_AUDC_DIV_31						0x6
#define ATARI_TIA_AUDC_5BIT_POLY_TO_DIV_2			0x7
#define ATARI_TIA_AUDC_9BIT_POLY					0x8
#define ATARI_TIA_AUDC_5BIT_POLY					0x9
#define ATARI_TIA_AUDC_DIV_31_2 					0xA
#define ATARI_TIA_AUDC_LAST_4BITS_1 				0xB
#define ATARI_TIA_AUDC_DIV_6						0xC
#define ATARI_TIA_AUDC_DIV_6_2  					0xD
#define ATARI_TIA_AUDC_DIV_93						0xE
#define ATARI_TIA_AUDC_5BIT_POLY_TO_DIV_6			0xF

/* Strings representing AUDC status */
const char* ATARI_TIA_AUDC_Descriptions[] = 
{
    "VOL1", 					// 0x0;
    "4BIT_POLY", 				// 0x1;
    "DIV_15_TO_4BIT_POLY",		// 0x2;
    "5BIT_POLY_TO_4BIT_POLY",   // 0x3;
    "DIV_2",                    // 0x4;
    "DIV_2_2",                  // 0x5;
    "DIV_31",                   // 0x6;
    "5BIT_POLY_TO_DIV_2",       // 0x7;
    "9BIT_POLY",                // 0x8;
    "5BIT_POLY",                // 0x9;
    "DIV_31_2",                 // 0xA;
    "LAST_4BITS_1",             // 0xB;
    "DIV_6",                    // 0xC;
    "DIV_6_2",                  // 0xD;
    "DIV_93",                   // 0xE;
    "5BIT_POLY_TO_DIV_6"        // 0xF;
	
};

/* Struct to define TIA audio registers */
typedef struct atari_tia_audio_registers_t
{
    unsigned int aud0_volume:    4;
    unsigned int aud0_freq_div:  5;
    unsigned int aud0_control:   4;

    unsigned int aud1_volume:    4;
    unsigned int aud1_freq_div:  5;
    unsigned int aud1_control:   4;
} atari_tia_audio_registers;


/* Register constraints */
#define ATARI_TIA_MAX_VOLUME      0xF;
#define ATARI_TIA_MAX_FREQ_DIV    0x1F;
#define ATARI_TIA_MAX_CONTROL     0xF;


#endif // ATARI_TIA_H
