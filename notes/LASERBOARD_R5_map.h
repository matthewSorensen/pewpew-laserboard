/*
  LASERBOARD_R5_map.h - driver code for IMXRT1062 processor (on Teensy 4.0 board)

  Part of grblHAL

  Board by Matthew Sorensen: https://github.com/matthewSorensen/pewpew-laserboard

  Note that this is a board map for using Laserboard-R5 as a generic 5x axis cnc controller,
  not for its intended purpose - driving fiber laser sources and galvo scanners, along
  with 4 axis motion. Some of the capabilities are limited - aux gpio isn't protected,
  the 4th axis limit switch doesn't have a proper debounce circuit, etc.

  Copyright (c) 2020-2023 Terje Io

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#define BOARD_NAME "Laserboard-R5"
#define BOARD_URL "https://github.com/matthewSorensen/pewpew-laserboard"

#if N_ABC_MOTORS > 2
#error "Axis configuration is not supported!"
#endif

#if QEI_ENABLE
#error "No pins available for encoder input!"
#endif

#if SPINDLE_SYNC_ENABLE
#error "Spindle sync is not supported for Laserboard-R5!"
#endif

#define X_STEP_PIN          (23u)
#define X_DIRECTION_PIN     (22u)
#define X_LIMIT_PIN         (2u)

#define Y_STEP_PIN          (19u)
#define Y_DIRECTION_PIN     (18u)
#define Y_LIMIT_PIN         (3u)

#define Z_STEP_PIN          (17u)
#define Z_DIRECTION_PIN     (16u)
#define Z_LIMIT_PIN         (4u)

// Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 0
#define M3_AVAILABLE
#define M3_STEP_PIN         (15u)
#define M3_DIRECTION_PIN    (14u)
#define M3_LIMIT_PIN        (10u)
#endif

// Define ganged axis or B axis step pulse and step direction output pins.
#if N_ABC_MOTORS == 2
#define M4_AVAILABLE
#define M4_STEP_PIN         (33u)
#define M4_DIRECTION_PIN    (34u)
#define M4_LIMIT_PIN        (27u)
#define M4_ENABLE_PIN       (35u)
#endif

#if MPG_MODE == 1 && !defined(M4_LIMIT_PIN)
#define MPG_MODE_PIN        (39u)
#endif

// Define stepper driver enable/disable output pin(s).
#define STEPPERS_ENABLE_PIN (36u)

// Define spindle enable and spindle direction output pins.
#if DRIVER_SPINDLE_ENABLE
#define SPINDLE_ENABLE_PIN      (8u)
#define SPINDLE_DIRECTION_PIN   (11u)
#define SPINDLE_PWM_PIN         (12u) // NOTE: only pin 12 or pin 13 can be assigned!
#endif

// Define flood and mist coolant enable output pins.
#define COOLANT_FLOOD_PIN   (28u)
#define COOLANT_MIST_PIN    (29u)

// Define user-control CONTROLs (cycle start, reset, feed hold, door) input pins.
#define RESET_PIN           (26u)
#define FEED_HOLD_PIN       (37u)
#define CYCLE_START_PIN     (38u)
#if SAFETY_DOOR_ENABLE
#define SAFETY_DOOR_PIN     (6u)
#endif

// Define probe switch input pin.
#define PROBE_PIN           (5U)

#define AUXOUTPUT0_PIN      (30u)
#define AUXOUTPUT1_PIN      (31u)

#if I2C_ENABLE
#define I2C_PORT    4
#define I2C_SCL4    (24u) // Not referenced, for info only
#define I2C_SDA4    (25u) // Not referenced, for info only
#endif
