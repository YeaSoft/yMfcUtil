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
 * FILENAME		:	MfcWinApp.cpp
 * PURPOSE		:	The MFC Base Application Class
 * SCOPE		:	YeaSoft MFC GUI Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/
#include "StdAfx.h"

#include <direct.h>
#include <afxpriv.h>
#include <HtmlHelp.h>
#include <yFixStr.h>
#include <yRegistry.h>
#include <lmInterface.h>
#include <ExtListCtrl.h>
#include <yMfcUtil.h>

#include "yUtilRes.h"

/*=============================================================================
 * GLOBAL VARIABLES
 *============================================================================*/
CLicenseManager					licManager;

/*=============================================================================
 * THE ABOUT DIALOG
 *============================================================================*/
class CAboutDialog : public CDialog
{
// Construction
public:
	 CAboutDialog				(CWnd* pParent = NULL);   // standard constructor

// Overridables
protected:

// Attributes
public:

public:
// Dialog Data
	//{{AFX_DATA(CAboutDialog)
	enum { IDD = IDD_ABOUT };
	CStatic	m_ctrlIcon;
	CString m_csTitle;
	CString m_csOwner;
	CString m_csCompany;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HICON						m_hIcon;
};

CAboutDialog::CAboutDialog(CWnd* pParent /*=NULL*/) : CDialog(CAboutDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDialog)
	m_csTitle = _T("");
	m_csOwner = _T("");
	m_csCompany = _T("");
	//}}AFX_DATA_INIT

	YRegistry reg(HKEY_LOCAL_MACHINE);

	if ( reg.Open (_T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"), KEY_READ) ) {
		m_csOwner	= reg.StringGet (_T("RegisteredOwner"));
		m_csCompany	= reg.StringGet (_T("RegisteredOrganization"));
	}
}

void CAboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDialog)
	DDX_Control(pDX, IDC_ABOUT_ICON, m_ctrlIcon);
	DDX_Text(pDX, IDC_ABOUT_TITLE, m_csTitle);
	DDX_Text(pDX, IDC_ABOUT_APP_OWNER, m_csOwner);
	DDX_Text(pDX, IDC_ABOUT_APP_COMPANY, m_csCompany);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDialog, CDialog)
	//{{AFX_MSG_MAP(CAboutDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog message handlers
BOOL CAboutDialog::OnInitDialog() 
{
	CDialog::OnInitDialog ();

	// set caption
	CString csFmt; GetWindowText (csFmt);
	CString csTxt; csTxt.Format (csFmt, AfxGetApp ()->m_pszAppName);
	SetWindowText (csTxt);

	// set icon
	m_ctrlIcon.SetIcon (m_hIcon);

	// Fill memory info
	MEMORYSTATUS MemStat;
	MemStat.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&MemStat);
	csFmt.LoadString(IDS_ABOUT_PHYSMEM);
	csTxt.Format(csFmt, MemStat.dwTotalPhys / 1024L);
	SetDlgItemText(IDC_ABOUT_PHYSICAL_MEM, csTxt);

	csFmt.LoadString(IDS_ABOUT_PHYSFREE);
	csTxt.Format(csFmt, MemStat.dwAvailPhys / 1024L);
	SetDlgItemText(IDC_ABOUT_PHYSICAL_FREE, csTxt);

	struct _diskfree_t diskfree;
	int nDrive = _getdrive (); // use current default drive
	if ( _getdiskfree(nDrive, &diskfree) == 0 ) {
		csFmt.LoadString(IDS_ABOUT_DISKSPACE);
		csTxt.Format(csFmt, (int) (
			(__int64)diskfree.avail_clusters *
			(__int64)diskfree.sectors_per_cluster *
			(__int64)diskfree.bytes_per_sector / ((__int64)1024)),
			nDrive-1 + _T('A'));
	}
 	else {
 		csTxt.LoadString(IDS_ABOUT_DISK_UNAVAIL);
	}
	SetDlgItemText(IDC_ABOUT_DISK_SPACE, csTxt);
	return TRUE;
}
/*=============================================================================
 * LICENSE LIST DIALOG
 *============================================================================*/
