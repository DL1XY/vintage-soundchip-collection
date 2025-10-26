# 1. Purpose and Scope

This OpsCon defines how the 8-bit Cartridge Synthesizer System (8-Bit Synth) is used and operated throughout its lifecycle.
It provides the context for system requirements and design decisions by describing intended users, environments, scenarios, modes, and operational data flows.

The system’s goal is to combine retro 8-bit sound chips (e.g. AY-3-8910, SID 6581/8580, YM2149) with a modern digital control core, allowing musicians to play, sequence, and modify chip parameters in real time, using cartridge modules that encapsulate each sound chip and its supporting circuitry.

# 2. Stakeholders and Users
|Role|Interest / Function|
|----|-------------------|
|Performer / Musician|Plays live, adjusts sound in real time.|
|Sound Designer|Creates and stores patches, explores chip-specific timbres.|
|Firmware Developer	|Implements chip drivers and UI logic.|
|Hardware Engineer|Designs cartridges, power, and audio subsystems.|
|Quality / Test	| Verifies conformance and reliability.|
|Maintenance / Service | Updates firmware, replaces worn connectors, calibrates audio.|

# 3. System Context

## External Interfaces:

* User: interacts via display, encoder, buttons, optional external MIDI keyboard.

* Host: communicates over USB-MIDI (class compliant).

* External Clock Source: optional sync via 24 PPQN in/out.

* Audio Outputs: stereo line out and headphone jack feed mixers, amps, or DAWs.

* Power Input: USB-C PD source (5 V–12 V profiles).

## Internal Elements:

* Control MCU (real-time scheduler, patch manager)

* Cartridge Backplane (4 slots)

* Each Cartridge: MCU + 8-bit sound chip + analog output stage

* Analog Mixer / EQ (sums outputs)

* Power Subsystem (multi-rail regulated supply)

# 4. Operational Scenarios

## UC-01: Power-on and Initialization

* User connects USB-C power or host.

* MCU negotiates PD profile and sequences rails.

* Each cartridge is powered and enumerated via I²C ID EEPROM.

* Firmware loads driver module for each detected chip.

* UI displays slot status.

* Ready for performance within 3 s.

**Success Criteria:** all cartridges active; no pops or rail glitches.

## UC-02: Live Performance Mode

* Performer connects MIDI keyboard or USB host.

* Incoming MIDI events are parsed; note events routed to active patch voices.

* Control MCU schedules register writes to each chip via SPI with bounded latency.

* Real-time parameters (volume, filter, envelope) are mapped to encoders.

* Audio from cartridges mixed and output via analog summing/EQ.

* Display shows patch name, tempo, active voices.

* Key Performance: total MIDI-to-audio latency < 5 ms; glitch-free control changes.

## UC-03: Sequencing Mode

* User enables internal 16-step sequencer (Roland-style grid).

* Steps trigger chip registers at beat boundaries.

* Tempo adjustable via encoder; clock can be master or slave via clock I/O.

* Sequence and patch saved to SD card.

**Outcome:** repeatable playback, stable tempo, non-blocking UI.

## UC-04: Cartridge Swap (Maintenance Mode)

* Power down system (hot-swap disabled).

* Remove cartridge; insert new one.

* Power up; MCU enumerates and identifies new chip type.

* If driver missing, shows “Unsupported Cartridge” message.

**Design Note:** Prevent over-voltage or mis-insertion through keyed connector.

## UC-05: Firmware Update

* User connects via USB; device enumerates as DFU or MSC volume.

* User copies firmware image or uses updater tool.

* Bootloader validates signature, updates main image.

* If failure detected, automatic rollback to previous image.

**Outcome**: field-upgradable without service tools.

## UC-06: Diagnostics and Self-Test

* On boot with “Test” button held, run BIST.

* Verify power rails, cartridge IDs, SPI comms, and generate test tones.

* Report summary on display.

**Use:** factory verification, RMA screening.

# 5. Modes of Operation
|Mode|Description|Transitions|
|----|-----------|-----------|
|Standby|Power present, low consumption; waiting for user.	|→ Performance or Firmware Update|
|Performance|Normal play and sequencing mode.|↔ Sequencer; → Settings|
|Settings|Patch management, EQ config, SD operations.|↔ Performance|
|Firmware Update|Bootloader active; accepts new image.|→ Standby after update|
|Self-Test|Diagnostic sequence.|	→ Standby after completion|

# 6. Operating Environment

* **Electrical:** powered by USB-C PD (5–12 V), compliant host or supply.

* **Ambient:** 0–40 °C, ≤85 % RH non-condensing.

* **Use Locations:** studio, stage, rehearsal room.

* **Acoustic:** line-level outputs feed professional mixers (nominal 1 Vrms).

# 7. Support, Maintenance & Lifecycle

* **Firmware updates** via USB without opening enclosure.

* **Cartridges replaceable** by user; mechanically keyed and ESD-protected.

* **Expected connector life:** ≥2000 insertions.

* **Diagnostics:** accessible from UI menu; reports voltages, firmware versions, slot status.

* **Service interval:** visual inspection and cleaning every 12 months.

# 8. Concept of Support and Disposal

* User manual and open API for patch format published.

* Spare cartridges and PCBs replaceable with minimal calibration.

* End of life: components RoHS compliant, recyclable; firmware open for archival use.

