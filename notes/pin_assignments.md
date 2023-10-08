# LaserBoard Pin Assignments

## Laser Source IO

Most of the laserboar-r5's GPIO is spent on a semi-universal interface for common fiber laser sources. None of these
pins have strict hardware interface, although SYNC must be a PWM-capable pin. 


|IO Name/Function|Teensy 4.1 Pin Number|Register/Bit|
|----------------|----------|-----------------------|
|INTERLOCK       |6         |GPIO7/10               |
|ENABLE          |8         |GPIO7/16               |
|GUIDE_LASER     |9         |GPIO7/11               |
|ALARM_0/LATCH   |10        |GPIO7/0                |
|SYNC            |11        |GPIO7/2                |
|MODULATE        |12        |GPIO7/1                |
|ALARM_2         |26        |GPIO6/30               |
|ALARM_1         |27        |GPIO6/31               |
|PWR_0           |33        |GPIO9/7                |
|PWR_1/SER_DATA  |34        |GPIO8/15               |
|PWR_2/SER_CLOCK |35        |GPIO8/14               |
|PWR_3           |36        |GPIO8/13               |
|PWR_4           |28        |GPIO8/18               |
|PWR_5           |29        |GPIO9/31               |
|PWR_6           |30        |GPIO8/23               |
|PWR_7           |31        |GPIO8/22               |

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


# Laser DB-25 Interface

| DB-25 Pin | Raycus RFL-P30QS | JPT YDFLP-E-20 | RFL-P20MB | JPT  YDFLP-M6+ | Current Pinout |
| --- | --- | --- | --- | --- | --- |
| 1 | Power LSB - D0 | Power LSB - D0 | Power LSB - D0 | Power LSB - D0 | PWR_0 |
| 2 | D1 | D1 | D1 / Serial Input | D1 / Serial Input | PWR_1/SER_DATA | 
| 3 | D2 | D2 | D2 / Serial Clock | D2 / Serial Clock | PWR_2/SER_CLOCK |
| 4 | D3 | D3 | D3 | D3 | PWR_3 |
| 5 | D4 | D4 | D4 | D4 | PWR_4 |
| 6 | D5 | D5 | D5 | D5 | PWR_5 |
| 7 | D6 | D6 | D6 | D6 | PWR_6 |
| 8 | Power MSB - D7 | Power MSB - D7 | Power MSB - D7 | Power MSB - D7 | PWR_7 |
| 9 | Obligate Raycus only | Power Latch | Obligate Raycus only | NC | Multiplexed to ALARM_O/LATCH |
| 10 | GND | GND | GND | GND | GND |
| 11 | Supply voltage alarm | GND | Abnormal state alarm | GND | Multiplexed to ALARM_O/LATCH |
| 12 | alarm - always high | GND | alarm - always high | GND | NC |
| 13 | GND | GND | Obligate Raycus only | GND | NC |
| 14 | GND | GND | GND | GND | GND |
| 15 | GND | GND | Obligate Raycus only | GND | NC |
| 16 | System Alarm | System Alarm | System Alarm | System Alarm | ALARM_1 |
| 17 | 5V Supply | NC | 5V Supply | NC | Jumper to 5V supply |
| 18 | Emission Enable | Master Oscilator enable | Emission Enable | Master Oscilator enable | SAFE_ENABLE |
| 19 | Emission Modulate | Emission Modulation | Emission Modulate | Emission Modulation | MODULATE |
| 20 | Sync | Frequency Modulation | Sync | Frequency Modulation | SYNC |
| 21 | Alarm | Temperature Alarm | Alarm | Temperature Alarm | ALARM_2 |
| 22 | Guide Laser | Guide Laser | Guide Laser / Serial Enable | Guide Laser / Serial Enable | GUIDE_LASER |
| 23 | Obligate Raycus only | Emergency Stop | Obligate Raycus only | NC | Jumper to INTERLOCK |
| 24 | GND | NC | Obligate Raycus only | NC | NC |
| 25 | GND | NC | Obligate Raycus only | NC | NC |

# Jumper Table

|Jumper Designators|Function|Default|Raycus State|JPT State| 
|------------------|--------|-------|------------|---------|
|JP14,15| Limit input 0 pull up|closed|n.a.|n.a|
|JP1,2| Limit input 0 pull down|open|n.a.|n.a|
|JP3,17| Limit input 1 pull up|closed|n.a.|n.a|
|JP4,16| Limit input 1 pull down|open|n.a.|n.a|
|JP5,19| Limit input 2 pull up|closed|n.a.|n.a|
|JP6,18| Limit input 2 pull down|open|n.a.|n.a|
|JP7,21| Limit input 3 pull up|closed|n.a.|n.a|
|JP8,20| Limit input 3 pull down|open|n.a.|n.a|
|JP9| Laser 5V supply| closed | closed | open|
|JP10| Power Latch | open | open | closed |
|JP11| Interlock/E-stop | closed | closed | closed |
|JP12| USB Power | n.a. | n.a. | n.a. |
|JP13| Alarm 0 |closed | closed | open |

Only one of each pair of JP1/JP2, etc should be closed for proper limit operation. For programming and
operation on USB power, JP12 must have pins 1 and 2 connected. For operation on external power, JP12 must
have pins 2 and 3 connected.
