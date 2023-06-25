## Revision History

### Rev 5

Revision 5 is, in some ways, a simplification, and breaks pin mapping backwards compatability. The major
changes are as follows:

* The MCU board is changed from a Teensy 4.0 to a Teensy 4.1, in order to accces more GPIO and remove a messy SMD
 header on the bottom of the board.
 
* Proper power supply input - small fiber lasers generally run on 24VDC supplies, and galvo scanners required -15/15V
 supplies, so there's always a readily available DC rail to generate a 5V rail for the teensy. The input protection
 circuit and switcher is essentially the same as published [here](https://blog.thea.codes/starfish-a-control-board-with-the-rp2040/),
 although it omits reverse polarity protection and uses a small polyfuse due to much lower current demands. The board
 may also be powered off a USB connection by shifting the location of a jumper.

* The Q-switch protection circuitry is removed, as the current firmware seems to be robust enough to trust with not
 generating Q-switch clock glitches, and the broader frequency range required for MOPA sources renders it useless.

* Previously, the standard 8-bit parallel laser power interface used a shift register to reduce the GPIO requirement - now,
  8 GPIO pins directly control the power. Supporting MOPA serial data stream with the shift register would have
  required bit-banging a serial stream to bit bang a serial stream - although this was technically feasible, the code
  complexity would have been annoying, and the switch to a parallel interface only required four extra pins.

* Four limit pins are properly debounced with a low-pass filter and Schmitt-trigger and have (jumper) configurable
  pull-up/down resistors and indicator LEDs.
  
* The teensy 4.1 ethernet phy is broken out to an on-board magjack.


### Rev 3 & 4

Rev 3 fixed a bodge wire needed for rev 2, and rev 4 slightly modified the laser pinout to
support JPT long-pulse sources, although that is as of yet untested.

### Rev 2

Rev 2 incorporated the following changes:

* Support for a two-axis galvanometer scanner communicating over XY-100, requiring
  adding a DB-15 interface and four differential line drivers.
* Motor interfaces were moved to 4 polarized 4 pin molex 0,1" headers.

Rev 2 is still in active use.

### Rev 1

Revision one was ordered 2021/5/4, and had the following features:

* One DB-25 interface for a q-switched fiber laser, with a one-shot timer
  used to protect the laser from abnormal q-switch pulse trains, a shift
  register for the power control interface, and a hardware interlock to
  require a good q-switch clock signal, a good e-stop signal, and software
  enabling of the laser.
* Four step/direction interfaces, level-shifted to 5V and broken out on a
  single 0.1" header.
* A schmitt-triggered and debounced e-stop input.
* 9 GPIO broken out on a 0.1" header, with no level-shifting or signal conditioning.

Revision one was used with a stepper-driven micrometer stage to get a proof-of-concept
working for some surface-patterning applications, and was quickly replaced with rev 2.


