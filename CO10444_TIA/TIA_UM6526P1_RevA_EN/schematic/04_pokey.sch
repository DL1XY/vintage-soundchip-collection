EESchema Schematic File Version 4
LIBS:TIA-cache
EELAYER 29 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 5 7
Title "04 / UM6526P1 PAL-family socket"
Date "2026-10-25"
Rev "A - document-reviewed design"
Comp "TIA / ESP32"
Comment1 "No hardware test; see documentation and commissioning procedure"
$EndDescr
Text Notes 700 600 0 110 ~ 12
04 / UM6526P1 PAL-family socket
Text Notes 700 900 0 75 ~ 0
PAL reference: Atari C011903 family / user confirmed UM6526P1 / no standalone UMC electrical datasheet located
$Comp
L TIA:U1_SYM U1
U 1 1 05000011
P 3400 5000
F 0 "U1" H 3400 1670 85 0000 C CNN
F 1 "UM6526P1 / PAL TIA / DIP-40" H 3400 1800 80 0000 C CNN
F 2 "" H 3400 5000 50 0001 C CNN
F 3 "" H 3400 5000 50 0001 C CNN
	1 3400 5000
	1 0 0 -1
$EndComp
Wire Wire Line
	2000 2150 1600 2150
Text GLabel 1600 2150 2 65 BiDi ~ 0
GND
NoConn ~ 2000 2450
NoConn ~ 2000 2750
Wire Wire Line
	2000 3050 1600 3050
Text GLabel 1600 3050 2 65 BiDi ~ 0
PHI0
NoConn ~ 2000 3350
NoConn ~ 2000 3650
NoConn ~ 2000 3950
Wire Wire Line
	2000 4250 1600 4250
Text GLabel 1600 4250 2 65 BiDi ~ 0
PAL_AUX8
NoConn ~ 2000 4550
Wire Wire Line
	2000 4850 1600 4850
Text GLabel 1600 4850 2 65 BiDi ~ 0
DEL_UNUSED
Wire Wire Line
	2000 5150 1600 5150
Text GLabel 1600 5150 2 65 BiDi ~ 0
TIA_OSC
Wire Wire Line
	2000 5450 1600 5450
Text GLabel 1600 5450 2 65 BiDi ~ 0
TIA12
Wire Wire Line
	2000 5750 1600 5750
Text GLabel 1600 5750 2 65 BiDi ~ 0
AUD_RAW
Wire Wire Line
	2000 6050 1600 6050
Text GLabel 1600 6050 2 65 BiDi ~ 0
D0
Wire Wire Line
	2000 6350 1600 6350
Text GLabel 1600 6350 2 65 BiDi ~ 0
D1
Wire Wire Line
	2000 6650 1600 6650
Text GLabel 1600 6650 2 65 BiDi ~ 0
D2
Wire Wire Line
	2000 6950 1600 6950
Text GLabel 1600 6950 2 65 BiDi ~ 0
D3
Wire Wire Line
	2000 7250 1600 7250
Text GLabel 1600 7250 2 65 BiDi ~ 0
D4
Wire Wire Line
	2000 7550 1600 7550
Text GLabel 1600 7550 2 65 BiDi ~ 0
D5
Wire Wire Line
	2000 7850 1600 7850
Text GLabel 1600 7850 2 65 BiDi ~ 0
5V
Wire Wire Line
	4800 2150 5200 2150
Text GLabel 5200 2150 0 65 BiDi ~ 0
GND
Wire Wire Line
	4800 2450 5200 2450
Text GLabel 5200 2450 0 65 BiDi ~ 0
GND
Wire Wire Line
	4800 2750 5200 2750
Text GLabel 5200 2750 0 65 BiDi ~ 0
CS1
Wire Wire Line
	4800 3050 5200 3050
Text GLabel 5200 3050 0 65 BiDi ~ 0
CS0_N
Wire Wire Line
	4800 3350 5200 3350
Text GLabel 5200 3350 0 65 BiDi ~ 0
GND
Wire Wire Line
	4800 3650 5200 3650
Text GLabel 5200 3650 0 65 BiDi ~ 0
PHI2
Wire Wire Line
	4800 3950 5200 3950
Text GLabel 5200 3950 0 65 BiDi ~ 0
GND
Wire Wire Line
	4800 4250 5200 4250
Text GLabel 5200 4250 0 65 BiDi ~ 0
A4
Wire Wire Line
	4800 4550 5200 4550
Text GLabel 5200 4550 0 65 BiDi ~ 0
A3
Wire Wire Line
	4800 4850 5200 4850
Text GLabel 5200 4850 0 65 BiDi ~ 0
A2
Wire Wire Line
	4800 5150 5200 5150
Text GLabel 5200 5150 0 65 BiDi ~ 0
A1
Wire Wire Line
	4800 5450 5200 5450
Text GLabel 5200 5450 0 65 BiDi ~ 0
A0
Wire Wire Line
	4800 5750 5200 5750
Text GLabel 5200 5750 0 65 BiDi ~ 0
D7
Wire Wire Line
	4800 6050 5200 6050
