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
 * FILENAME		:	StdAfx.cpp
 * PURPOSE       :	Helper class for serializing CObjects
 * SCOPE		:	YeaSoft MFC GUI Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/
#include "StdAfx.h"

#include <yMfcUtil.h>

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
BOOL CObjectSerializer::Load (LPCTSTR pszFileName, BOOL bReportException /* = FALSE */)
{
	if ( !m_pObj ) {
		return FALSE;
	}

	CFileException	fe;
	CDocument		dc;	// needed for emulating all that stuff....

	CFile* pFile = dc.GetFile (
		pszFileName,
		CFile::modeRead|CFile::shareDenyWrite,
		&fe
	);
	if ( pFile == NULL ) {
		SetLastException (new CFileException (fe.m_cause, fe.m_lOsError, fe.m_strFileName));
		if ( bReportException ) {
			dc.ReportSaveLoadException (pszFileName, &fe, FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		}
		return FALSE;
	}

	CArchive loadArchive (pFile, CArchive::load | CArchive::bNoFlushOnDelete);
	loadArchive.m_pDocument		= &dc;
	loadArchive.m_bForceFlat	= FALSE;

	try {
		CWaitCursor wait;
		if ( pFile->GetLength() != 0 ) {
			// load me
			PreSerializeObject (loadArchive);
			m_pObj->Serialize (loadArchive);
			PostSerializeObject (loadArchive);
		}
		loadArchive.Close ();
		dc.ReleaseFile (pFile, FALSE);
	}
	catch ( CException *pEx ) {
		SetLastException (pEx);
		dc.ReleaseFile (pFile, TRUE);

		if ( bReportException ) {
			TRY {
				dc.ReportSaveLoadException (pszFileName, pEx, FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
			}
			END_TRY
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CObjectSerializer::Save (LPCTSTR pszFileName, BOOL bReportException /* = FALSE */)
{
	if ( !m_pObj ) {
		return FALSE;
	}

	CFileException	fe;
	CDocument		dc;	// needed for emulating all that stuff....

	CFile * pFile = dc.GetFile (
		pszFileName,
		CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive,
		&fe
	);

	if ( pFile == NULL ) {
		SetLastException (new CFileException (fe.m_cause, fe.m_lOsError, fe.m_strFileName));
		if ( bReportException ) {
			dc.ReportSaveLoadException (pszFileName, &fe, TRUE, AFX_IDP_INVALID_FILENAME);
		}
		return FALSE;
	}

	CArchive saveArchive (pFile, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_pDocument		= &dc;
	saveArchive.m_bForceFlat	= FALSE;
	try {
		CWaitCursor wait;
		PreSerializeObject (saveArchive);
		m_pObj->Serialize (saveArchive);     // save me
		PostSerializeObject (saveArchive);
		saveArchive.Close();
		dc.ReleaseFile (pFile, FALSE);
	}
	catch ( CException *pEx ) {
		SetLastException (pEx);
		dc.ReleaseFile (pFile, TRUE);

		if ( bReportException ) {
			TRY {
				dc.ReportSaveLoadException (pszFileName, pEx, TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
			}
			END_TRY
		}
		return FALSE;
	}

	return TRUE;        // success
}

void CObjectSerializer::SetLastException (CException *pException)
{
	if ( m_pLastException != pException ) {
		if ( m_pLastException ) {
			m_pLastException->Delete ();
		}
		m_pLastException = pException;
	}
}

//
// EoF
////////