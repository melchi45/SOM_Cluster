#if !defined(AFX_RUNTHREAD_H__4B4074FA_1599_46AA_B57D_2E7E3FA5E083__INCLUDED_)
#define AFX_RUNTHREAD_H__4B4074FA_1599_46AA_B57D_2E7E3FA5E083__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RunThread.h : header file
//

#include "SOM_ClusterDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CRunThread thread

class CRunThread : public CWinThread
{
	DECLARE_DYNCREATE(CRunThread)
protected:
	CRunThread();           // protected constructor used by dynamic creation

// Attributes
public:
	CSOM_ClusterDlg* m_pDlg;
// Operations
public:
	int Run();
	void SetOwner(CSOM_ClusterDlg* pDlg);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRunThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRunThread();

	// Generated message map functions
	//{{AFX_MSG(CRunThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUNTHREAD_H__4B4074FA_1599_46AA_B57D_2E7E3FA5E083__INCLUDED_)
