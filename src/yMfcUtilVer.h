/*=============================================================================
 * This is a part of the YeaSoft Software Development Kit.
 * Copyright (C) 2001 YEAsoft Int'l.
 * All rights reserved.
 *=============================================================================
 * Copyright (c) 2001 YEAsoft Int'l (Leo Moll, Andrea Pennelli).
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *=============================================================================
 * FILENAME		:	yMfcUtilVer.h
 * PURPOSE		:	Version Information
 * SCOPE		:	YeaSoft MFC GUI Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/
#ifndef __yMfcUtilVer_h__
#define __yMfcUtilVer_h__

/*==================================================================================*
 * BUILD INFORMATION
 *==================================================================================*/
#define BUILD_NUMBER				100
#define BUILD_STRING				"100"
#define BUILD_MACHINE				"HELLRAISER"
#define BUILD_USER					"leo"
#define BUILD_DATE					"2001/09/25"
#define BUILD_TIME					"17:00:00"
#define BUILD_OFFICIAL				0
#define BUILD_RELEASE				0

/*==================================================================================*
 * SPECIFIC PRODUCT INFORMATION
 *==================================================================================*/
#define VER_PROD_MAJOR				1
#define VER_PROD_MINOR				0
#define VER_PROD_MAJOR_STR			"1"
#define VER_PROD_MINOR_STR			"0"
#define VER_PROD_TAG_STR			""
#define VER_PROD_BASELINE			""
#define VER_PROD_YEAR				2001
#define VER_PROD_MONTH				9
#define VER_PROD_DAY				25

/*==================================================================================*
 * MY DEFINITIONS (See below for documentation...)
 *==================================================================================*/
#define MODULE_TYPE				2
#define MODULE_STEPPING			1
#define MODULE_STEPPING_STR		"1"
#define MODULE_NAME				"yMfcUtil"
#define MODULE_DESCRIPTION		"MFC Shared Utility Library"
#define MODULE_FILENAME			"yMfcUtil.dll"

/*==================================================================================*
 * HELP
 *==================================================================================*/
//
// MODULE_TYPE:
//		Type of the module. Can be
//			1		Application/Service
//			2		DLL (Dynamic Link Library)
//			3		Printer Driver
//
//
// MODULE_STEPPING:
//		Private build number for this module
//		MUST be an integer (0-65535)
//		String representation must also be
//		provided as MODULE_STEPPING_STR
//
//
// MODULE_NAME:
//		Short module name up to 8 chars. This is a
//		very important parameter since it will be
//		the internal module name for many purposes.
//
//
// MODULE_DESCRIPTION:
//		Short text containing a descriptive
//		name for the module (e.g. "InfiScript Compiler")
//
//
// MODULE_FILENAME:
//
//		Original filename of the module
//
/*==================================================================================*
 * RELATED INCLUDES
 *==================================================================================*/
#include <yVerGen.h>

#endif //__yMfcUtilVer_h__

//
// EoF
////////