Text GLabel 5200 6050 0 65 BiDi ~ 0
D6
Wire Wire Line
	4800 6350 5200 6350
Text GLabel 5200 6350 0 65 BiDi ~ 0
I5
Wire Wire Line
	4800 6650 5200 6650
Text GLabel 5200 6650 0 65 BiDi ~ 0
I4
Wire Wire Line
	4800 6950 5200 6950
Text GLabel 5200 6950 0 65 BiDi ~ 0
I3
Wire Wire Line
	4800 7250 5200 7250
Text GLabel 5200 7250 0 65 BiDi ~ 0
I2
Wire Wire Line
	4800 7550 5200 7550
Text GLabel 5200 7550 0 65 BiDi ~ 0
I1
Wire Wire Line
	4800 7850 5200 7850
Text GLabel 5200 7850 0 65 BiDi ~ 0
I0
$Comp
L TIA:C16_SYM C16
U 1 1 050000AA
P 9200 2000
F 0 "C16" H 9200 1770 85 0000 C CNN
F 1 "100n X7R 10V" H 9200 1900 80 0000 C CNN
F 2 "" H 9200 2000 50 0001 C CNN
F 3 "" H 9200 2000 50 0001 C CNN
	1 9200 2000
	1 0 0 -1
$EndComp
Wire Wire Line
	8700 2000 8300 2000
Text GLabel 8300 2000 2 65 BiDi ~ 0
5V
Wire Wire Line
	9700 2000 10100 2000
Text GLabel 10100 2000 0 65 BiDi ~ 0
GND
$Comp
L TIA:C17_SYM C17
U 1 1 050000BD
P 13900 2000
F 0 "C17" H 13900 1770 85 0000 C CNN
F 1 "10u X7R 10V" H 13900 1900 80 0000 C CNN
F 2 "" H 13900 2000 50 0001 C CNN
F 3 "" H 13900 2000 50 0001 C CNN
	1 13900 2000
	1 0 0 -1
$EndComp
Wire Wire Line
	13400 2000 13000 2000
Text GLabel 13000 2000 2 65 BiDi ~ 0
5V
Wire Wire Line
	14400 2000 14800 2000
Text GLabel 14800 2000 0 65 BiDi ~ 0
GND
$Comp
L TIA:R12_SYM R12
U 1 1 050000D0
P 9200 2950
F 0 "R12" H 9200 2720 85 0000 C CNN
F 1 "1k 1%" H 9200 2850 80 0000 C CNN
F 2 "" H 9200 2950 50 0001 C CNN
F 3 "" H 9200 2950 50 0001 C CNN
	1 9200 2950
	1 0 0 -1
$EndComp
Wire Wire Line
	8700 2950 8300 2950
Text GLabel 8300 2950 2 65 BiDi ~ 0
5V
Wire Wire Line
	9700 2950 10100 2950
Text GLabel 10100 2950 0 65 BiDi ~ 0
AUD_RAW
$Comp
L TIA:R13_SYM R13
U 1 1 050000E3
P 13900 2950
F 0 "R13" H 13900 2720 85 0000 C CNN
F 1 "100k" H 13900 2850 80 0000 C CNN
F 2 "" H 13900 2950 50 0001 C CNN
F 3 "" H 13900 2950 50 0001 C CNN
	1 13900 2950
	1 0 0 -1
$EndComp
Wire Wire Line
	13400 2950 13000 2950
Text GLabel 13000 2950 2 65 BiDi ~ 0
I0
Wire Wire Line
	14400 2950 14800 2950
Text GLabel 14800 2950 0 65 BiDi ~ 0
GND
$Comp
L TIA:R14_SYM R14
U 1 1 050000F6
P 9200 3900
F 0 "R14" H 9200 3670 85 0000 C CNN
F 1 "100k" H 9200 3800 80 0000 C CNN
F 2 "" H 9200 3900 50 0001 C CNN
F 3 "" H 9200 3900 50 0001 C CNN
	1 9200 3900
	1 0 0 -1
$EndComp
Wire Wire Line
	8700 3900 8300 3900
Text GLabel 8300 3900 2 65 BiDi ~ 0
I1
Wire Wire Line
	9700 3900 10100 3900
Text GLabel 10100 3900 0 65 BiDi ~ 0
GND
$Comp
L TIA:R15_SYM R15
U 1 1 05000109
P 13900 3900
F 0 "R15" H 13900 3670 85 0000 C CNN
F 1 "100k" H 13900 3800 80 0000 C CNN
F 2 "" H 13900 3900 50 0001 C CNN
F 3 "" H 13900 3900 50 0001 C CNN
	1 13900 3900
	1 0 0 -1
$EndComp
Wire Wire Line
	13400 3900 13000 3900
Text GLabel 13000 3900 2 65 BiDi ~ 0
I2
Wire Wire Line
	14400 3900 14800 3900
