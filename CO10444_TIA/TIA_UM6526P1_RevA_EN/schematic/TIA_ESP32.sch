EESchema Schematic File Version 4
LIBS:TIA-cache
EELAYER 29 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 7
Title "TIA ESP32 - project overview"
Date "2026-10-25"
Rev "A - document-reviewed design"
Comp "TIA / ESP32"
Comment1 "No hardware test; see documentation and commissioning procedure"
$EndDescr
$Sheet
S 2200 1800 7000 900
U 70000000
F0 "01 / USB-C and power supply" 90
F1 "01_power.sch" 75
$EndSheet
$Sheet
S 2200 3200 7000 900
U 70000001
F0 "02 / ESP32 and latched TIA write bus" 90
F1 "02_controller.sch" 75
$EndSheet
$Sheet
S 2200 4600 7000 900
U 70000002
F0 "03 / PAL master clock and synchronized write pulse" 90
F1 "03_clock.sch" 75
$EndSheet
$Sheet
S 2200 6000 7000 900
U 70000003
F0 "04 / UM6526P1 PAL-family socket" 90
F1 "04_pokey.sch" 75
$EndSheet
$Sheet
S 2200 7400 7000 900
U 70000004
F0 "05 / Mono audio and TRS headphone output" 90
F1 "05_audio.sch" 75
$EndSheet
$Sheet
S 2200 8800 7000 900
U 70000005
F0 "06 / PAL-to-NTSC changes and component reuse" 90
F1 "06_ntsc.sch" 75
$EndSheet
Text Notes 1500 1000 0 120 ~ 12
TIA / ESP32 - Rev. A
Text Notes 2200 10500 0 85 ~ 0
Global net names connect the subsheets. Read the documentation before assembly.
$EndSCHEMATC
