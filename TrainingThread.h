#if !defined(AFX_TRAININGTHREAD_H__70747539_F4B1_4581_A54D_5A0AA685A459__INCLUDED_)
#define AFX_TRAININGTHREAD_H__70747539_F4B1_4581_A54D_5A0AA685A459__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrainingThread.h : header file
//

#include "SOM_ClusterDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CTrainingThread thread

class CTrainingThread : public CWinThread
{
	DECLARE_DYNCREATE(CTrainingThread)
protected:
	CTrainingThread();           // protected constructor used by dynamic creation

// Attributes
public:
	CSOM_ClusterDlg* m_pDlg;
// Operations
public:
	int Run();
	void SetOwner(CSOM_ClusterDlg* pDlg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrainingThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTrainingThread();

	// Generated message map functions
	//{{AFX_MSG(CTrainingThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAININGTHREAD_H__70747539_F4B1_4581_A54D_5A0AA685A459__INCLUDED_)