class CLicenseList : public CDialog
{
// Construction
public:
	CLicenseList				(const CLicenseManager *pLicManager, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLicenseList)
	enum { IDD = IDD_LIC_DISPLAY };
	CEdit	m_ctrlLicID;
	CExtListCtrl	m_ctrlList;
	CString	m_csLicID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicenseList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLicenseList)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Implementation
protected:
	static CString				LocalSystemDateToStr	(SYSTEMTIME *pst);
	static CString				LocalSystemTimeToStr	(SYSTEMTIME *pst);
	static CString				CTimeToDateStr			(CTime &ct);
	static CString				CTimeToStr				(CTime &ct);

// Implementation
protected:
	const CLicenseManager *		m_pLicManager;
	CFont						m_Font;
};

CLicenseList::CLicenseList(const CLicenseManager *pLicManager, CWnd* pParent /*=NULL*/)
	: CDialog(CLicenseList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLicenseList)
	m_csLicID = _T("");
	//}}AFX_DATA_INIT
	m_pLicManager = pLicManager;
}


CString CLicenseList::LocalSystemDateToStr (SYSTEMTIME *pst)
{
	TCHAR		szDateStr[64];
	CString		cs(_T(""));

	if ( !::GetDateFormat (LOCALE_USER_DEFAULT, DATE_SHORTDATE, pst, NULL, szDateStr, _countof (szDateStr)) ) {
		return cs;
	}
	return CString (szDateStr);
}

CString CLicenseList::LocalSystemTimeToStr (SYSTEMTIME *pst)
{
	TCHAR		szDateStr[64];
	TCHAR		szTimeStr[64];
	CString		cs(_T(""));

	if ( !::GetDateFormat (LOCALE_USER_DEFAULT, DATE_SHORTDATE, pst, NULL, szDateStr, _countof (szDateStr)) ) {
		return cs;
	}
	if ( !::GetTimeFormat (LOCALE_USER_DEFAULT, 0, pst, NULL, szTimeStr, _countof (szTimeStr)) ) {
		return cs;
	}
	return CString (szDateStr) + _T(" ") + CString (szTimeStr);
}

CString CLicenseList::CTimeToDateStr (CTime &ct)
{
	SYSTEMTIME	st;

	ct.GetAsSystemTime (st);

	return LocalSystemDateToStr (&st);
}

CString CLicenseList::CTimeToStr (CTime &ct)
{
	SYSTEMTIME	st;

	ct.GetAsSystemTime (st);

	return LocalSystemTimeToStr (&st);
}

void CLicenseList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLicenseList)
	DDX_Control(pDX, IDC_LIC_MACHID, m_ctrlLicID);
	DDX_Control(pDX, IDC_LIC_LST_LICENSES, m_ctrlList);
	DDX_Text(pDX, IDC_LIC_MACHID, m_csLicID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicenseList, CDialog)
	//{{AFX_MSG_MAP(CLicenseList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenseList message handlers

