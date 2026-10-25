EESchema Schematic File Version 4
LIBS:TIA-cache
EELAYER 29 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 7 7
Title "06 / PAL-to-NTSC changes and component reuse"
Date "2026-10-25"
Rev "A - document-reviewed design"
Comp "TIA / ESP32"
Comment1 "No hardware test; see documentation and commissioning procedure"
$EndDescr
Text Notes 700 600 0 110 ~ 12
06 / PAL-to-NTSC changes and component reuse
Text Notes 700 900 0 75 ~ 0
Audio-only conversion instructions / change chip, clock profile and JP1 together / never fit JP1 on a PAL part
Text Notes 1000 1900 0 75 ~ 0
PAL BUILD (default): U1=UM6526P1, C011903-compatible PAL family. M3 CLK0=3.546894 MHz. JP1=DNP.
Text Notes 1000 2400 0 75 ~ 0
NTSC BUILD: U1=verified C010444-family NTSC TIA. M3 CLK0=3.579545 MHz. Fit JP1 to sum pins12+13.
Text Notes 1000 2900 0 75 ~ 0
Firmware: change TIA_NTSC=false to true, rebuild and flash with DevKit removed from the carrier.
Text Notes 1000 3400 0 75 ~ 0
Clock-derived quantities: PAL PHI0 approximately1.182298 MHz, audio tick31.113 kHz; NTSC1.193182 MHz,31.399 kHz.
Text Notes 1000 3900 0 75 ~ 0
The NTSC/PAL pitch ratio is approximately1.009206 (0.921% or15.86 cents). Register divisors are integers; exact retuning is limited.
Text Notes 1000 4500 0 75 ~ 0
Regional pins: PAL6=LUM2,7=LUM0,8=auxiliary,12=auxiliary; NTSC6=BLK,7=LUM2,8=LUM0,12=audio voice.
Text Notes 1000 5000 0 75 ~ 0
Pins5=LUM1 and9=COL stay video outputs; all remain unused here. PAL pin13 is the combined audio output.
Text Notes 1000 5500 0 75 ~ 0
A full PAL color-video implementation also needs its regional color-clock/bias circuitry (typically4.433618 MHz). Not included.
Text Notes 1000 6100 0 75 ~ 0
UNCHANGED: USB-C J1/U10/U11/U12/M1, ESP32 M2, SPI U2/U3, OE Q1, U5/U6 synchronizer and U7 NAND.
Text Notes 1000 6600 0 75 ~ 0
UNCHANGED: U8 MCP6002, U9 LM4808 SOIC, RV1, SW1, TRS socket, all analog coupling/feedback/output protection values.
Text Notes 1000 7100 0 75 ~ 0
CHANGED: U1 socket map; R12 10k->1k; U3.QF=CS1, QE=A4; U4 HCT74->HCT14; X1 removed, M3 added.
Text Notes 1000 7600 0 75 ~ 0
ADDED: R40/C27 timing delay, R41 master input pull-down, JP1 NTSC-only DNP link; SDA/SCL/3V3 module connections.
Text Notes 1000 8200 0 75 ~ 0
REMOVED: POKEY-only R19/R20/R23/R24 terminations. Remaining input terminations are reassigned to TIA inputs.
Text Notes 1000 8800 0 75 ~ 0
DO NOT reuse POKEY firmware/register addresses or its 1-MHz PHI2 wiring. TIA has2 voices and6 audio registers, not4 voices.
Text Notes 1000 9400 0 75 ~ 0
Verification: structural pin/net checks and ideal logic models only. No hardware test, UMC DC guarantee, KiCad ERC or firmware build.
Text Notes 1000 9900 0 75 ~ 0
Before headphones: verify supply, clocks, write timing and both voices using load resistors; MUTE open during power changes.
$EndSCHEMATC
