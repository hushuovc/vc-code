// DmsStatic.h: interface for the CDmsStatic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMSSTATIC_H__3E21F070_4E72_4E3B_99D9_1726834DFF9D__INCLUDED_)
#define AFX_DMSSTATIC_H__3E21F070_4E72_4E3B_99D9_1726834DFF9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDmsStatic  
{
public:
	static void SetLoginDBInfo(LPCTSTR lpLogin, LPCTSTR lpPassword, LPCTSTR lpDBSource);

	static void GetLoginDBInfo(CString& strLogin, CString& strPassword, CString& strDBSource);

	static void SetLanguageFlags(int nFlags);

	static void GetLanguageFlags(int& nFlags);

private:
	CDmsStatic();

	virtual ~CDmsStatic();

private:
	static CString m_strLogin;
	static CString m_strPassword;
	static CString m_strDBSource;

	static int	m_nLanguageFlags;
};

#endif // !defined(AFX_DMSSTATIC_H__3E21F070_4E72_4E3B_99D9_1726834DFF9D__INCLUDED_)