BOOL CLicenseList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Font.CreateFont (
		-8,
		0,
		0,
		0,
		FW_BOLD,
		FALSE,
		FALSE,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		_T("MS Sans Serif")
	);

	CLMMachineID mid = m_pLicManager->GetMachineID ();
	m_ctrlLicID.SetFont (&m_Font);
	m_csLicID.Format (_T("%08x-%08x-%08x-%08x"), mid.m_dwID1, mid.m_dwID2, mid.m_dwID3, mid.m_dwID4);

	UpdateData (FALSE);

	CRect rc;
	m_ctrlList.GetClientRect (rc);
	rc.right -= ::GetSystemMetrics (SM_CXVSCROLL);

	CString cs;
	cs.LoadString (IDS_COL_LICNAME);
	m_ctrlList.InsertColumn (0, cs);
	m_ctrlList.SetColumnWidth (0, (rc.Width () * 40) / 100);
	cs.LoadString (IDS_COL_LICCOUNT);
	m_ctrlList.InsertColumn (1, cs);
	m_ctrlList.SetColumnWidth (1, (rc.Width () * 10) / 100);
	cs.LoadString (IDS_COL_LICUSE);
	m_ctrlList.InsertColumn (2, cs);
	m_ctrlList.SetColumnWidth (2, (rc.Width () * 10) / 100);
	cs.LoadString (IDS_COL_LICEXPIRE);
	m_ctrlList.InsertColumn (3, cs);
	m_ctrlList.SetColumnWidth (3, (rc.Width () * 18) / 100);
	cs.LoadString (IDS_COL_LICCOMP);
	m_ctrlList.InsertColumn (4, cs);
	m_ctrlList.SetColumnWidth (4, (rc.Width () * 22) / 100);

	for ( int i = 0; i < m_pLicManager->GetLicenseCount (); i++ ) {
		CLicense lic;
		if ( m_pLicManager->GetLicense (i, lic) ) {
			int iIndex = m_ctrlList.InsertItem (m_ctrlList.GetItemCount (), lic.GetDescription ());
			if ( iIndex != -1 ) {
				YString128 ysBuffer;

				// count
				ysBuffer.Assign (lic.GetCount ());
				m_ctrlList.SetItemText (iIndex, 1, ysBuffer);

				// usage count
				ysBuffer.Assign (lic.GetUsageCount ());
				m_ctrlList.SetItemText (iIndex, 2, ysBuffer);

				// expiration
				if ( lic.IsTimeBombed () ) {
					m_ctrlList.SetItemText (iIndex, 3, CTimeToDateStr (CTime (lic.GetExpirationDate ())));
				}

				// restrictions
				ysBuffer = lic.GetComputerName ();
				ysBuffer += (!ysBuffer.IsEmpty ()) ? (_T(" ")) : (_T(""));
				ysBuffer += lic.GetUserName ();
				m_ctrlList.SetItemText (iIndex, 4, ysBuffer);

			}
		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*=============================================================================
 * LICENSE ERROR DIALOG
 *============================================================================*/
class CLicenseError : public CDialog
{
// Construction
public:
	CLicenseError				(const CLicenseManager *pLicManager, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLicenseError)
	enum { IDD = IDD_LIC_ERROR };
	CButton	m_ctrlShowList;
	CEdit	m_ctrlLicID;
	CString	m_csLicID;
	CString	m_csCaption;
	CString	m_csLicError;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicenseError)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLicenseError)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnShowLicenses();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Implementation
protected:
	const CLicenseManager *		m_pLicManager;
	CFont						m_Font;
};

CLicenseError::CLicenseError(const CLicenseManager *pLicManager, CWnd* pParent /*=NULL*/)
	: CDialog(CLicenseError::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLicenseError)
	m_csLicID = _T("");
	m_csCaption = _T("");
	m_csLicError = _T("");
	//}}AFX_DATA_INIT
	m_pLicManager = pLicManager;
}


void CLicenseError::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLicenseError)
	DDX_Control(pDX, IDC_LIC_BTN_SHOWLIC, m_ctrlShowList);
	DDX_Control(pDX, IDC_LIC_MACHID, m_ctrlLicID);
	DDX_Text(pDX, IDC_LIC_MACHID, m_csLicID);
	DDX_Text(pDX, IDC_LIC_ST_CAPTION, m_csCaption);
	DDX_Text(pDX, IDC_LIC_ST_ERROR, m_csLicError);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicenseError, CDialog)
	//{{AFX_MSG_MAP(CLicenseError)
	ON_BN_CLICKED(IDC_LIC_BTN_SHOWLIC, OnBtnShowLicenses)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenseError message handlers

