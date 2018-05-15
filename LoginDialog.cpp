// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ABPConvertData.h"
#include "LoginDialog.h"
#include "DmsGlobal.h"
#include "AdoInterface.h"
#include "DmsStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog


CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDialog)
	m_strDBSource = _T("");
	m_strPassword = _T("");
	m_bRembPwd = FALSE;
	m_strUserName = _T("");
	//}}AFX_DATA_INIT
}


void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDialog)
	DDX_Text(pDX, IDC_LOGIN_DB_SOURCE, m_strDBSource);
	DDX_Text(pDX, IDC_LOGIN_PASSWORD, m_strPassword);
	DDX_Check(pDX, IDC_LOGIN_REMEMBER_PASSWORD, m_bRembPwd);
	DDX_Text(pDX, IDC_LOGIN_USER, m_strUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	//{{AFX_MSG_MAP(CLoginDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog message handlers

void CLoginDialog::OnOK() 
{
	UpdateData(TRUE);

	CString strDBSource = m_strDBSource;
	strDBSource.TrimLeft();
	strDBSource.TrimRight();
	if (strDBSource.IsEmpty())
	{
		CString str;
		str = LoadStringDms("IDS_LOGIN_ERROR1");
		MessageBox(str, "Tips", MB_OK|MB_ICONWARNING);
		GetDlgItem(IDC_LOGIN_DB_SOURCE)->SetFocus();
		return ;
	}
	
	CString strDBUserName = m_strUserName;
	strDBUserName.TrimLeft();
	strDBUserName.TrimRight();
	if (strDBUserName.IsEmpty())
	{
		CString str;
		str = LoadStringDms("IDS_LOGIN_ERROR2");
		MessageBox(str, "Tips", MB_OK|MB_ICONWARNING);
		GetDlgItem(IDC_LOGIN_USER)->SetFocus();
		return ;
	}
	
	CString strPassword = m_strPassword;
	strPassword.TrimLeft();
	strPassword.TrimRight();
	if (strPassword.IsEmpty())
	{
		CString str;
		str = LoadStringDms("IDS_LOGIN_ERROR3");
		MessageBox(str, "Tips", MB_OK|MB_ICONWARNING);
		GetDlgItem(IDC_LOGIN_PASSWORD)->SetFocus();
		return ;
	}

	CString strCmd = _T("");
	CString strLog = _T("");
	CAdoInterface AdoApp;
	HRESULT hRes = CoInitialize(NULL); 
	strCmd.Format(_T("Provider=SQLOLEDB.1;Persist Security Info=False;User ID=%s;Initial Catalog=master;Data Source=%s"), strDBUserName, strDBSource);
	if(!AdoApp.ConnecDataLibrary(strCmd, strDBUserName, strPassword))
	{
		CString str;
		str = LoadStringDms("IDS_LOGIN_ERROR4");
		WriteLog(str);
		MessageBox(str, "Tips", MB_OK|MB_ICONWARNING);
		return ;
	}
	
	try
	{
		strCmd = _T("use CardioScanServer");
		if (AdoApp.Execute(strCmd, FALSE) == RT_ERROR)
		{
			strLog.Format(_T("%s: %s"), LoadStringDms("IDS_FAILED_CONNECT_DB"), strCmd);
			WriteLog(strLog);
			MessageBox(strLog, "Tips", MB_OK|MB_ICONWARNING);
			return ;
		}
		
		AdoApp.CloseDataLibrary();
	}
	catch(_com_error e)
	{
		AdoApp.CloseDataLibrary();
		strLog.Format("Database operation fails\nError Number:%x\nError Messages:%s\nError original:%s\nError Description:%s",e.Error(),e.ErrorMessage(),(LPCSTR)e.Source(),(LPCSTR)e.Description());
		WriteLog(strLog);
		MessageBox(strLog, "Tips", MB_OK|MB_ICONWARNING);
		return ;
	}

	CDmsStatic::SetLoginDBInfo(strDBUserName, strPassword, strDBSource);
	WriteLoginInfoToIni(strDBSource, strDBUserName, strPassword, m_bRembPwd);
	
	CDialog::OnOK();
}

void CLoginDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CLoginDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strName;
	HICON hIcon = LoadIconBySize(IDI_ICON_USER, 16, 16);
	SetIcon(hIcon, FALSE);
	SetIcon(hIcon, TRUE);

	GetLoginInfoFromIni(m_strDBSource, m_strUserName, m_strPassword, m_bRembPwd);

	m_OKBtn.SubclassDlgItem(IDOK, this);
	hIcon = LoadIconBySize(IDI_ICON_GO_TO, 32, 32);
	HICON hIcon2 = LoadIconBySize(IDI_ICON_GO_TO2, 32, 32);
	m_OKBtn.SetIcon(hIcon2, hIcon);
	m_OKBtn.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
	m_OKBtn.DrawTransparent(TRUE);
	m_OKBtn.SetFlat(FALSE);

	strName = LoadStringDms("IDS_IDOK_LOGIN");
	m_OKBtn.SetWindowText(strName);

	SetDlgText(this, "IDD_LOGIN_DIALOG");

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
