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
 * FILENAME		:	DlgFileEx.cpp
 * PURPOSE		:	Special Purpose File Dialogs
 * SCOPE		:	YeaSoft MFC GUI Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/
#include "StdAfx.h"

#ifndef __AFXPRIV_H__
#include <afxpriv.h>
#endif
#include <yMfcUtil.h>

/*==================================================================================*
 * THE EXTENDED FILE DIALOG
 *==================================================================================*/
IMPLEMENT_DYNAMIC(CFileDialogEx, CFileDialog)

CFileDialogEx::CFileDialogEx(BOOL bOpenFileDialog,
	LPCTSTR lpszDefExt, LPCTSTR lpszFileName, DWORD dwFlags,
	LPCTSTR lpszFilter, CWnd* pParentWnd)
	
	: CFileDialog (bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}

typedef struct tagOFNEX { 
	DWORD			lStructSize; 
	HWND			hwndOwner; 
	HINSTANCE		hInstance; 
	LPCTSTR			lpstrFilter; 
	LPTSTR			lpstrCustomFilter; 
	DWORD			nMaxCustFilter; 
	DWORD			nFilterIndex; 
	LPTSTR			lpstrFile; 
	DWORD			nMaxFile; 
	LPTSTR			lpstrFileTitle; 
	DWORD			nMaxFileTitle; 
	LPCTSTR			lpstrInitialDir; 
	LPCTSTR			lpstrTitle; 
	DWORD			Flags; 
	WORD			nFileOffset; 
	WORD			nFileExtension; 
	LPCTSTR			lpstrDefExt; 
	LPARAM			lCustData; 
	LPOFNHOOKPROC	lpfnHook; 
	LPCTSTR			lpTemplateName; 
	void *			pvReserved;
	DWORD			dwReserved;
	DWORD			FlagsEx;
} OPENFILENAMEEX, *LPOPENFILENAMEEX;

int CFileDialogEx::DoModal()
{
	ASSERT_VALID(this);
	ASSERT(m_ofn.Flags & OFN_ENABLEHOOK);
	ASSERT(m_ofn.lpfnHook != NULL); // can still be a user hook

	// zero out the file buffer for consistent parsing later
	ASSERT(AfxIsValidAddress(m_ofn.lpstrFile, m_ofn.nMaxFile));
	DWORD nOffset = lstrlen(m_ofn.lpstrFile)+1;
	ASSERT(nOffset <= m_ofn.nMaxFile);
	memset(m_ofn.lpstrFile+nOffset, 0, (m_ofn.nMaxFile-nOffset)*sizeof(TCHAR));

	// WINBUG: This is a special case for the file open/save dialog,
	//  which sometimes pumps while it is coming up but before it has
	//  disabled the main window.
	HWND hWndFocus = ::GetFocus();
	BOOL bEnableParent = FALSE;
	m_ofn.hwndOwner = PreModal();
	AfxUnhookWindowCreate();
	if (m_ofn.hwndOwner != NULL && ::IsWindowEnabled(m_ofn.hwndOwner))
	{
		bEnableParent = TRUE;
		::EnableWindow(m_ofn.hwndOwner, FALSE);
	}

	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	ASSERT(pThreadState->m_pAlternateWndInit == NULL);

	if (m_ofn.Flags & OFN_EXPLORER)
		pThreadState->m_pAlternateWndInit = this;
	else
		AfxHookWindowCreate(this);

	BYTE bVer = (BYTE) (::GetVersion () & 0x000000ff);

	OPENFILENAMEEX ofnex;

	memset (&ofnex, 0, sizeof (ofnex));
	memcpy (&ofnex, &m_ofn, sizeof (m_ofn));
	ofnex.lStructSize = (bVer >= 5) ? (sizeof(ofnex)) : (sizeof(m_ofn));
	int nResult;
	if (m_bOpenFileDialog)
		nResult = ::GetOpenFileName((LPOPENFILENAME) &ofnex);
	else
		nResult = ::GetSaveFileName((LPOPENFILENAME) &ofnex);
	memcpy (&m_ofn, &ofnex, sizeof (m_ofn));
	m_ofn.lStructSize = sizeof(m_ofn);

	if (nResult)
		ASSERT(pThreadState->m_pAlternateWndInit == NULL);
	pThreadState->m_pAlternateWndInit = NULL;

	// WINBUG: Second part of special case for file open/save dialog.
	if (bEnableParent)
		::EnableWindow(m_ofn.hwndOwner, TRUE);
	if (::IsWindow(hWndFocus))
		::SetFocus(hWndFocus);

	PostModal();
	return nResult ? nResult : IDCANCEL;
}

//
// EoF
////////