BOOL CLicenseError::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Font.CreateFont (
		-8,
		0,
		0,
		0,
		FW_BOLD,
		FALSE,
		FALSE,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		_T("MS Sans Serif")
	);

	CLMMachineID mid = m_pLicManager->GetMachineID ();
	m_ctrlLicID.SetFont (&m_Font);
	m_csLicID.Format (_T("%08x-%08x-%08x-%08x"), mid.m_dwID1, mid.m_dwID2, mid.m_dwID3, mid.m_dwID4);
	m_ctrlShowList.EnableWindow (m_pLicManager->IsActive ());

	UpdateData (FALSE);
	
	return TRUE;
}

void CLicenseError::OnBtnShowLicenses() 
{
	CLicenseList dlg (m_pLicManager); dlg.DoModal ();
}

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
IMPLEMENT_DYNAMIC(YWinApp, CWinApp)

BEGIN_MESSAGE_MAP(YWinApp, CWinApp)
	//{{AFX_MSG_MAP(YWinApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

YWinApp::YWinApp()
{
}

BOOL YWinApp::InitApplication() 
{
	// let's compute the application path
	m_ysAppPath = m_pszHelpFilePath;
	m_ysAppPath.ReverseTerminateAfter (_T('\\'));

	SetHelpName ();
	
	return CWinApp::InitApplication();
}

BOOL YWinApp::IsChicago () const
{
	DWORD	dwVersion = GetVersion ();

	if ( dwVersion < 0x80000000 ) {
		// NT
		return FALSE;
	}
	return LOBYTE (LOWORD (dwVersion)) >= 4;
}

void YWinApp::SetHelpName (LPCTSTR pszHelpName /* = NULL */)
{
	YPathString	ysOrgHelp = m_pszHelpFilePath;
	ysOrgHelp.StripExtension ();
	if ( pszHelpName ) {
		ysOrgHelp.SubstFileName (pszHelpName);
	}

	YPathString ysHelp;

	switch ( PRIMARYLANGID(LANGIDFROMLCID(GetUserDefaultLCID ())) ) {
	default:
	case LANG_ENGLISH:
		ysHelp = ysOrgHelp + _T("EN.chm");
		break;
	case LANG_ITALIAN:
		ysHelp = ysOrgHelp + _T("IT.chm");
		break;
	case LANG_GERMAN:
		ysHelp = ysOrgHelp + _T("DE.chm");
		break;
	}

	if ( !ysHelp.IsFile () ) {
		ysHelp = ysOrgHelp + _T("EN.chm");
		if ( !ysHelp.IsFile () ) {
			ysHelp = ysOrgHelp + _T(".chm");
			if ( !ysHelp.IsFile () ) {
				return;
			}
		}
	}

	m_ysHlpName = ysHelp;
}

void YWinApp::SetFullHelpFileName (LPCTSTR pszHelpFile)
{
	if ( pszHelpFile && *pszHelpFile ) {
		m_ysHlpName = pszHelpFile;
	}
}

void YWinApp::ShowAboutBox (LPCTSTR pszIcon, LPCTSTR pszTitle)
{
	CAboutDialog dlg;
	if ( pszIcon ) {
		dlg.m_hIcon = LoadIcon (pszIcon);
	}
	dlg.m_csTitle = (pszTitle) ? (pszTitle) : (_T(""));
	dlg.DoModal ();
}

void YWinApp::ShowLicenseList () const
{
	CLicenseList dlg (&licManager);
	dlg.DoModal ();
}

void YWinApp::ShowLicenseError (LPCTSTR pszCaption, DWORD dwError) const
{
	CLicenseError	dlg (&licManager);

	dlg.m_csCaption		= pszCaption;
	dlg.m_csLicError	= GetLicenseErrorString (dwError);
	dlg.DoModal ();
}

void YWinApp::ShowLicenseError (UINT nID, DWORD dwError) const
{
	CLicenseError	dlg (&licManager);

	dlg.m_csCaption.LoadString (nID);
	dlg.m_csLicError	= GetLicenseErrorString (dwError);
	dlg.DoModal ();
}

