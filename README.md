# PewPew LaserBoard

## What Is It?

LaserBoard is an open source controller for fiber laser marking systems, based around a Teensy 4.1 MCU board. LaserBoard
provides a USB interface compatible with most low-cost fiber laser sources and XY-100-speaking galvanometer scanners, and
supports 4 axes of step/direction motion control.

## Q&A

### Why?

At the component level, laser marking hardware is remarkably cheap and high quality, and easy to interface with - with
the exception of the control boards! Generally, they're bundled with a license for low-quality, proprietary software,
greatly inflating the price - a control board with 4 auxiliary axes (eg. JCZ DLC2-M4) cost about as much as a quality
laser source and scanner ($2000!). 

Advanced features such as high-precision lens calibration, field stitching, active z-axes control etc. are also very
difficult to implement, as the commercial controllers behave like a black-box and speak an undocumented host/controller
protocol. Some reverse-engineered 3rd party software exists, such as [LightBurn](https://lightburnsoftware.com/) (commercial,
user-friendly high-quality GUI) or [Balor](https://www.bryce.pw/engraver.html) (open-source python interface library),
but controller support is limited.

### Lasers Are Dangerous! Is This Safe?

Lasers can be very dangerous! Unenclosed 10+ watt invisible lasers with peak powers in the low 10s of kW are
absolutely not safe, and a quick scan of YouTokstagram "laser influencer" content will show many poorly educated people
doing very dangerous things with them. Laser safety regulation and enforcement hasn't caught up to the ease with
which anyone can import a turnkey class-4 laser capable of instablindess.

Lasers are also very useful and all of the risks associated with them may be mitigated with proper engineering and
procedural controls. It is essential to fully understand these risks BEFORE purchasing a laser, and if you already
have one, before modifying it or further using it.

If you're in a context with a laser safety officer, talk with them. Laser safety officers are your friends, even
if they seem scary at first.

### What Software Do I Need?

LaserBoard is designed for use with [pewpew-laser](https://github.com/matthewSorensen/pewpew-laser). If that link
appears to be a 404, it's because I'm ambivalent about running an open-source project and haven't figured out the
liability issues related to releasing a complete system. Additionally, there's no GUI or even a standard toolpath
generation script - although there might be some [Rhinoceros](https://www.rhino3d.com/) plugins in the works.

## Revision History

### Rev 5

Revision 5 is, in some ways, a simplification, and breaks pin mapping backwards compatibility. The major
changes are as follows:

* The MCU board is changed from a Teensy 4.0 to a Teensy 4.1, in order to access more GPIO and remove a messy SMD
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


### Rev 4

Rev 4 fixed a bodge wire needed for rev 3 and slightly modified the laser pinout to
support JPT long-pulse sources, although that is as of yet untested.

### Rev 3

Rev 2 incorporated the following changes:

* Support for a two-axis galvanometer scanner communicating over XY-100, requiring
  adding a DB-15 interface and four differential line drivers.
* Motor interfaces were moved to 4 polarized 4 pin molex 0,1" headers.

Rev 3 is still in active use.

### Rev 1 and 2

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
working for some surface-patterning applications, and was quickly replaced with rev 2 -
seemingly a mostly cosmetic modification .

