/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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

/** \file
 *
 *  Header file for V2Protocol.c.
 */

#ifndef _V2_PROTOCOL_
#define _V2_PROTOCOL_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/eeprom.h>

		#include <LUFA/Version.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Peripheral/SPI.h>
		
		#include "../Descriptors.h"
		#include "V2ProtocolConstants.h"

	/* Macros: */
		#define PROGRAMMER_ID       "AVRISP_MK2"
		#define PROGRAMMER_ID_LEN   (sizeof(PROGRAMMER_ID) - 1)
		
	/* Type Defines: */
		typedef struct
		{
			uint8_t ParameterID;
			uint8_t ParameterValue;
		} ParameterItem_t;

	/* Function Prototypes: */
		void V2Protocol_Init(void);
		void V2Protocol_ProcessCommand(void);
		
		#if defined(INCLUDE_FROM_V2PROTOCOL_C)
			static void    V2Protocol_ReconfigureSPI(void);
			static void    V2Protocol_ChangeTargetResetLine(bool ResetTarget);

			static uint8_t V2Protocol_GetParameter(uint8_t ParamID);
			static void    V2Protocol_SetParameter(uint8_t ParamID, uint8_t Value);

			static void    V2Protocol_Command_Unknown(uint8_t V2Command);
			static void    V2Protocol_Command_SignOn(void);
			static void    V2Protocol_Command_GetSetParam(uint8_t V2Command);
			static void    V2Protocol_Command_SPIMulti(void);
		#endif

#endif