BOOL YWinApp::HtmlHelpContents ()
{
	return HtmlHelper (0, HH_DISPLAY_TOC, NULL);
}

BOOL YWinApp::HtmlHelpTopic (LPCTSTR pszTopic)
{
	return HtmlHelper (0, HH_DISPLAY_TOPIC, pszTopic);
}

BOOL YWinApp::HtmlHelpIndex ()
{
	return HtmlHelper (0, HH_DISPLAY_INDEX, NULL);
}

BOOL YWinApp::HtmlHelpFinder ()
{
	return HtmlHelper (0, HH_DISPLAY_SEARCH, NULL);
}

BOOL YWinApp::HtmlHelpKeyWord (LPCTSTR pszKeyWord)
{
	if ( HtmlHelper (0, HH_DISPLAY_INDEX, pszKeyWord) ) {
		return HtmlHelper (0, HH_KEYWORD_LOOKUP, pszKeyWord);
	}
	return FALSE;
}

BOOL YWinApp::HtmlHelpSearch (LPCTSTR pszSearchString)
{
	return HtmlHelper (0, HH_DISPLAY_SEARCH, pszSearchString);
}

BOOL YWinApp::HtmlHelpContext (DWORD dwContextId)
{
	return HtmlHelper (dwContextId, HH_HELP_CONTEXT, NULL);
}

BOOL YWinApp::HtmlHelpContextMenu (LPDWORD lpCtrlToContextMap, LPCTSTR pszPopupFile)
{
	return HtmlHelper ((DWORD) lpCtrlToContextMap, HH_TP_HELP_CONTEXTMENU, pszPopupFile);
}

BOOL YWinApp::HtmlHelpMessage (LPDWORD lpCtrlToContextMap, LPCTSTR pszPopupFile)
{
	return HtmlHelper ((DWORD) lpCtrlToContextMap, HH_TP_HELP_WM_HELP, pszPopupFile);
}

void YWinApp::HtmlHelpQuit ()
{
	::HtmlHelp (NULL, NULL, HH_CLOSE_ALL, 0);
}

DWORD YWinApp::GetLastLicenseError ()
{
	return licManager.GetLastError ();
}

