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
 * FILENAME		:	yMfcUtil.rc2
 * PURPOSE		:	Version Information mangler include
 * SCOPE		:	YeaSoft MFC GUI Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/
#ifndef __yVerGen_h__
#define __yVerGen_h__

/*==================================================================================*
 * RELATED INCLUDES
 *==================================================================================*/
#ifndef __yNames_h__
#include <yNames.h>
#endif

/*==================================================================================*
 * INFORMATION CHECK
 *==================================================================================*/
#ifndef BUILD_NUMBER
#error Missing Build Information.
#endif
#ifndef VER_PROD_MAJOR
#error Missing Product Information
#endif

/*==================================================================================*
 * INCLUDE ORDER CHECK
 *==================================================================================*/
#ifndef MODULE_TYPE
#error Missing MODULE_TYPE definition (can be from 1 to 4) before icVerGen.h inclusion!
#endif
#ifndef MODULE_STEPPING
#error Missing MODULE_STEPPING definition before icVerGen.h inclusion!
#endif
#ifndef MODULE_NAME
#error Missing MODULE_NAME definition before icVerGen.h inclusion!
#endif
#ifndef MODULE_DESCRIPTION
#error Missing MODULE_DESCRIPTION definition before icVerGen.h inclusion!
#endif
#ifndef MODULE_FILENAME
#error Missing MODULE_FILENAME definition before icVerGen.h inclusion!
#endif

/*==================================================================================*
 * PLATFORM DEFINES
 *==================================================================================*/
#if !defined(WIN32) && !defined(__TANDEM)
#error Unsupported Platform (Neither WIN32 nor Tandem NSK)
#endif

#ifdef WIN32

#define VER_FILEOS					VOS_NT_WINDOWS32
#define VER_OSVER					"NT"

#define STR_FUNC					_stprintf
#define STR_MODIFIER(a)				_T((a))

#endif //WIN32

#ifdef __TANDEM

#define VER_FILEOS					0
#define VER_OSVER					"NSK"

#define VS_FF_DEBUG					0
#define VS_FF_PRIVATEBUILD			0
#define VS_FF_PRERELEASE			0
#define VS_FFI_FILEFLAGSMASK		0
#define VFT_APP						0
#define VFT_DLL						0
#define VFT_DRV						0
#define VFT2_UNKNOWN				0
#define VFT2_DRV_PRINTER			0

#define STR_FUNC					sprintf
#define STR_MODIFIER(a)				(a)

#endif //__TANDEM

/*==================================================================================*
 * GENERIC DEFINES
 *==================================================================================*/
#define VER_CP_UNICODE				1200

#define VER_LC_NEUTRAL				0x0000
#define VER_LC_ENGLISH				0x0409
#define VER_LC_GERMAN				0x0407
#define VER_LC_ITALIAN				0x0410

#define VER_LS_NEUTRAL				"000004b0"
#define VER_LS_ENGLISH				"040904b0"
#define VER_LS_GERMAN				"040704b0"
#define VER_LS_ITALIAN				"041004b0"

#ifdef MODULE_GERMAN
	#define VER_HAS_GERMAN
#endif
#ifdef MODULE_ITALIAN
	#define VER_HAS_GERMAN
#endif

/*==================================================================================*
 * PRODUCT VERSION TAGS
 *==================================================================================*/
#if (BUILD_RELEASE > 0)
	#define VER_TAG_STR				""
#else
	#define VER_TAG_STR				"ß"
#endif

#if (BUILD_OFFICIAL > 0)
	#define VER_BLD_STR				""
#else
	#define VER_BLD_STR				"(p)"
#endif

#if defined(_DEBUG)
	#define VER_TYPE_STR			"Debug"
	#define VER_TYPE_STR2			" (Debug)"
#else
	#define VER_TYPE_STR			"Release"
	#define VER_TYPE_STR2			""
#endif

#define VER_PRODUCTVERSION_STR		VER_PROD_MAJOR_STR "." VER_PROD_MINOR_STR VER_BLD_STR VER_TYPE_STR2 " " VER_PROD_TAG_STR
#define VER_PRODUCTVERSION			VER_PROD_MAJOR,VER_PROD_MINOR,0,0

/*==================================================================================*
 * FILE FLAG DEFINES
 *==================================================================================*/
// default is nodebug
#if !defined(_DEBUG)
	#define VER_DEBUG				0
#else
	#define VER_DEBUG				VS_FF_DEBUG
#endif

/* default is privatebuild */
#if (BUILD_OFFICIAL > 0)
	#define VER_PRIVATEBUILD		0
#else
	#define VER_PRIVATEBUILD		VS_FF_PRIVATEBUILD
#endif

/* default is prerelease */
#if (BUILD_RELEASE > 0)
	#define VER_PRERELEASE			0
