## Laser Source IO

|IO Name/Function|Teensy 4.1 Pin Number|Register/Bit|
|----------------|----------|-----------------------|
|SYNC            |11        |GPIO7/2                |
|ENABLE          |10        |GPIO7/0                |
|MODULATE        |13        |GPIO7/3                |
|PWR_EN          |27        |GPIO6/31               |
|PWR_DATA        |26        |GPIO6/30               |
|PWR_SET         |24        |GPIO6/12               |
|PWR_CLK         |25        |GPIO6/13               |
|POWER_LATCH_PIN |8         |GPIO7/16               |
|SAFE_ENABLE     |33        |GPIO9/7                |
|INTERLOCK       |30        |GPIO8/23               |
|ALARM0          |31        |GPIO8/22               |
|ALARM1          |29        |GPIO9/31               |
|ALARM2          |28        |GPIO8/18               |
|GUIDE_LASER     |9         |GPIO7/11               |

## Galvo XY-100 IO

The galvo IO needs to be on these exact pins, as it uses the Teensy's I2S hardware to generate all signals. 
The interface to the galvos is made through two UA9638CD differential line drivers, each taking two single-ended
signals from the processor and turning them into differential signals for the galvos.


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
would be easy to refactor. 

Electrically, step/dir pins are level shifted to 5V with a 74AHC245PW-Q100J. Currently, limit switch input pins
aren't buffered, which is suboptimal. 

|IO Name/Function|Teensy 4.1 Pin Number|Register/Bit|
|----------------|----------|-----------------------|
|Axis 0 Step     |23        |**GPIO6/25**           |
|Axis 0 Direction|22        |**GPIO6/24**           |
|Axis 0 Home     |2         |**GPIO9/4**            |
|Axis 1 Step     |19        |**GPIO6/16**           |
|Axis 1 Direction|18        |**GPIO6/17**           |
|Axis 1 Home     |3         |**GPIO6/5**            |
|Axis 2 Step     |17        |**GPIO6/22**           |
|Axis 2 Direction|16        |**GPIO6/23**           |
|Axis 2 Home     |4         |**GPIO6/6**            |
|Axis 3 Step     |15        |**GPIO6/19**           |
|Axis 3 Direction|14        |**GPIO6/18**           |
