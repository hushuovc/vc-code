// DmsStatic.cpp: implementation of the CDmsStatic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ABPConvertData.h"
#include "DmsStatic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CString CDmsStatic::m_strLogin = _T("");
CString CDmsStatic::m_strPassword = _T("");
CString CDmsStatic::m_strDBSource = _T("");
int	CDmsStatic::m_nLanguageFlags = 0;


CDmsStatic::CDmsStatic()
{

}

CDmsStatic::~CDmsStatic()
{

}

void CDmsStatic::SetLoginDBInfo(LPCTSTR lpLogin, LPCTSTR lpPassword, LPCTSTR lpDBSource)
{
	if (lpLogin != NULL)
	{
		m_strLogin.Format(_T("%s"), lpLogin);
		m_strLogin.TrimLeft();
		m_strLogin.TrimRight();
	}

	if (lpPassword != NULL)
	{
		m_strPassword.Format(_T("%s"), lpPassword);
		m_strPassword.TrimLeft();
		m_strPassword.TrimRight();
	}

	if (lpDBSource != NULL)
	{
		m_strDBSource.Format(_T("%s"), lpDBSource);
		m_strDBSource.TrimLeft();
		m_strDBSource.TrimRight();
	}
}

void CDmsStatic::GetLoginDBInfo(CString& strLogin, CString& strPassword, CString& strDBSource)
{
	strLogin = m_strLogin;
	strPassword = m_strPassword;
	strDBSource = m_strDBSource;
}

void CDmsStatic::SetLanguageFlags(int nFlags)
{
	m_nLanguageFlags = nFlags;
}

void CDmsStatic::GetLanguageFlags(int& nFlags)
{
	nFlags = m_nLanguageFlags;
}