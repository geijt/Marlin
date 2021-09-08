/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "env_validate.h"

#define BOARD_INFO_NAME "DAVINCI"

//
// EEPROM
//
#if NO_EEPROM_SELECTED
  #define SDCARD_EEPROM_EMULATION
#endif

//
// Limit Switches
//
#define X_STOP_PIN                            11
#define Y_STOP_PIN                            68
#define Z_STOP_PIN                           124

//
// Steppers
//
#define X_STEP_PIN                            15
#define X_DIR_PIN                             14
#define X_ENABLE_PIN                          29

#define Y_STEP_PIN                            30
#define Y_DIR_PIN                             12
#define Y_ENABLE_PIN                          69

#define Z_STEP_PIN                           119
#define Z_DIR_PIN                            118
#define Z_ENABLE_PIN                         120

#define E0_STEP_PIN                          122
#define E0_DIR_PIN                           121
#define E0_ENABLE_PIN                        123

//
// Temperature Sensors
//
#define TEMP_0_PIN                             9  // Analog Input
#define TEMP_BED_PIN                          14  // Analog Input

//
// Heaters / Fans
//
#define HEATER_0_PIN                          16
#define HEATER_BED_PIN                        17  // BED

#define FAN_PIN                               25
#define FAN1_PIN                               4

//
// Misc. Functions
//
#define SD_DETECT_PIN                         74
#define PS_ON_PIN                             -1
#define CASE_LIGHT_PIN                        85
#define FIL_RUNOUT_PIN                        24

/* No Marlin equilent to this
  #define TOP_SENSOR_PIN                       6
 */

//additionnal PINS
#define MOSI_PIN        43
#define MISO_PIN        73
#define SCK_PIN         42
#define DUE_SOFTWARE_SPI

//
// LCD / Controller
//
#if HAS_WIRED_LCD
  #define UI_DISPLAY_RS_PIN                    8 // PINK.1, 88, D_RS
  #define UI_DISPLAY_RW_PIN                   45 //but do not use it just set state to LOW
  #define UI_DISPLAY_ENABLE_PIN              125 // PINK.3, 86, D_E
  #define UI_DISPLAY_D0_PIN                   34 // PINF.5, 92, D_D4
  #define UI_DISPLAY_D1_PIN                   35 // PINK.2, 87, D_D5
  #define UI_DISPLAY_D2_PIN                   36 // PINL.5, 40, D_D6
  #define UI_DISPLAY_D3_PIN                   37 // PINK.4, 85, D_D7
  #define UI_DISPLAY_D4_PIN                   38 // PINF.5, 92, D_D4
  #define UI_DISPLAY_D5_PIN                   39 // PINK.2, 87, D_D5
  #define UI_DISPLAY_D6_PIN                   40 // PINL.5, 40, D_D6
  #define UI_DISPLAY_D7_PIN                   41 // PINK.4, 85, D_D7
  //back light  PIN - reported in uiconfig.h
  #define UI_BACKLIGHT_PIN                    78
  #define BEEPER_PIN                          66
#endif // HAS_WIRED_LCD

#ifndef SDSS
  #define SDSS                                55
#endif
