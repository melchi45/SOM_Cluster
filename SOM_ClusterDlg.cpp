// SOM_ClusterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SOM_Cluster.h"
#include "SOM_ClusterDlg.h"
#include "TrainingThread.h"
#include "RunThread.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSOM_ClusterDlg dialog

CSOM_ClusterDlg::CSOM_ClusterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSOM_ClusterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSOM_ClusterDlg)
	m_EndLearning = _T("0.01");
	m_InputFile = _T("cross.dat");
	m_LayerX = _T("30");
	m_LayerY = _T("30");
	m_NetworkFile = _T("cross.net");
	m_OutputFile = _T("cross.out");
	m_OutputNodeNumber = _T("2");
	m_InputNodeNumber = _T("2");
	m_StartLearningRate = _T("0.5");
	m_DecrementInterval = _T("1000");
	m_EndIteration = _T("5000");
	m_NeighborhoodNumber = _T("5");
	m_SaveInterval = _T("500");
	m_ViewInterval = _T("10");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_LearnDotMatrix = new CDotMatrix;
	m_RunDotMatrix = new CDotMatrix;
}

void CSOM_ClusterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSOM_ClusterDlg)
	DDX_Control(pDX, IDC_RADIO_TRAINING, m_RadioTraining);
	DDX_Control(pDX, IDC_RADIO_RUN, m_RadioRun);
	DDX_Control(pDX, IDC_CHECK_PAUSE, m_PauseCheck);
	DDX_Text(pDX, IDC_EDIT_END_LEARNING_RATE, m_EndLearning);
	DDX_Text(pDX, IDC_EDIT_INPUT_FILE, m_InputFile);
	DDX_Text(pDX, IDC_EDIT_LAYER_X, m_LayerX);
	DDX_Text(pDX, IDC_EDIT_LAYER_Y, m_LayerY);
	DDX_Text(pDX, IDC_EDIT_NETWORK_FILE, m_NetworkFile);
	DDX_Text(pDX, IDC_EDIT_OUTPUT_FILE, m_OutputFile);
	DDX_Text(pDX, IDC_EDIT_OUTPUT_NODE, m_OutputNodeNumber);
	DDX_Text(pDX, IDC_EDIT_INPUT_NODE, m_InputNodeNumber);
	DDX_Text(pDX, IDC_EDIT_START_LEARNING_RATE, m_StartLearningRate);
	DDX_Text(pDX, IDC_EDIT1_DECREMENT_ITERATION, m_DecrementInterval);
	DDX_Text(pDX, IDC_EDIT1_END_ITERATION, m_EndIteration);
	DDX_Text(pDX, IDC_EDIT1_NEIGH, m_NeighborhoodNumber);
	DDX_Text(pDX, IDC_EDIT1_SAVE_INTERVAL, m_SaveInterval);
	DDX_Text(pDX, IDC_EDIT1_VIEW_INTERVAL, m_ViewInterval);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSOM_ClusterDlg, CDialog)
	//{{AFX_MSG_MAP(CSOM_ClusterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	ON_BN_CLICKED(IDC_CHECK_PAUSE, OnCheckPause)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_RADIO_RUN, OnRadioRun)
	ON_BN_CLICKED(IDC_RADIO_TRAINING, OnRadioTraining)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSOM_ClusterDlg message handlers

BOOL CSOM_ClusterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// create the control
		
	// TODO: Add extra initialization here
	m_LearnDotMatrix->SubclassDlgItem(IDC_STATIC_TRAINING, this);
	m_LearnDotMatrix->SetLayer(atoi((LPTSTR)(LPCTSTR)m_LayerX), atoi((LPTSTR)(LPCTSTR)m_LayerY));

	m_RunDotMatrix->SubclassDlgItem(IDC_STATIC_RUN, this);
	m_RunDotMatrix->SetLayer(atoi((LPTSTR)(LPCTSTR)m_LayerX), atoi((LPTSTR)(LPCTSTR)m_LayerY));

	m_RadioTraining.SetCheck(BST_CHECKED);
	m_RadioRun.SetCheck(BST_UNCHECKED);

	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSOM_ClusterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSOM_ClusterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSOM_ClusterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSOM_ClusterDlg::OnOK() 
{
	CDialog::OnOK();
}

void CSOM_ClusterDlg::OnButtonRun() 
{
	// Button이 눌렸을때 Thread를 생성시킨다.
	m_pTrainingThread	= (CTrainingThread*)AfxBeginThread(RUNTIME_CLASS(CTrainingThread),
		THREAD_PRIORITY_LOWEST, 0, CREATE_SUSPENDED);
	m_pTrainingThread->SetOwner(this); // Dlg에 대한 포인터를 넘긴다.
	m_pTrainingThread->ResumeThread(); // Thread를 시작 시킨다.
		// Thread를 동작하는 동안 다른 Thread를 동작 시키지 못하게 한다.

	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_RUN)->EnableWindow(FALSE);
}

void CSOM_ClusterDlg::OnCheckPause() 
{
	if(m_PauseCheck.GetCheck())
	{
		if(m_pTrainingThread != NULL)
			m_pTrainingThread->SuspendThread();
	}
	else
	{
		if(m_pTrainingThread != NULL)
			m_pTrainingThread->ResumeThread();
	}	
}

void CSOM_ClusterDlg::OnButtonStop() 
{
	if(m_pTrainingThread != NULL)
	{
		m_pTrainingThread->SuspendThread();
	}

	GetDlgItem(IDC_BUTTON_RUN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
}

void CSOM_ClusterDlg::OnRadioRun() 
{
	m_RadioTraining.SetCheck(BST_UNCHECKED);
	m_RadioRun.SetCheck(BST_CHECKED);
}

void CSOM_ClusterDlg::OnRadioTraining() 
{
	m_RadioTraining.SetCheck(BST_CHECKED);
	m_RadioRun.SetCheck(BST_UNCHECKED);
}
