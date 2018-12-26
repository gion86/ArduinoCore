/*
 *  This file is part of ATMegaCore Library.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */
#ifndef TIMEUTILS_H_
#define TIMEUTILS_H_

#include <time.h>
#include <avr/pgmspace.h>

#include <Arduino.h>

// MACRO to manipulate dates for avr-libc time.h (years since 1900,
// months in [0, 11]
#define  TM_YEAR_CAL(Y) ((Y) + 1900)  // Full four digit year
#define  CAL_YEAR_TM(Y) ((Y) - 1900)

#define  TM_YEAR_Y2K(Y) ((Y) - 100)   // Two digit year
#define  Y2K_YEAR_TM(Y) ((Y) + 100)

#define  TM_MON_CAL(M)  ((M) + 1)     // Two digit month
#define  CAL_MON_TM(M)  ((M) - 1)

// ########################################################
// Time manipulation functions
// ########################################################

/*
 * Write to serial a digit with zero padding if needed.
 *
 * Param:
 * - int digits
 */
static void inline printDigits(int d) {
  if (d >= 0 && d < 10)
    Serial.print('0');
  Serial.print(d);
}

/*
 * Write to serial a digit with zero padding if needed.
 *
 * Param:
 * - float n
 */
static void inline printDigits(float f) {
  if (f >= 0.0 && f < 10.0)
    Serial.print('0');
  Serial.print(f);
}

/*
 * Writes to Serial the clock (date and time) in human readable format.
 *
 * Param:
 * - struct tm  *tm: struct tm from the time.h (avr-libc)
 * - const char *tz: string for the timezone, if not used set to NULL
 */
static void printTime(struct tm *tm, const char *tz = NULL, const bool newl = true) {
  printDigits(tm->tm_hour);
  Serial.print(':');
  printDigits(tm->tm_min);
  Serial.print(':');
  printDigits(tm->tm_sec);
  Serial.print(' ');
  Serial.print(tm->tm_mday);
  Serial.print('/');
  Serial.print(TM_MON_CAL(tm->tm_mon));      // avr-libc time.h: months in [0, 11]
  Serial.print('/');
  Serial.print(TM_YEAR_CAL(tm->tm_year));    // avr-libc time.h: years since 1900
  Serial.print(' ');
  Serial.print(tm->tm_wday);
  if (tz != NULL) {
    Serial.print(' ');
    Serial.print(tz);
  }
  if (newl) {
    Serial.println();
  }
}

/*
 * Writes to Serial the clock (date and time) in human readable format.
 *
 * Param:
 * - time_t time: time from the time.h (avr-libc)
 * - const char *tz: string for the timezone, if not used set to NULL
 */
static void printTime(time_t time, const char *tz = NULL, const bool newl = true) {
  struct tm tm;

  memset((void*) &tm, 0, sizeof(tm));
  gmtime_r(&time, &tm);

  printTime(&tm, tz, newl);
}

/*
 * Converts the date/time to standard Unix epoch format, using time.h library (avr-libc)
 *
 * Param:
 * - int16_t YYYY: year (given as ex. 2017)
 * - int8_t MM: month [1, 12]
 * - int8_t DD: day of the month [1, 31]
 * - int8_t hh: hour [0, 23]
 * - int8_t mm: minute [0, 59]
 * - int8_t ss: second [0, 59]
 */
static time_t makeTime(int16_t YYYY, int8_t MM, int8_t DD, int8_t hh, int8_t mm, int8_t ss) {
  struct tm tm;

  memset((void*) &tm, 0, sizeof(tm));

  tm.tm_year = CAL_YEAR_TM(YYYY);   // avr-libc time.h: years since 1900
  tm.tm_mon  = CAL_MON_TM(MM);      // avr-libc time.h: months in [0, 11]
  tm.tm_mday = DD;
  tm.tm_hour = hh;
  tm.tm_min  = mm;
  tm.tm_sec  = ss;
  return mk_gmtime(&tm);
}

/*
 * Converts the date/time to standard Unix epoch format, using time.h library (avr-libc).
 * Fills the tm struct parameter.
 *
 * Param:
 * - struct tm *tm: pointer to the tm structure to be filled
 * - int16_t YYYY: year (given as ex. 2017)
 * - int8_t MM: month [1, 12]
 * - int8_t DD: day of the month [1, 31]
 * - int8_t hh: hour [0, 23]
 * - int8_t mm: minute [0, 59]
 * - int8_t ss: second [0, 59]
 */
static time_t makeTime(struct tm *tm, int16_t YYYY, int8_t MM, int8_t DD, int8_t hh, int8_t mm, int8_t ss) {
  memset((void*) tm, 0, sizeof(*tm));

  tm->tm_year = CAL_YEAR_TM(YYYY);  // avr-libc time.h: years since 1900
  tm->tm_mon  = CAL_MON_TM(MM);     // avr-libc time.h: months in [0, 11]
  tm->tm_mday = DD;
  tm->tm_hour = hh;
  tm->tm_min  = mm;
  tm->tm_sec  = ss;

  // Set weekday and yearday
  return mktime(tm);
}

#endif /* TIMEUTILS_H_ */
