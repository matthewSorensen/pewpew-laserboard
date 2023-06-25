## Laser Source IO

Most of the laserboar-r5's GPIO is spent on a semi-universal interface for common fiber laser sources. None of these
pins have strict hardware interface, although SYNC must be a PWM-capable pin. 


|IO Name/Function|Teensy 4.1 Pin Number|Register/Bit|
|----------------|----------|-----------------------|
|INTERLOCK       |6         |GPIO7/2                |
|ENABLE          |8         |GPIO7/0                |
|GUIDE_LASER     |9         |GPIO7/3                |
|ALARM_0/LATCH   |10        |GPIO6/31               |
|SYNC            |11        |GPIO6/30               |
|MODULATE        |12        |GPIO6/12               |
|ALARM_2         |26        |GPIO6/13               |
|ALARM_1         |27        |GPIO7/16               |
|PWR_0           |33        |GPIO9/7                |
|PWR_1/SER_DATA  |34        |GPIO9/7                |
|PWR_2/SER_CLOCK |35        |GPIO9/7                |
|PWR_3           |36        |GPIO9/7                |
|PWR_4           |28        |GPIO9/7                |
|PWR_5           |29        |GPIO9/7                |
|PWR_6           |30        |GPIO9/7                |
|PWR_7           |31        |GPIO9/7                |

INTERLOCK is an input pin for an enclosure interlock switch (active closed, labeled "Interlock" on PCB), which is
debounced and level-shifted to 3.3v. This signal is also level-shifted to 5V and routed to the laser's interlock
pin (thought jumper JP11), and has an associated indicator LED (labeled "Interlock OK!"). ENABLE is an
(active-high) output pin for the controller to arm the laser - the actual enable signal is derived by passing this
and the INTERLOCK signal through an AND-gate.

GUIDE_LASER is an active-high output for the laser source's aiming laser, if one exists. Note that this has no
interlock, as it is intended for use with an open enclosure. On most MOPA sources, this also puts the source
into receive mode for the serial data stream on PWR_1/SER_DATA & PWR_2/SER_CLOCK - thus, firmware must not change
any power levels while GUIDE_LASER is high.

SYNC is the laser pulse clock - unlike previous revisions, there is no hardware timer supervising this, and so it
must not be changed while the laser is actively firing, or giant Q-switch pulses may destroy optics. Pulse
repetition rate is highly source dependent, but the teensy 4.x can generate PWM at up to 10s of MHz, and the
74AHC245PW is similarly capable.

Once a laser source is armed (INTERLOCK is high, ENABLE is high, SYNC is running, and a suitable lockout period
has passed), MODULATE is an active-high pin that controls laser emission.

On some laser sources, ALARM_0/LATCH is a controller input that sources may use to signal undervoltage conditions.
It is also multiplexed as a latch signal for sources that require one - JP13 controls this, and defaults to closed/alarm
mode.

PWR_0 through PWR_7 form a 8-bit parallel interface for laser power control, with a least-significant bit of PWR_0. MOPA
laser sources also support a serial data input stream for configuring pulse length - in that case, serial data may be
written at 8kHz over PWR_1/SER_DATA and PWR_1/SER_CLOCK when the GUIDE_LASER line is high. In all cases, the power bits
may not change when the laser is emitting.


## Galvo XY-100 IO

The galvo IO needs to be on these exact pins, as it uses the Teensy's I2S hardware to generate all signals. 
The interface to the galvos is made through two UA9638CD differential line drivers, each taking two single-ended
signals from the processor and turning them into differential signals for the galvos. These are all verified to be
compatible between teensy 4, 4.1, and Teensy Micromod.


|IO Name/Function|Teensy 4.1 Pin Number|Register/Bit|
|----------------|----------|-----------------------|
|GALVO_CLOCK     |21        |**GPIO6/27**           |
|GALVO_SYNC      |20        |**GPIO6/26**           |
|GALVO_D1        |7         |**GPIO7/17**           |
|GALVO_D2        |32        |**GPIO7/12**           |

## Motion IO

The step and direction GPIO must all lie on one port - in this case, GPIO6. This is the main limit to the number of
stepper axes, and could be expanded by refactoring the code to only require that the step pins lie on one port, and
the direction pins on another. Similarly, the limit switch pins must all lie on one port - this is less critical, and
would be easy to refactor away from. 

Electrically, step/dir pins are level shifted to 5V with a 74AHC245PW-Q100J. Limit switches are debounced with a slightly
elaborate arrangement of an RC low-pass filter, jumper-configurable pull-ups/pull-downs with diodes for symmetric recovery,
and another 74AHC245PW Schmitt-trigger.


|IO Name/Function|Teensy 4.1 Pin Number|Register/Bit|
|----------------|----------|-----------------------|
|Axis 0 Step     |23        |**GPIO6/25**           |
|Axis 0 Direction|22        |**GPIO6/24**           |
|Axis 0 Home     |2         |**GPIO9/4**            |
|Axis 1 Step     |19        |**GPIO6/16**           |
|Axis 1 Direction|18        |**GPIO6/17**           |
|Axis 1 Home     |3         |**GPIO9/5**            |
|Axis 2 Step     |17        |**GPIO6/22**           |
|Axis 2 Direction|16        |**GPIO6/23**           |
|Axis 2 Home     |4         |**GPIO9/6**            |
|Axis 3 Step     |15        |**GPIO6/19**           |
|Axis 3 Direction|14        |**GPIO6/18**           |
|Axis 3 Home     |5         |**GPIO9/8**            |


