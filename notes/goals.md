## Revision 4 Goals

* ethernet
* better power supply - independent, non-usb operation
* signal conditioning and ESD protection for 4-5 inputs.
* reconsider universal laser source support - mopa, co2 as well?
* what busses for sensors and extensiblility does it make sense to expose?


## Project History

### Laser Board Rev 1

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

### Laser Board Rev 2

Rev 2 incorporated the following changes:

* Support for a two-axis galvanometer scanner communicating over XY-100, requiring
  adding a DB-15 interface and four differential line drivers.
* Motor interfaces were moved to 4 polarized 4 pin molex 0,1" headers.

Rev 2 is still in active use.

### Laser Board Rev 3

Rev three fixed a bodge wire needed for rev 2, and slightly modified the laser pinout to
support JPT long-pulse sources, although that is as of yet untested.
