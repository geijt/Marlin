/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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

/**
 * Driver for the Philips PCA9685 PWM driver.
 */

#include "../inc/MarlinConfig.h"

#if ENABLED(PCA9685)

#include "pca9685.h"
#include <Wire.h>

#define PCA9685_MODE1_VALUE         PCA9685_MODE_ALLCALL|PCA9685_MODE_AUTOINC
#define PCA9685_MODE2_VALUE         PCA9685_MODE_TOTEM_POLE
#ifndef PCA9685_ADDRESS
  #define PCA9685_ADDRESS           (byte)0x40
#endif

/* Register addresses */
#define PCA9685_MODE1_REG           (byte)0x00
#define PCA9685_MODE2_REG           (byte)0x01
#define PCA9685_SUBADR1_REG         (byte)0x02
#define PCA9685_SUBADR2_REG         (byte)0x03
#define PCA9685_SUBADR3_REG         (byte)0x04
#define PCA9685_ALLCALL_REG         (byte)0x05
#define PCA9685_LED0_REG            (byte)0x06 // Start of PWMx regs, 4B per reg, 2B on phase, 2B off phase, little-endian
#define PCA9685_PRESCALE_REG        (byte)0xFE
#define PCA9685_ALLLED_REG          (byte)0xFA

// Mode1 register pin layout
#define PCA9685_MODE_RESTART        (byte)0x80
#define PCA9685_MODE_EXTCLK         (byte)0x40
#define PCA9685_MODE_AUTOINC        (byte)0x20
#define PCA9685_MODE_SLEEP          (byte)0x10
#define PCA9685_MODE_SUBADR1        (byte)0x08
#define PCA9685_MODE_SUBADR2        (byte)0x04
#define PCA9685_MODE_SUBADR3        (byte)0x02
#define PCA9685_MODE_ALLCALL        (byte)0x01

// Mode2 register pin layout
#define PCA9685_MODE_INVRT          (byte)0x10
#define PCA9685_MODE_OCH            (byte)0x08
#define PCA9685_MODE_TOTEM_POLE     (byte)0x04
#define PCA9685_MODE_OUTNE1         (byte)0x02
#define PCA9685_MODE_OUTNE0         (byte)0x01

#define PCA9685_PWM_FULL            (uint16_t)0x01000 // Special value for full on/full off LEDx modes

#define FREQUENCY_OSCILLATOR         25000000  // Int. osc. frequency in datasheet
#define PCA9685_PRESCALE_MIN                3  // minimum prescale value
#define PCA9685_PRESCALE_MAX              255  // maximum prescale value

byte PCA9685_init = 0;

static void PCA9685_WriteRegister(const byte addr, const byte regadd, const byte value) {
  Wire.beginTransmission(addr);
  Wire.write(regadd);
  Wire.write(value);
  Wire.endTransmission();
}

static uint8_t PCA9685_ReadRegister(const byte addr, const byte regadd) {
  Wire.beginTransmission(addr);
  Wire.write(regadd);
  Wire.requestFrom((uint8_t)addr,(uint8_t)1);
  uint8_t value = Wire.read();
  Wire.endTransmission();
  return value;
}

static void PCA9685_WriteAllRegisters(const byte addr, const byte regadd, const byte value1, const byte value2, const byte value3, const byte value4) {
  Wire.beginTransmission(addr);
  Wire.write(regadd);
  Wire.write(value1);
  Wire.write(value2);
  Wire.write(value3);
  Wire.write(value3);
  Wire.endTransmission();
}

/*!
 *  @brief  Sets the PWM frequency for the entire chip, up to ~1.6 KHz
 *  @param  freq Floating point frequency that we will attempt to match
 */
void PCA9685_setPWMFreq(float freq) {
  // Range output modulation frequency is dependant on oscillator
  if (freq < 1)
    freq = 1;
  if (freq > 3500)
    freq = 3500; // Datasheet limit is 3052=50MHz/(4*4096)

  float prescaleval = ((FREQUENCY_OSCILLATOR / (freq * 4096.0)) + 0.5) - 1;
  if (prescaleval < PCA9685_PRESCALE_MIN)
    prescaleval = PCA9685_PRESCALE_MIN;
  if (prescaleval > PCA9685_PRESCALE_MAX)
    prescaleval = PCA9685_PRESCALE_MAX;
  uint8_t prescale = (uint8_t)prescaleval;

  uint8_t oldmode = PCA9685_ReadRegister(PCA9685_ADDRESS, PCA9685_MODE1_REG);
  uint8_t newmode = (oldmode & ~PCA9685_MODE_RESTART) | PCA9685_MODE_SLEEP; // sleep
  PCA9685_WriteRegister(PCA9685_ADDRESS,PCA9685_MODE1_REG, newmode);
  PCA9685_WriteRegister(PCA9685_ADDRESS,PCA9685_PRESCALE_REG, prescale);
  PCA9685_WriteRegister(PCA9685_ADDRESS,PCA9685_MODE1_REG, oldmode);
  safe_delay(5);
  // This sets the MODE1 register to turn on auto increment.
  PCA9685_WriteRegister(PCA9685_ADDRESS,PCA9685_MODE1_REG, oldmode | PCA9685_MODE_RESTART | PCA9685_MODE_AUTOINC);
}

void pca9685_set_port_PWM16(const uint8_t port, uint16_t pwm) {
  byte on_l=0;
  byte on_h=0;
  byte off_l=0;
  byte off_h=0;

  Wire.begin();
  if (!PCA9685_init) {
    PCA9685_init = 1;
    PCA9685_WriteRegister(PCA9685_ADDRESS,PCA9685_MODE1_REG, PCA9685_MODE1_VALUE);
    PCA9685_WriteRegister(PCA9685_ADDRESS,PCA9685_MODE2_REG, PCA9685_MODE2_VALUE);
    PCA9685_setPWMFreq(PCA9685_FREQUENCY);
  }

  if (pwm > PCA9685_PWM_FULL ) pwm = PCA9685_PWM_FULL;

  if (pwm == PCA9685_PWM_FULL ) on_h = (PCA9685_PWM_FULL&0x1F00)>>8;
  else if (pwm == 0) off_h = (PCA9685_PWM_FULL&0x1F00)>>8;
  else {
    off_h = (pwm&0xF00)>>8;
    off_l = pwm&0xFF;
  }

  PCA9685_WriteAllRegisters(PCA9685_ADDRESS,PCA9685_LED0_REG+(4*port), on_h, on_l, off_h, off_l);
}

void pca9685_set_port_PWM8(const uint8_t port, uint16_t pwm) {
  if (pwm >= 255 ) pwm = 256;
  pca9685_set_port_PWM16(port, pwm<<4);
}

#endif // PCA9685
