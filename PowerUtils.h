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
#ifndef POWERUTILS_H_
#define POWERUTILS_H_

#include <avr/sleep.h>

/*
 * Put the micro to sleep.
 * Sleep modes: see iom*.h file from AVR library.
 */
static void systemSleep(uint8_t mode) {
  set_sleep_mode(mode);
  sleep_enable();
  sleep_mode();

  // sleeping ...
  sleep_disable(); // wake up fully
}

/*
 * Setup watchdog timeout and start for AVR Mega CPUs.
 * Watchdog modes: 0 = 16ms, 1 = 32ms, 2 = 64ms, 3 = 128ms, 4 = 250ms,
 *                 5 = 500ms, 6 =1  sec, 7 = 2 sec, 8 = 4 sec, 9 = 8sec
 */
void setupWatchdog(uint8_t wdmode) {
  uint8_t wdreg;

  if (wdmode > 9)
    wdmode = 9;
  wdreg = wdmode & 7;

  if (wdmode > 7)
    wdreg |= (1 << 5);
  wdreg |= (1 << WDCE);

  // Clear the reset flag.
  MCUSR &= ~(1 << WDRF);

  // Start timed sequence: in order to change WDE or the prescaler, we need to
  // set WDCE (This will allow updates for 4 clock cycles).
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  // Set new watchdog timeout prescaler value.
  WDTCSR = wdreg;

  // Enable the WD interrupt (note no reset).
  WDTCSR |= _BV(WDIE);
}

/*
 * Stop watchdog count.
 */
void stopWatchdog() {
  MCUSR &= ~(1 << WDRF);

  // Write logical one to WDCE and WDE
  // Keep old prescaler setting to prevent unintentional time-out
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  // Turn off WDT
  WDTCSR = 0x00;
}

#endif /* POWERUTILS_H_ */
