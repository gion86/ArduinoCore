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

// ########################################################
// Time manipulation functions
// ########################################################

/*
 * Write to serial a digit with zero padding if needed.
 *
 * Param:
 * - int digits
 */
static void inline printDigits(int digits) {
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

/*
 * Writes to Serial the clock (date and time) in human readable format.
 *
 * Param:
 * - struct tm  *tm: struct tm from the time.h (avr-libc)
 * - const char *tz: string for the timezone, if not used set to NULL
 */
static void printTime(struct tm *tm, const char *tz = NULL) {
  printDigits(tm->tm_hour);
  Serial.print(':');
  printDigits(tm->tm_min);
  Serial.print(':');
  printDigits(tm->tm_sec);
  Serial.print(' ');
  Serial.print(tm->tm_mday);
  Serial.print('/');
  Serial.print(tm->tm_mon + 1);              // avr-libc time.h: months in [0, 11]
  Serial.print('/');
  Serial.print(tm->tm_year + 1900);          // avr-libc time.h: years since 1900

  Serial.print(' ');
  Serial.print(tm->tm_wday);

  if (tz != NULL) {
    Serial.print(' ');
    Serial.print(tz);
  }

  Serial.println();
}

/*
 * Writes to Serial the clock (date and time) in human readable format.
 *
 * Param:
 * - time_t time: time from the time.h (avr-libc)
 * - const char *tz: string for the timezone, if not used set to NULL
 */
static void printTime(time_t time, const char *tz = NULL) {
  struct tm tm;

  memset((void*) &tm, 0, sizeof(tm));
  gmtime_r(&time, &tm);

  printTime(&tm, tz);
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

  tm.tm_year = YYYY - 1900;         // avr-libc time.h: years since 1900
  tm.tm_mon  = MM - 1;              // avr-libc time.h: months in [0, 11]
  tm.tm_mday = DD;
  tm.tm_hour = hh;
  tm.tm_min  = mm;
  tm.tm_sec  = ss;
  return mk_gmtime(&tm);
}

/*
 * Converts the date/time to standard Unix epoch format, using time.h library (avr-libc).
 * Fills the struct tm parameter.
 *
 * Param:
 * - int16_t YYYY: year (given as ex. 2017)
 * - int8_t MM: month [1, 12]
 * - int8_t DD: day of the month [1, 31]
 * - int8_t hh: hour [0, 23]
 * - int8_t mm: minute [0, 59]
 * - int8_t ss: second [0, 59]
 */
static void makeTime(struct tm *tm, int16_t YYYY, int8_t MM, int8_t DD, int8_t hh, int8_t mm, int8_t ss) {
  memset((void*) tm, 0, sizeof(*tm));

  tm->tm_year = YYYY - 1900;         // avr-libc time.h: years since 1900
  tm->tm_mon  = MM - 1;              // avr-libc time.h: months in [0, 11]
  tm->tm_mday = DD;
  tm->tm_hour = hh;
  tm->tm_min  = mm;
  tm->tm_sec  = ss;
}

#endif /* TIMEUTILS_H_ */
