// TrainingThread.cpp : implementation file
//

#include "stdafx.h"
#include "SOM_Cluster.h"
#include "TrainingThread.h"
#include "DotMatrix.h"

#include "Son.h"

#define PATTERN 1000

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrainingThread

IMPLEMENT_DYNCREATE(CTrainingThread, CWinThread)

CTrainingThread::CTrainingThread()
{
}

CTrainingThread::~CTrainingThread()
{
}

BOOL CTrainingThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CTrainingThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CTrainingThread, CWinThread)
	//{{AFX_MSG_MAP(CTrainingThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrainingThread message handlers

void CTrainingThread::SetOwner(CSOM_ClusterDlg *pDlg)
{
	m_pDlg = pDlg;
}

int CTrainingThread::Run()
{
	CDotMatrix* m_LearnDotMatrix = (CDotMatrix*)m_pDlg->m_LearnDotMatrix;
	CDotMatrix* m_RunDotMatrix = (CDotMatrix*)m_pDlg->m_RunDotMatrix;

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
	int mode;

	enum {RUN, LEARN};

	CButton* pLearnCheck = (CButton*)m_pDlg->GetDlgItem(IDC_RADIO_TRAINING);
	CButton* pRunCheck = (CButton*)m_pDlg->GetDlgItem(IDC_RADIO_RUN);

	if(pLearnCheck->GetCheck() && !pRunCheck->GetCheck())
	{
		mode = LEARN;
	}
	else if(pRunCheck->GetCheck() && !pLearnCheck->GetCheck())
	{
		mode = RUN;
	}
	else 
	{
		AfxMessageBox("모드를 확인하세요");
		return 0;
	}

	if(mode == LEARN)
	{
		m_pDlg->GetDlgItemText(IDC_EDIT_START_LEARNING_RATE, Str);
		initial_learning_rate = atof((LPTSTR)(LPCTSTR)Str);
		m_pDlg->GetDlgItemText(IDC_EDIT_END_LEARNING_RATE, Str);
		final_learning_rate = atof((LPTSTR)(LPCTSTR)Str);

		x_size = m_pDlg->GetDlgItemInt(IDC_EDIT_LAYER_X);
		y_size = m_pDlg->GetDlgItemInt(IDC_EDIT_LAYER_Y);

		m_LearnDotMatrix->SetLayer(x_size, y_size);
		m_LearnDotMatrix->Invalidate();

		input_nodes = m_pDlg->GetDlgItemInt(IDC_EDIT_INPUT_NODE);
		output_nodes = m_pDlg->GetDlgItemInt(IDC_EDIT_OUTPUT_NODE);
		
		initial_neigh_size = m_pDlg->GetDlgItemInt(IDC_EDIT1_NEIGH);
		neighborhood_decrement_interval = m_pDlg->GetDlgItemInt(IDC_EDIT1_DECREMENT_ITERATION);
		num_iterations = m_pDlg->GetDlgItemInt(IDC_EDIT1_END_ITERATION);
		display_interval = m_pDlg->GetDlgItemInt(IDC_EDIT1_VIEW_INTERVAL);
		frame_rate = m_pDlg->GetDlgItemInt(IDC_EDIT1_SAVE_INTERVAL);

		Pattern * data[PATTERN];
		int pattern_count = 0;

		m_pDlg->GetDlgItemText(IDC_EDIT_INPUT_FILE, Str);
		ifstream infile((LPTSTR)(LPCTSTR)Str);

		while(!infile.eof() && !infile.fail())
		{
			data[pattern_count] = new Pattern(input_nodes, output_nodes, infile);
//			data[pattern_count]->Print();
			pattern_count++;
		}

		infile.close();

		SON_Network a(input_nodes, x_size, y_size, initial_learning_rate, final_learning_rate,
			initial_neigh_size, neighborhood_decrement_interval, num_iterations);
		
		m_pDlg->GetDlgItemText(IDC_EDIT_OUTPUT_FILE, Str);

		ofstream ofile;
		if(frame_rate != 0)
		{
			ofile.open((LPTSTR)(LPCTSTR)Str);
			a.Print(ofile);
		}

		for(iteration = 0; iteration < num_iterations; iteration++)
		{
			for(int i = 0; i < pattern_count; i++)
			{
				a.Set_Value(data[i]);
				a.Run();
				a.Learn();
				if(display_interval != 0 && iteration % display_interval == 0)
				{
					for( int j = 0; j < output_nodes; j++)
					{
						 if(data[i]->Out(0) == 1) 
							class_num = 1;
						 else if(data[i]->Out(1) == 1)
							class_num = 2;
						 else if(data[i]->Out(2) == 1)
							class_num = 3;
					}

//					cout << " " << setw(4) << a.Get_Value(COMPOSITE) << " "
//						 << a.Get_Value(ROW) << " " << a.Get_Value(COL) << endl;
					m_LearnDotMatrix->UpdateCircle((int)a.Get_Value(ROW), (int)a.Get_Value(COL), class_num);
				}
			}

			a.Epoch();

//			if(display_interval != 0 && iteration % display_interval == 0)
			{
				m_pDlg->SetDlgItemInt(IDC_EDIT_NOW_ITERATION, iteration, TRUE);
				Str.Format("%f", a.Get_Learning_Rate());
				m_pDlg->SetDlgItemText(IDC_EDIT_NOW_LEARNING_RATE, Str);
				m_pDlg->SetDlgItemInt(IDC_EDIT_NEIGHBORHOOD, a.Get_Neighborhood_Size(), TRUE);
			}

			if(frame_rate != 0 && iteration % frame_rate == 0)
			{
				a.Print(ofile);
			}
		}

		if(frame_rate != 0)
		{
			ofile.close();
		}

		m_pDlg->GetDlgItemText(IDC_EDIT_NETWORK_FILE, Str);

		ofstream outfile((LPTSTR)(LPCTSTR)Str);
		a.Save(outfile);
		outfile.close();
	}
	else if(mode == RUN)
	{
		input_nodes = m_pDlg->GetDlgItemInt(IDC_EDIT_INPUT_NODE);
		output_nodes = m_pDlg->GetDlgItemInt(IDC_EDIT_OUTPUT_NODE);
		
		m_pDlg->GetDlgItemText(IDC_EDIT_NETWORK_FILE, Str);
		SON_Network SONnet((LPTSTR)(LPCTSTR)Str);

		m_RunDotMatrix->SetLayer(SONnet.x_size, SONnet.y_size);
		m_RunDotMatrix->Invalidate();

		input_nodes = SONnet.Get_Input_Count();
		Pattern *input_data;

		m_pDlg->GetDlgItemText(IDC_EDIT_INPUT_FILE, Str);
		ifstream infile((LPTSTR)(LPCTSTR)Str);

		while(!infile.eof() && !infile.fail())
		{
			input_data = new Pattern(input_nodes, output_nodes, infile);
			SONnet.Set_Value(input_data);
			SONnet.Run();

			for(int i = 0; i < output_nodes; i++)
			{
				if(input_data->Out(0) == 1) 
					class_num = 1;
				else if(input_data->Out(1) == 1)
					class_num = 2;
				else if(input_data->Out(2) == 1)
					class_num = 3;
			}
			
			m_RunDotMatrix->UpdateCircle((int)SONnet.Get_Value(ROW), (int)SONnet.Get_Value(COL), class_num);

			delete input_data;
		}

		infile.close();
	}

	AfxEndThread(0);

	m_pDlg->GetDlgItem(IDC_BUTTON_RUN)->EnableWindow(TRUE); 
	m_pDlg->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE); 

	return CWinThread::Run();
}
