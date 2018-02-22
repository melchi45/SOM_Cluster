// DotMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "SOM_Cluster.h"
#include "DotMatrix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDotMatrix

CDotMatrix::CDotMatrix()
{
	m_xLayer = 8;
	m_yLayer = 8;

	m_colorpen = RGB(0,0,255);
}

CDotMatrix::~CDotMatrix()
{
}


BEGIN_MESSAGE_MAP(CDotMatrix, CWnd)
	//{{AFX_MSG_MAP(CDotMatrix)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDotMatrix message handlers

void CDotMatrix::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CBrush BkBrush;

	GetClientRect(&rect);

	m_colorpen = RGB(255,255,255);
	brush.CreateSolidBrush(m_colorpen);
	dc.SelectObject(&brush);
	
	dc.FillRect(rect, &brush);

	brush.DeleteObject();
	
	int init_x = (int)rect.Height() / m_xLayer;
	int init_y = (int)rect.Width() / m_yLayer;

	for(int i = 0; i < m_xLayer ; i++)
	{
		for(int j = 0 ; j < m_yLayer ; j++)
		{
				//Initialize Draw Circle

				m_colorpen = RGB(0,0,0);

				pen.CreatePen(PS_SOLID , 1 , m_colorpen);
				brush.CreateSolidBrush(m_colorpen);

				dc.SelectObject(&pen);
				dc.SelectObject(&brush);

				dc.Ellipse(i * init_x , j * init_x , init_x + i * init_x , init_y + j * init_x);

				pen.DeleteObject();
				brush.DeleteObject();
		}
	}

}

void CDotMatrix::SetLayer(int x_layer, int y_layer)
{
	m_xLayer = x_layer;
	m_yLayer = y_layer;
}

void CDotMatrix::SetClassNumber(int class_number)
{
	if(class_number == 1)
	{
		m_colorpen = RGB(255,0,0);
	}
	else if(class_number == 2)
	{
		m_colorpen = RGB(0,255,0);
	}
	else if(class_number == 3)
	{
		m_colorpen = RGB(0,0,255);
	}
	else if(class_number == 0)
	{
		m_colorpen = RGB(0,0,0);
	}
}

void CDotMatrix::UpdateCircle(int x, int y, int class_number)
{
//	InvalidateRect(NULL);
	CClientDC memDC(this); // device context for painting

	GetClientRect(&rect);

	int init_x = (int)rect.Height() / m_xLayer;
	int init_y = (int)rect.Width() / m_yLayer;

	SetClassNumber(class_number);

	brush.CreateSolidBrush(m_colorpen);
	oldbrush = memDC.SelectObject(&brush);

	pen.CreatePen(PS_SOLID , 2 , m_colorpen);
	oldpen = memDC.SelectObject(&pen);
	

	memDC.Ellipse(x * init_x , y * init_x , init_x + x * init_x , init_y + y * init_x);

	memDC.SelectObject(&oldbrush);
	memDC.SelectObject(&oldpen);

	pen.DeleteObject();
	brush.DeleteObject();

//	Invalidate();
}


