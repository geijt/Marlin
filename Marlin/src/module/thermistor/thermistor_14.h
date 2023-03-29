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

// 100K B57560G1104F
// Calculated using 4.7kohm pullup, voltage divider math, and manufacturer provided temp/resistance

constexpr temp_entry_t temptable_14[] PROGMEM = {
{ OV(  23),  300 },
{ OV(  24),  295 },
{ OV(  26),  290 },
{ OV(  28),  285 },
{ OV(  30),  280 },
{ OV(  32),  275 },
{ OV(  35),  270 },
{ OV(  37),  265 },
{ OV(  40),  260 },
{ OV(  43),  255 },
{ OV(  47),  250 },
{ OV(  51),  245 },
{ OV(  55),  240 },
{ OV(  60),  235 },
{ OV(  65),  230 },
{ OV(  70),  225 },
{ OV(  76),  220 },
{ OV(  83),  215 },
{ OV(  90),  210 },
{ OV(  99),  205 },
{ OV( 108),  200 },
{ OV( 118),  195 },
{ OV( 129),  190 },
{ OV( 141),  185 },
{ OV( 154),  180 },
{ OV( 168),  175 },
{ OV( 184),  170 },
{ OV( 202),  165 },
{ OV( 221),  160 },
{ OV( 242),  155 },
{ OV( 265),  150 },
{ OV( 289),  145 },
{ OV( 316),  140 },
{ OV( 344),  135 },
{ OV( 375),  130 },
{ OV( 407),  125 },
{ OV( 441),  120 },
{ OV( 476),  115 },
{ OV( 512),  110 },
{ OV( 550),  105 },
{ OV( 587),  100 },
{ OV( 625),  95  },
{ OV( 663),  90  },
{ OV( 699),  85  },
{ OV( 734),  80  },
{ OV( 768),  75  },
{ OV( 800),  70  },
{ OV( 829),  65  },
{ OV( 856),  60  },
{ OV( 881),  55  },
{ OV( 903),  50  },
{ OV( 922),  45  },
{ OV( 939),  40  },
{ OV( 954),  35  },
{ OV( 966),  30  },
{ OV( 977),  25  },
{ OV( 986),  20  },
{ OV( 994),  15  },
{ OV(1000),  10  },
{ OV(1005),  5   },
{ OV(1009),  0   },
{ OV(1012), -5   },
{ OV(1015), -10  },
{ OV(1017), -15  },
{ OV(1018), -20  },
{ OV(1019), -25  },
{ OV(1020), -30  },
{ OV(1021), -35  },
{ OV(1022), -40  },
{ OV(1022), -45  },
{ OV(1022), -50  },
{ OV(1023), -55  }
};


