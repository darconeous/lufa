/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/*
   This is a stub driver header file, for implementing custom board
   layout hardware with compatible LUFA board specific drivers. If
   the library is configured to use the BOARD_USER board mode, this
   driver file should be completed and copied into the "/Board/" folder
   inside the application's folder.

   This stub is for the board-specific component of the LUFA Buttons driver,
   for the control of physical board-mounted GPIO pushbuttons.
*/


/*
 * Copyright (c) 2006, Technical University of Munich
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Simon Barner <barner@in.tum.de>
 *
 * @(#)$$
 */

#ifndef __BUTTONS_USER_H__
#define __BUTTONS_USER_H__

	/* Includes: */
		// TODO: Add any required includes here

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_BUTTONS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Buttons.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Button mask for the first button on the board. */
			#define BUTTONS_BUTTON1     1

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void Buttons_Init(void)
			{
				// TODO: Initialize the appropriate port pins as an inputs here, with pull-ups
			}

			static inline uint8_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Buttons_GetStatus(void)
			{
                uint8_t tests;
                uint8_t matches;
                static const uint8_t total_tests=255;
                /*    
                 Three pads on RZUSBSTICK go: GND PD3 PD2
                 
                 We pulse PD3, and check for that pattern on PD2.
                 
                 A (moist) finger across those three pads should be enough
                 to bridge these
                 */
                
                //Output
                DDRD |= 1<<PD3;
                
                //Input
                DDRD &= ~(1<<PD2);
                
                tests = total_tests;
                matches = 0;
                while(tests) {
                    
                    //Set bit PD3 to value of LSB of 'tests'
                    PORTD = (PORTD & ~(1<<PD3)) | ( (tests & 0x01) << PD3);
                    
                    //Allow changes to propogate
                    _delay_us(1);
                    
                    //Check if PD2 matches what we set PD3 to
                    if ((PIND & (1<<PD2)) == ((tests & 0x01) << PD2)) {
                        matches++;      
                    }
                    
                    tests--;
                }
                
                if (matches > (uint8_t)(total_tests*0.7)) {
                    return 0xFF;
                }
                
                return 0;
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

