// RunThread.cpp : implementation file
//

#include "stdafx.h"
#include "SOM_Cluster.h"
#include "RunThread.h"
#include "DotMatrix.h"

#include "Son.h"

#define PATTERN 1000

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRunThread

IMPLEMENT_DYNCREATE(CRunThread, CWinThread)

CRunThread::CRunThread()
{
}

CRunThread::~CRunThread()
{
}

BOOL CRunThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CRunThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CRunThread, CWinThread)
	//{{AFX_MSG_MAP(CRunThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRunThread message handlers
void CRunThread::SetOwner(CSOM_ClusterDlg *pDlg)
{
	m_pDlg = pDlg;
}

int CRunThread::Run()
{
	CDotMatrix* m_DotMatrix = (CDotMatrix*)m_pDlg->m_LearnDotMatrix;
	CString Str;
	long iteration;
	double initial_learning_rate, final_learning_rate;
	int initial_neigh_size;
	int neighborhood_decrement_interval;
	long num_iterations;
	int display_interval;
	int frame_rate;
	
	int input_nodes, output_nodes, x_size, y_size;

	int class_num;

	if(m_pDlg->m_Mode == FALSE)
	{
//		m_pDlg->GetDlgItemText(IDC_EDIT_INPUT_FILE, Str);
//		m_pDlg->GetDlgItemText(IDC_EDIT_NETWORK_FILE, Str);
//		m_pDlg->GetDlgItemText(IDC_EDIT_OUTPUT_FILE, Str);
		m_pDlg->GetDlgItemText(IDC_EDIT_START_LEARNING_RATE, Str);
		initial_learning_rate = atof((LPTSTR)(LPCTSTR)Str);
		m_pDlg->GetDlgItemText(IDC_EDIT_END_LEARNING_RATE, Str);
		final_learning_rate = atof((LPTSTR)(LPCTSTR)Str);




		input_nodes = m_pDlg->GetDlgItemInt(IDC_EDIT_INPUT_NODE);
		output_nodes = m_pDlg->GetDlgItemInt(IDC_EDIT_OUTPUT_NODE);
		x_size = m_pDlg->GetDlgItemInt(IDC_EDIT_LAYER_X);
		y_size = m_pDlg->GetDlgItemInt(IDC_EDIT_LAYER_Y);
		initial_neigh_size = m_pDlg->GetDlgItemInt(IDC_EDIT1_NEIGH);
		neighborhood_decrement_interval = m_pDlg->GetDlgItemInt(IDC_EDIT1_DECREMENT_ITERATION);
		num_iterations = m_pDlg->GetDlgItemInt(IDC_EDIT1_END_ITERATION);
		display_interval = m_pDlg->GetDlgItemInt(IDC_EDIT1_VIEW_INTERVAL);
		frame_rate = m_pDlg->GetDlgItemInt(IDC_EDIT1_SAVE_INTERVAL);

		m_pDlg->GetDlgItemText(IDC_EDIT_NETWORK_FILE, Str);
		SON_Network SONnet((LPTSTR)(LPCTSTR)Str);
		
		input_nodes = SONnet.Get_Input_Count();
		Pattern *input_data;

		m_pDlg->GetDlgItemText(IDC_EDIT_INPUT_FILE, Str);
		ifstream infile((LPTSTR)(LPCTSTR)Str);
		ASSERT(infile);

		while(!infile.eof() && !infile.fail())
		{
			input_data = new Pattern(input_nodes, output_nodes, infile);
			SONnet.Set_Value(input_data);
			SONnet.Run();

			cout << input_data->Get_ID() << "  ";
//			for(int i = 0; i < input_nodes; i++)
//			{
//				cout << input_data->In(i) << "  ";
//			}
			for(int i = 0; i < output_nodes; i++)
			{
				if(input_data->Out(0) == 1) 
					class_num = 1;
				else if(input_data->Out(1) == 1)
					class_num = 2;
				else 
					class_num = 3;
			}
			
//			cout << "  " << SONnet.Get_Value(COMPOSITE) << " "
//				<< SONnet.Get_Value(ROW) << " " << SONnet.Get_Value(COL) << endl;
			m_DotMatrix->UpdateCircle(SONnet.Get_Value(ROW), SONnet.Get_Value(COL), class_num);

			delete input_data;
		}

		infile.close();
	}
	else
	{
		AfxMessageBox("Train/Run Mode에 FALSE인지 확인해 주세요");
	}

	m_pDlg->GetDlgItem(IDC_BUTTON_RUN)->EnableWindow(TRUE); 
	m_pDlg->GetDlgItem(IDC_CHECK_MODE)->EnableWindow(TRUE);

	AfxEndThread(0);

	return CWinThread::Run();
}