#else
	#define VER_PRERELEASE			VS_FF_PRERELEASE
#endif

#define VER_FILEFLAGSMASK			VS_FFI_FILEFLAGSMASK
#define VER_FILEFLAGS				(VER_PRIVATEBUILD|VER_PRERELEASE|VER_DEBUG)

/*==================================================================================*
 * WINDOWS SPECIFIC STUFF
 *==================================================================================*/
#define VFT_VISIO_ADDON				0x00000010L

/*==================================================================================*
 * USEFUL MAKROS
 *==================================================================================*/
#define GETMAJOR(n)					HIBYTE(HIWORD(n))
#define GETMINOR(n)					LOBYTE(HIWORD(n))
#define GETBUILD(n)					LOWORD(n)

#define MAKEVERSIONSTRING(sz)		(STR_FUNC((sz),STR_MODIFIER("Version %i.%02i.%i"VER_TAG_STR" (WIN-%s) "VER_TYPE_STR" Build %i"),VER_MAJOR,VER_MINOR,VER_STEPPING,VER_OSVER,VER_BUILD))
#define MAKESHORTVERSIONSTRING(sz)	(STR_FUNC((sz), STR_MODIFIER("%i.%02i.%i.%i"), VER_MAJOR, VER_MINOR, VER_STEPPING, VER_BUILD))

/*==================================================================================*
 * STATIC VERSION INFORMATION
 *==================================================================================*/
#define VER_LEGALCOPYRIGHT_STR		"Copyright \251 " VER_COPYRIGHTDATES_STR " " NAM_SHORTCOMPANYNAME_STR
#define VER_SHORTCOPYRIGHT_STR		"Copyright \251 " VER_COPYRIGHTDATES_STR
#define VER_LEGALCOPYRIGHT_OEM		"Copyright (c) " VER_COPYRIGHTDATES_STR " " NAM_SHORTCOMPANYNAME_STR
#define VER_SHORTCOPYRIGHT_OEM		"Copyright (c) " VER_COPYRIGHTDATES_STR

#define VER_COMPANYNAME_STR			NAM_COMPANYNAME_STR
#define VER_PRODUCTNAME_STR			NAM_PRODUCTNAME_STR
#define VER_LEGALTRADEMARKS_STR		NAM_LEGALTRADEMARKS_STR
#define VER_COPYRIGHTDATES_STR		NAM_COPYRIGHTDATES_STR

/*==================================================================================*
 * SIMPLE VERSION INFORMATION
 *==================================================================================*/
#define VER_BUILD					BUILD_NUMBER
#define VER_MINOR					VER_PROD_MINOR
#define VER_MAJOR					VER_PROD_MAJOR
#define VER_BUILD_STR				BUILD_STRING
#define VER_MINOR_STR				VER_PROD_MINOR_STR
#define VER_MAJOR_STR				VER_PROD_MAJOR_STR
#define VER_YEAR					VER_PROD_YEAR
#define VER_MONTH					VER_PROD_MONTH
#define VER_DAY						VER_PROD_DAY
#define VER_STEPPING				MODULE_STEPPING
#define VER_STEPPING_STR			MODULE_STEPPING_STR
#define VER_INTERNALNAME_STR		MODULE_NAME
#define VER_FILEDESCRIPTION_STR		MODULE_DESCRIPTION
#define VER_ORIGINALFILENAME_STR	MODULE_FILENAME

/*==================================================================================*
 * COMPOUND VERSION INFORMATION
 *==================================================================================*/
#define VER_FILEVERSION				VER_MAJOR,VER_MINOR,VER_STEPPING,VER_BUILD
#define VER_FILEVERSION_STR			VER_MAJOR_STR "." VER_MINOR_STR "." VER_STEPPING_STR "." VER_BUILD_STR
#define VER_WORD					(VER_MAJOR << 8) | VER_MINOR
#define VER_DWORD					MAKELONG(VER_BUILD,VER_WORD)

/*==================================================================================*
 * FILE TYPE DEFINITION
 *==================================================================================*/
#if MODULE_TYPE == 1
#define VER_FILETYPE				VFT_APP
#define VER_FILESUBTYPE				VFT2_UNKNOWN
#elif MODULE_TYPE == 2
#define VER_FILETYPE				VFT_DLL
#define VER_FILESUBTYPE				VFT2_UNKNOWN
#elif MODULE_TYPE == 3
#define VER_FILETYPE				VFT_DRV
#define VER_FILESUBTYPE				VFT2_DRV_PRINTER
#elif MODULE_TYPE == 4
#define VER_FILETYPE				VFT_VISIO_ADDON
#define VER_FILESUBTYPE				VFT2_UNKNOWN
#else
#error Bad value specified for MODULE_TYPE in version.h (can be from 1 to 4)
#endif

#endif //__yVerGen_h__
//
// EoF
////////