Text GLabel 14800 3900 0 65 BiDi ~ 0
GND
$Comp
L TIA:R16_SYM R16
U 1 1 0500011C
P 9200 4850
F 0 "R16" H 9200 4620 85 0000 C CNN
F 1 "100k" H 9200 4750 80 0000 C CNN
F 2 "" H 9200 4850 50 0001 C CNN
F 3 "" H 9200 4850 50 0001 C CNN
	1 9200 4850
	1 0 0 -1
$EndComp
Wire Wire Line
	8700 4850 8300 4850
Text GLabel 8300 4850 2 65 BiDi ~ 0
I3
Wire Wire Line
	9700 4850 10100 4850
Text GLabel 10100 4850 0 65 BiDi ~ 0
GND
$Comp
L TIA:R17_SYM R17
U 1 1 0500012F
P 13900 4850
F 0 "R17" H 13900 4620 85 0000 C CNN
F 1 "100k" H 13900 4750 80 0000 C CNN
F 2 "" H 13900 4850 50 0001 C CNN
F 3 "" H 13900 4850 50 0001 C CNN
	1 13900 4850
	1 0 0 -1
$EndComp
Wire Wire Line
	13400 4850 13000 4850
Text GLabel 13000 4850 2 65 BiDi ~ 0
DEL_UNUSED
Wire Wire Line
	14400 4850 14800 4850
Text GLabel 14800 4850 0 65 BiDi ~ 0
GND
$Comp
L TIA:R18_SYM R18
U 1 1 05000142
P 9200 5800
F 0 "R18" H 9200 5570 85 0000 C CNN
F 1 "100k" H 9200 5700 80 0000 C CNN
F 2 "" H 9200 5800 50 0001 C CNN
F 3 "" H 9200 5800 50 0001 C CNN
	1 9200 5800
	1 0 0 -1
$EndComp
Wire Wire Line
	8700 5800 8300 5800
Text GLabel 8300 5800 2 65 BiDi ~ 0
PAL_AUX8
Wire Wire Line
	9700 5800 10100 5800
Text GLabel 10100 5800 0 65 BiDi ~ 0
GND
$Comp
L TIA:R21_SYM R21
U 1 1 05000155
P 13900 5800
F 0 "R21" H 13900 5570 85 0000 C CNN
F 1 "10k" H 13900 5700 80 0000 C CNN
F 2 "" H 13900 5800 50 0001 C CNN
F 3 "" H 13900 5800 50 0001 C CNN
	1 13900 5800
	1 0 0 -1
$EndComp
Wire Wire Line
	13400 5800 13000 5800
Text GLabel 13000 5800 2 65 BiDi ~ 0
5V
Wire Wire Line
	14400 5800 14800 5800
Text GLabel 14800 5800 0 65 BiDi ~ 0
I4
$Comp
L TIA:R22_SYM R22
U 1 1 05000168
P 9200 6750
F 0 "R22" H 9200 6520 85 0000 C CNN
F 1 "10k" H 9200 6650 80 0000 C CNN
F 2 "" H 9200 6750 50 0001 C CNN
F 3 "" H 9200 6750 50 0001 C CNN
	1 9200 6750
	1 0 0 -1
$EndComp
Wire Wire Line
	8700 6750 8300 6750
Text GLabel 8300 6750 2 65 BiDi ~ 0
5V
Wire Wire Line
	9700 6750 10100 6750
Text GLabel 10100 6750 0 65 BiDi ~ 0
I5
$Comp
L TIA:JP1_SYM JP1
U 1 1 0500017B
P 13900 6750
F 0 "JP1" H 13900 6520 85 0000 C CNN
F 1 "0R NTSC ONLY / DNP PAL" H 13900 6650 80 0000 C CNN
F 2 "" H 13900 6750 50 0001 C CNN
F 3 "" H 13900 6750 50 0001 C CNN
	1 13900 6750
	1 0 0 -1
$EndComp
Wire Wire Line
	13400 6750 13000 6750
Text GLabel 13000 6750 2 65 BiDi ~ 0
TIA12
Wire Wire Line
	14400 6750 14800 6750
Text GLabel 14800 6750 0 65 BiDi ~ 0
AUD_RAW
Text Notes 800 8700 0 75 ~ 0
PAL: JP1 MUST remain unpopulated. Pin12 is not a second audio output. Pin13 already contains both audio voices.
Text Notes 800 9050 0 75 ~ 0
NTSC conversion: use a verified NTSC TIA, fit JP1, select 3.579545-MHz firmware clock profile. See sheet06.
Text Notes 800 9400 0 75 ~ 0
No video output is provided. DEL/color auxiliary networks are not a PAL video implementation. Do not connect a TV.
Text Notes 800 9750 0 75 ~ 0
C16 is now at U1 pins20/1. TIA/POKEY sockets are NOT interchangeable. R/W, CS2_N and CS3_N are grounded.
Text Notes 800 10100 0 75 ~ 0
C010444 normally denotes NTSC; UM6526P1 corresponds to the PAL C011903 family. Do not use a MOS/CSG 6526 CIA.
Text Notes 800 10450 0 75 ~ 0
Clone identity is corroborated; a manufacturer UM6526P1 pin/electrical datasheet was not located. Verify donor mapping before power.
$EndSCHEMATC
