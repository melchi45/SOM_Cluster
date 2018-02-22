// SOM_ClusterDlg.h : header file
//

#if !defined(AFX_SOM_CLUSTERDLG_H__8AD4E582_EE28_4842_9A27_147809DF5043__INCLUDED_)
#define AFX_SOM_CLUSTERDLG_H__8AD4E582_EE28_4842_9A27_147809DF5043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSOM_ClusterDlg dialog

#include "DotMatrix.h"

class CTrainingThread;
class CRunThread;

class CSOM_ClusterDlg : public CDialog
{
// Construction
public:
	CSOM_ClusterDlg(CWnd* pParent = NULL);	// standard constructor
	CDotMatrix* m_LearnDotMatrix;
	CDotMatrix* m_RunDotMatrix;
	CTrainingThread* m_pTrainingThread;
	CRunThread* m_pRunThread;
	BOOL m_Mode;
// Dialog Data
	//{{AFX_DATA(CSOM_ClusterDlg)
	enum { IDD = IDD_SOM_CLUSTER_DIALOG };
	CButton	m_RadioTraining;
	CButton	m_RadioRun;
	CButton	m_PauseCheck;
	CString	m_EndLearning;
	CString	m_InputFile;
	CString	m_LayerX;
	CString	m_LayerY;
	CString	m_NetworkFile;
	CString	m_OutputFile;
	CString	m_OutputNodeNumber;
	CString	m_InputNodeNumber;
	CString	m_StartLearningRate;
	CString	m_DecrementInterval;
	CString	m_EndIteration;
	CString	m_NeighborhoodNumber;
	CString	m_SaveInterval;
	CString	m_ViewInterval;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSOM_ClusterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSOM_ClusterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButtonRun();
	afx_msg void OnCheckPause();
	afx_msg void OnButtonStop();
	afx_msg void OnRadioRun();
	afx_msg void OnRadioTraining();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOM_CLUSTERDLG_H__8AD4E582_EE28_4842_9A27_147809DF5043__INCLUDED_)
