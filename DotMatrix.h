#if !defined(AFX_DOTMATRIX_H__D0E4ECF9_9645_4341_B388_26D31FAC4D5D__INCLUDED_)
#define AFX_DOTMATRIX_H__D0E4ECF9_9645_4341_B388_26D31FAC4D5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DotMatrix.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDotMatrix window

class CDotMatrix : public CWnd
{
// Construction
public:
	CDotMatrix();
	int m_xLayer;
	int m_yLayer;
	COLORREF   m_colorpen;
	CPen	pen, *oldpen;
	CBrush	brush, *oldbrush;
	CRect rect;
//	int set_x, set_y;
	CDC ScreenDC;
	CBitmap m_pBitmap;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDotMatrix)
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateCircle(int x, int y, int class_number);
	void SetClassNumber(int class_number);
	void SetLayer(int x_layer, int y_layer);
	virtual ~CDotMatrix();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDotMatrix)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOTMATRIX_H__D0E4ECF9_9645_4341_B388_26D31FAC4D5D__INCLUDED_)