CString YWinApp::GetLicenseErrorString (DWORD dwError)
{
	CString cs;
	switch ( dwError ) {
	case LMERR_NOERROR:
		cs.LoadString( IDS_LMERR_NOERROR );				// _T("No error");
		break;
	// generic errors
	case LMERR_FILENOTFOUND:
		cs.LoadString( IDS_LMERR_FILENOTFOUND );		// _T("File not found");
		break;
	case LMERR_NOT_ENOUGH_MEMORY:
		cs.LoadString( IDS_LMERR_NOT_ENOUGH_MEMORY );	// _T("Error allocating memory");
		break;
	case LMERR_WRITEFAULT:
		cs.LoadString( IDS_LMERR_WRITEFAULT );			//_T("Error writing file");
		break;
	case LMERR_READFAULT:
		cs.LoadString( IDS_LMERR_READFAULT );			//_T("Error reading file");
		break;
	case LMERR_CANNOT_MAKE:
		cs.LoadString( IDS_LMERR_CANNOT_MAKE );			//_T("Cannot create the file");
		break;

	// scheme errors
	case LMERR_SCHEME_INVALID:
		cs.LoadString( IDS_LMERR_SCHEME_INVALID );		//_T("Licensing scheme is not valid");
		break;
	case LMERR_SCHEME_TAMPERED:
		cs.LoadString( IDS_LMERR_SCHEME_TAMPERED );		//_T("Licensing scheme has been tampered");
		break;
	case LMERR_SCHEME_NOTLOADED:
		cs.LoadString( IDS_LMERR_SCHEME_NOTLOADED );	//_T("Error loading licensing scheme");
		break;

	// server errors
	case LMERR_SERVER_NOTINITED:
		cs.LoadString( IDS_LMERR_SERVER_NOTINITED );	//_T("Licensing system not initialized");
		break;
	case LMERR_SERVER_INITED:
		cs.LoadString( IDS_LMERR_SERVER_INITED );		//_T("Licensing system already initialized");
		break;
	case LMERR_SERVER_INVALIDADDR:
		cs.LoadString( IDS_LMERR_SERVER_INVALIDADDR );	//_T("Invalid license manager address");
		break;
	case LMERR_SERVER_UNSUPPORTEDADDR:
		cs.LoadString( IDS_LMERR_SERVER_UNSUPPORTEDADDR );//_T("Unsupported license manager address type");
		break;
	case LMERR_SERVER_CONNECTION:
		cs.LoadString( IDS_LMERR_SERVER_CONNECTION );	// _T("Connection error to license manager");
		break;
	case LMERR_SERVER_NOTFOUND:
		cs.LoadString( IDS_LMERR_SERVER_NOTFOUND );		//_T("No licensing scheme found");
		break;
	case LMERR_SERVER_MACHINEID:
		cs.LoadString( IDS_LMERR_SERVER_MACHINEID );	//_T("Cannot determine machine ID");
		break;
	case LMERR_SERVER_UNKNOWNPRODUCT:
		cs.LoadString( IDS_LMERR_SERVER_UNKNOWNPRODUCT );// _T("Unknown product requested");
		break;
	case LMERR_SERVER_UNKNOWNFEATURE:
		cs.LoadString( IDS_LMERR_SERVER_UNKNOWNFEATURE );// _T("Unknown feature requested");
		break;
	case LMERR_SERVER_LICNOTFOUND:
		cs.LoadString( IDS_LMERR_SERVER_LICNOTFOUND );	// _T("No suitable license found");
		break;
	case LMERR_SERVER_NOMORELICENSES:
		cs.LoadString( IDS_LMERR_SERVER_NOMORELICENSES );//_T("No more licenses for the requested feature");
		break;
	case LMERR_SERVER_LICEXPIRED:
		cs.LoadString( IDS_LMERR_SERVER_LICEXPIRED );	// _T("License is expired");
		break;

	// license errors
	case LMERR_LICENSE_BADMID:
		cs.LoadString( IDS_LMERR_LICENSE_BADMID );		//_T("The machine ID does not match the license key");
		break;
	case LMERR_LICENSE_BADKEY:
		cs.LoadString( IDS_LMERR_LICENSE_BADKEY );		//_T("The license key is malformed");
		break;
	case LMERR_LICENSE_INVALID:
		cs.LoadString( IDS_LMERR_LICENSE_INVALID );		//_T("The specified license is invalid");
		break;

	default:
		cs.LoadString( IDS_LMERR_UNKNOWN );				//_T("Unknown Error.");
		break;
	}
	return cs;
}

BOOL YWinApp::ConnectLicenseManager (GUID guid, LPCTSTR pszAddress)
{
	return licManager.Connect (guid, pszAddress);
}

BOOL YWinApp::DisconnectLicenseManager ()
{
	return licManager.Disconnect ();
}

BOOL YWinApp::AddLicense (LPCTSTR pszKey)
{
	return licManager.AddLicense (pszKey);
}

BOOL YWinApp::AddLicenseFile (LPCTSTR pszFileName)
{
	return licManager.AddLicenseFile (pszFileName);
}

BOOL YWinApp::AllocateLicense (WORD wCode, WORD nCount /* = 1 */)
{
	return licManager.AllocateLicense (wCode, nCount);
}

BOOL YWinApp::TestLicense (WORD nCount, ...)
{
	va_list va;
	va_start (va, nCount);
	DWORD dwRet = licManager.TestLicensesVa (nCount, va);
	licManager.SetLastError (dwRet);
	va_end (va);
	return dwRet == LMERR_NOERROR;
}

