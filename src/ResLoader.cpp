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
 * FILENAME		:	ResLoader.cpp
 * PURPOSE		:	The Resource Loader Class
 * SCOPE		:	YeaSoft MFC GUI Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2001/09/26 17:06:05  leopoldo
 * Initial revision
 *
 *============================================================================*/
#include "StdAfx.h"

#include <yMfcUtil.h>
#include <yFiles.h>

/*=============================================================================
 * CLASS IMPLEMENTATION
 *============================================================================*/
CResourceLoader::CResourceLoader ()
{
	m_hData		= NULL;
	m_pData		= NULL;
	m_cbSize	= 0;
}

CResourceLoader::~CResourceLoader ()
{
	Free ();
}

BOOL CResourceLoader::Load (UINT nID, LPCTSTR pszType)
{
	HINSTANCE hInst = AfxFindResourceHandle (MAKEINTRESOURCE(nID), pszType);
	return Load (hInst, MAKEINTRESOURCE(nID), pszType);
}

BOOL CResourceLoader::Load (LPCTSTR pszName, LPCTSTR pszType)
{
	HINSTANCE hInst = AfxFindResourceHandle (pszName, pszType);
	return Load (hInst, pszName, pszType);
}

BOOL CResourceLoader::Load (HINSTANCE hInst, UINT nID, LPCTSTR pszType)
{
	return Load (hInst, MAKEINTRESOURCE(nID), pszType);
}

BOOL CResourceLoader::Load (HINSTANCE hInst, LPCTSTR pszName, LPCTSTR pszType)
{
	
	HRSRC hResource = ::FindResource (hInst, pszName, pszType);
	if ( !hResource ) {
		return FALSE;
	}
	HGLOBAL hData = ::LoadResource (hInst, hResource);
	if ( !hData ) {
		return FALSE;
	}

	Free ();

	m_hData		= hData;
	m_pData		= ::LockResource (hData);
	m_cbSize	= ::SizeofResource (hInst, hResource);
	return TRUE;
}

void CResourceLoader::Free ()
{
	if ( m_hData ) {
		::UnlockResource (m_hData);
		::FreeResource (m_hData);
	}
	m_hData		= NULL;
	m_pData		= NULL;
	m_cbSize	= 0;
}

BOOL CResourceLoader::Export (LPCTSTR pszFileName, ...) const
{
	va_list va;
	va_start (pszFileName, va);
	BOOL bRet = ExportVa (pszFileName, va);
	va_end (va);
	return bRet;
}

BOOL CResourceLoader::ExportVa (LPCTSTR pszFileName, va_list va) const
{
	if ( !m_pData ) {
		return FALSE;
	}

	YPathString		ys;
	YFile			outFile;

	ys.FormatV (pszFileName, va);
	if ( !outFile.Open (ys, YFile::modeCreate|YFile::modeWrite) ) {
		return FALSE;
	}
	if ( !outFile.Write (m_pData, m_cbSize) ) {
		outFile.Close ();
		ys.DeleteFiles (TRUE);
		return FALSE;
	}
	outFile.Close ();
	return TRUE;
}

//
// EoF
////////