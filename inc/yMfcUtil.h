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
 * FILENAME		:	yMfcUtil.h
 * PURPOSE		:	The YeaSoft Shared GUI Utilities Library
 * SCOPE		:	YeaSoft MFC GUI Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2001/09/26 17:01:36  leopoldo
 * Initial revision
 *
 *============================================================================*/
#ifndef __yMfcUtil_h__
#define __yMfcUtil_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yFixStr_h__
#include <yFixStr.h>
#endif

/*=============================================================================
 * DLL LINKAGE STUFF
 *============================================================================*/
#ifndef YEAUTIL_EXT_CLASS
#define YEAUTIL_EXT_CLASS __declspec(dllimport)
#endif

/*=============================================================================
 * THE BASE APPLICATION CLASS
 *============================================================================*/
class YEAUTIL_EXT_CLASS YWinApp : public CWinApp
{
// Construction
public:
	YWinApp					();

// Attributes
public:
	// Environment
	BOOL						IsChicago				() const;
	LPCTSTR						GetAppPath				() const { return m_ysAppPath; }

	// HTML Help System
	void						SetHelpName				(LPCTSTR pszHelpName = NULL);
	void						SetFullHelpFileName		(LPCTSTR pszHelpFile);
	LPCTSTR						GetFullHelpFileName		() const { return m_ysHlpName; }

// Operations
public:
	// Dialog boxes
	void						ShowAboutBox			(LPCTSTR pszIcon, LPCTSTR pszTitle);
	void						ShowLicenseList			() const;
	void						ShowLicenseError		(UINT nID, DWORD dwError) const;
	void						ShowLicenseError		(LPCTSTR pszCaption, DWORD dwError) const;
	void						ShowLicenseError		(UINT nID) const { ShowLicenseError (nID, GetLastLicenseError ()); }
	void						ShowLicenseError		(LPCTSTR pszCaption) const { ShowLicenseError (pszCaption, GetLastLicenseError ()); }

	// HTML Help System
	BOOL						HtmlHelpContents		();
	BOOL						HtmlHelpTopic			(LPCTSTR pszTopic);
	BOOL						HtmlHelpIndex			();
	BOOL						HtmlHelpFinder			();
	BOOL						HtmlHelpKeyWord			(LPCTSTR pszKeyWord);
	BOOL						HtmlHelpSearch			(LPCTSTR pszSearchString);
	BOOL						HtmlHelpContext			(DWORD dwContextId);
	BOOL						HtmlHelpContextMenu		(LPDWORD lpCtrlToContextMap, LPCTSTR pszPopupFile);
	BOOL						HtmlHelpMessage			(LPDWORD lpCtrlToContextMap, LPCTSTR pszPopupFile);
	void						HtmlHelpQuit			();

	// License Manager
	static BOOL					ConnectLicenseManager	(GUID guid, LPCTSTR pszAddress);
	static BOOL					DisconnectLicenseManager();

	static BOOL					AddLicense				(LPCTSTR pszKey);
	static BOOL					AddLicenseFile			(LPCTSTR pszFileName);

	static DWORD				GetLastLicenseError		();
	static CString				GetLicenseErrorString	(DWORD dwError);

	static BOOL					AllocateLicense			(WORD wCode, WORD nCount = 1);
	static BOOL					TestLicense				(WORD nCount, ...);
	static BOOL					FreeLicense				(WORD wCode, WORD nCount = 1);

	static BOOL					TestExpiration			(time_t *ptExpiration, ...);

	BOOL						TestLicenseEx			(LPCTSTR pszCaption, WORD nCount, ...) const;
	BOOL						TestLicenseEx			(UINT nIDCaption, WORD nCount, ...) const;

// Overrides
public:
	virtual BOOL				HtmlHelper				(DWORD dwData, UINT uCommand, LPCTSTR pszParam);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(YWinApp)
	public:
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	virtual BOOL InitApplication();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(YWinApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	// implementation
	YPathString					m_ysAppPath;
	YPathString					m_ysHlpName;

	DECLARE_DYNAMIC(YWinApp)
};

/*==================================================================================*
 * THE OBJECT SERIALIZER
 *==================================================================================*/
class YEAUTIL_EXT_CLASS CObjectSerializer
{
// Construction
public:
	CObjectSerializer			(CObject *pObj = NULL) { m_pObj = pObj; m_pLastException = NULL; }
	~CObjectSerializer			() { SetLastException (NULL); }

// Attributes
public:
	void						SetObject				(CObject *pObj) { m_pObj = pObj; SetLastException (NULL); }
	CObject *					GetObject				() const { return m_pObj; }
	CException *				GetLastException		() const { return m_pLastException; }

// Operations
public:
	BOOL						Load					(LPCTSTR pszFileName, BOOL bReportException = FALSE);
	BOOL						Save					(LPCTSTR pszFileName, BOOL bReportException = FALSE);

// Overridables
public:
	virtual void				PreSerializeObject		(CArchive &ar) { }
	virtual void				PostSerializeObject		(CArchive &ar) { }

// Implementation
protected:
	void						SetLastException		(CException *pException);

// Implementation
protected:
	CObject *					m_pObj;
	CException *				m_pLastException;
};

/*==================================================================================*
 * THE RESOUREC LOADER
 *==================================================================================*/
class YEAUTIL_EXT_CLASS CResourceLoader
{
// Construction
public:
	CResourceLoader				();
	~CResourceLoader			();

// Attributes
public:
	void *						GetData					() const { return m_hData; }
	UINT						GetSize					() const { return m_cbSize; }

// Operations
public:
	BOOL						Load					(UINT nID, LPCTSTR pszType);
	BOOL						Load					(LPCTSTR pszName, LPCTSTR pszType);
	BOOL						Load					(HINSTANCE hInst, UINT nID, LPCTSTR pszType);
	BOOL						Load					(HINSTANCE hInst, LPCTSTR pszName, LPCTSTR pszType);
	void						Free					();
	BOOL						Export					(LPCTSTR pszFileName, ...) const;
	BOOL						ExportVa				(LPCTSTR pszFileName, va_list va) const;

// Implementation
protected:
	HGLOBAL						m_hData;
	void *						m_pData;
	UINT						m_cbSize;
};

/*==================================================================================*
 * THE EXTENDED FILE DIALOG
 *==================================================================================*/
class YEAUTIL_EXT_CLASS CFileDialogEx : public CFileDialog
{
	DECLARE_DYNAMIC(CFileDialogEx)

public:
// Constructors
	CFileDialogEx(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

// Operations
	virtual int DoModal();
};


#endif //__yMfcUtil_h__
//
// EoF
////////