BOOL YWinApp::TestExpiration (time_t *ptExpiration, ...)
{
	va_list va;
	va_start (va, ptExpiration);
	DWORD dwRet = licManager.TestExpirationVa (ptExpiration, va);
	licManager.SetLastError (dwRet);
	va_end (va);
	return dwRet == LMERR_NOERROR;
}

BOOL YWinApp::TestLicenseEx (LPCTSTR pszCaption, WORD nCount, ...) const
{
	va_list va;
	va_start (va, nCount);
	DWORD dwRet = licManager.TestLicensesVa (nCount, va);
	va_end (va);
	if ( dwRet != LMERR_NOERROR ) {
		ShowLicenseError (pszCaption, dwRet);
		return FALSE;
	}
	return TRUE;
}

BOOL YWinApp::TestLicenseEx (UINT nIDCaption, WORD nCount, ...) const
{
	va_list va;
	va_start (va, nCount);
	DWORD dwRet = licManager.TestLicensesVa (nCount, va);
	va_end (va);
	if ( dwRet != LMERR_NOERROR ) {
		ShowLicenseError (nIDCaption, dwRet);
		return FALSE;
	}
	return TRUE;
}

BOOL YWinApp::FreeLicense (WORD wCode, WORD nCount /* = 1 */)
{
	return licManager.FreeLicense (wCode, nCount);
}

BOOL YWinApp::HtmlHelper (DWORD dwData, UINT uCommand, LPCTSTR pszParam /* = NULL */)
{
	CWnd* pMainWnd = AfxGetMainWnd();
	ASSERT_VALID(pMainWnd);

	// return global app help mode state to FALSE (backward compatibility)
	m_bHelpMode = FALSE;
	pMainWnd->PostMessage (WM_KICKIDLE); // trigger idle update

	CWaitCursor	wait;
	if ( pMainWnd->IsFrameWnd () ) {
		// CFrameWnd windows should be allowed to exit help mode first
		CFrameWnd* pFrameWnd = (CFrameWnd*) pMainWnd;
		pFrameWnd->ExitHelpMode ();
	}

	// cancel any tracking modes
	pMainWnd->SendMessage (WM_CANCELMODE);
	pMainWnd->SendMessageToDescendants (WM_CANCELMODE, 0, 0, TRUE, TRUE);

	// need to use top level parent (for the case where m_hWnd is in DLL)
	CWnd* pWnd = pMainWnd->GetTopLevelParent();
	pWnd->SendMessage (WM_CANCELMODE);
	pWnd->SendMessageToDescendants (WM_CANCELMODE, 0, 0, TRUE, TRUE);

	// attempt to cancel capture
	HWND hWndCapture = ::GetCapture ();
	if ( hWndCapture != NULL ) {
		::SendMessage (hWndCapture, WM_CANCELMODE, 0, 0);
	}

	HH_AKLINK		akParam; memset (&akParam, 0, sizeof (akParam));
	HH_FTS_QUERY	fqParam; memset (&fqParam, 0, sizeof (fqParam));
	CString			csHelp = GetFullHelpFileName ();

	akParam.cbStruct			= sizeof (akParam);
	akParam.pszWindow			= _T("Standard");
	akParam.fIndexOnFail		= TRUE ;
	fqParam.cbStruct			= sizeof (fqParam);
	fqParam.iProximity			= HH_FTS_DEFAULT_PROXIMITY;

	if ( m_ysHlpName.IsEmpty () || !m_ysHlpName.IsFile () ) {
		AfxMessageBox(AFX_IDP_FAILED_TO_LAUNCH_HELP);
		return FALSE;
	}
	switch ( uCommand ) {
	case HH_DISPLAY_TOC:
	case HH_DISPLAY_TOPIC:
		if ( pszParam ) {
			csHelp += _T("::/");
			csHelp += pszParam;
		}
		break;
	case HH_DISPLAY_INDEX:
		dwData = (pszParam) ? ((DWORD) pszParam) : ((DWORD) _T(""));
		break;
	case HH_DISPLAY_SEARCH:
		if ( pszParam ) {
			fqParam.pszSearchQuery	= pszParam;
			fqParam.fExecute		= TRUE;
		}
		else {
			fqParam.pszSearchQuery	= _T("");
		}
		dwData = (DWORD) &fqParam;
		break;
	case HH_ALINK_LOOKUP:
	case HH_KEYWORD_LOOKUP:
		akParam.pszKeywords	= pszParam;
		dwData = (DWORD) &akParam;
		break;
	case HH_HELP_CONTEXT:
	case HH_TP_HELP_CONTEXTMENU:
	case HH_TP_HELP_WM_HELP:
		break;
	}


	HWND hWnd = ::HtmlHelp (GetMainWnd ()->m_hWnd, csHelp, uCommand, dwData);
	return TRUE;
}

