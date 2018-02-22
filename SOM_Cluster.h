// SOM_Cluster.h : main header file for the SOM_CLUSTER application
//

#if !defined(AFX_SOM_CLUSTER_H__1D85A6AC_BBE8_4138_B965_5842CAA0B4CF__INCLUDED_)
#define AFX_SOM_CLUSTER_H__1D85A6AC_BBE8_4138_B965_5842CAA0B4CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSOM_ClusterApp:
// See SOM_Cluster.cpp for the implementation of this class
//

class CSOM_ClusterApp : public CWinApp
{
public:
	CSOM_ClusterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSOM_ClusterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSOM_ClusterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOM_CLUSTER_H__1D85A6AC_BBE8_4138_B965_5842CAA0B4CF__INCLUDED_)