void YWinApp::WinHelp (DWORD dwData, UINT nCmd) 
{
	TRACE3 ("WinHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n", GetFullHelpFileName (), dwData, nCmd);

	switch ( nCmd ) {
	case HELP_COMMAND:
		TRACE(_T("WinHelp: HELP_COMMAND not supported in HtmlHelp\n"));
		break;
//	case HELP_CONTENTS:
//		TRACE(_T("WinHelp: HELP_CONTENTS\n"));
//		HtmlHelper (0, HH_DISPLAY_TOC);
//		break;
	case HELP_CONTEXT:
		TRACE1(_T("WinHelp: HELP_CONTEXT(%d)\n"), dwData);
		HtmlHelper (dwData, HH_HELP_CONTEXT, NULL);
		break;
	case HELP_CONTEXTMENU:
		TRACE(_T("WinHelp: HELP_COMMAND not yet supported in YWinApp\n"));
		break;
	case HELP_CONTEXTPOPUP:
		TRACE(_T("WinHelp: HELP_CONTEXTPOPUP not yet supported in YWinApp\n"));
		break;
	case HELP_FINDER:
		TRACE(_T("WinHelp: HELP_FINDER\n"));
		HtmlHelper (0, HH_DISPLAY_SEARCH, NULL);
		break;
	case HELP_FORCEFILE:
		TRACE(_T("WinHelp: HELP_FORCEFILE not yet supported in YWinApp\n"));
		break;
	case HELP_HELPONHELP:
		TRACE(_T("WinHelp: HELP_HELPONHELP not yet supported in YWinApp\n"));
		break;
	case HELP_INDEX:
		TRACE(_T("WinHelp: HELP_INDEX\n"));
		HtmlHelper (0, HH_DISPLAY_INDEX, NULL);
		break;
	case HELP_KEY:
		TRACE(_T("WinHelp: HELP_KEY not yet supported in YWinApp\n"));
		break;
	case HELP_MULTIKEY:
		TRACE(_T("WinHelp: HELP_MULTIKEY not yet supported in YWinApp\n"));
		break;
	case HELP_PARTIALKEY:
		TRACE(_T("WinHelp: HELP_PARTIALKEY not yet supported in YWinApp\n"));
		break;
	case HELP_QUIT:
		HtmlHelper (0, HH_CLOSE_ALL, NULL);
		break;
	case HELP_SETCONTENTS:
		TRACE(_T("WinHelp: HELP_SETCONTENTS not yet supported in YWinApp\n"));
		break;
	case HELP_SETPOPUP_POS:
		TRACE(_T("WinHelp: HELP_SETPOPUP_POS not yet supported in YWinApp\n"));
		break;
	case HELP_SETWINPOS:
		TRACE(_T("WinHelp: HELP_SETWINPOS not yet supported in YWinApp\n"));
		break;
	case HELP_TCARD:
		TRACE(_T("WinHelp: HELP_TCARD not yet supported in YWinApp\n"));
		break;
	case HELP_WM_HELP:
		TRACE(_T("WinHelp: HELP_WM_HELP not yet supported in YWinApp\n"));
		break;
	}
}

//
// EoF
////////