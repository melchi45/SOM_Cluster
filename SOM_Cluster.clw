; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDotMatrix
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SOM_Cluster.h"

ClassCount=6
Class1=CSOM_ClusterApp
Class2=CSOM_ClusterDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CDotMatrix
Class5=CTrainingThread
Resource3=IDD_SOM_CLUSTER_DIALOG
Resource4=IDD_ABOUTBOX (Korean)
Class6=CRunThread
Resource5=IDD_SOM_CLUSTER_DIALOG (Korean)

[CLS:CSOM_ClusterApp]
Type=0
HeaderFile=SOM_Cluster.h
ImplementationFile=SOM_Cluster.cpp
Filter=N

[CLS:CSOM_ClusterDlg]
Type=0
HeaderFile=SOM_ClusterDlg.h
ImplementationFile=SOM_ClusterDlg.cpp
Filter=D
LastObject=CSOM_ClusterDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SOM_ClusterDlg.h
ImplementationFile=SOM_ClusterDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SOM_CLUSTER_DIALOG]
Type=1
Class=CSOM_ClusterDlg
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_TRAINING,static,1342177287
Control4=IDC_BUTTON_TRAINING,button,1342242816
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_EDIT3,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT4,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT5,edit,1350631552
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287
Control17=IDC_EDIT6,edit,1350631552
Control18=IDC_STATIC,static,1342308352

[CLS:CDotMatrix]
Type=0
HeaderFile=DotMatrix.h
ImplementationFile=DotMatrix.cpp
BaseClass=CWnd
Filter=W
LastObject=CDotMatrix
VirtualFilter=WC

[CLS:CTrainingThread]
Type=0
HeaderFile=TrainingThread.h
ImplementationFile=TrainingThread.cpp
BaseClass=CWinThread
Filter=N
LastObject=CTrainingThread

[DLG:IDD_ABOUTBOX (Korean)]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SOM_CLUSTER_DIALOG (Korean)]
Type=1
Class=CSOM_ClusterDlg
ControlCount=46
Control1=IDC_EDIT_INPUT_FILE,edit,1350631552
Control2=IDC_EDIT_NETWORK_FILE,edit,1350631552
Control3=IDC_EDIT_OUTPUT_FILE,edit,1350631552
Control4=IDC_EDIT_INPUT_NODE,edit,1350631552
Control5=IDC_EDIT_OUTPUT_NODE,edit,1350631552
Control6=IDC_EDIT_LAYER_X,edit,1350631552
Control7=IDC_EDIT_LAYER_Y,edit,1350631552
Control8=IDC_EDIT_START_LEARNING_RATE,edit,1350631552
Control9=IDC_EDIT_END_LEARNING_RATE,edit,1350631552
Control10=IDC_EDIT1_NEIGH,edit,1350631552
Control11=IDC_EDIT1_DECREMENT_ITERATION,edit,1350631552
Control12=IDC_EDIT1_END_ITERATION,edit,1350631552
Control13=IDC_EDIT1_VIEW_INTERVAL,edit,1350631552
Control14=IDC_EDIT1_SAVE_INTERVAL,edit,1350631552
Control15=IDC_EDIT_NOW_ITERATION,edit,1350631552
Control16=IDOK,button,1342242816
Control17=IDCANCEL,button,1342242816
Control18=IDC_STATIC_TRAINING,static,1342177287
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC_RUN,static,1342177287
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_BUTTON_RUN,button,1342242816
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342181380
Control38=IDC_EDIT_NOW_LEARNING_RATE,edit,1350631552
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_EDIT_NEIGHBORHOOD,edit,1350631552
Control42=IDC_CHECK_PAUSE,button,1342242819
Control43=IDC_BUTTON_STOP,button,1342242816
Control44=IDC_RADIO_TRAINING,button,1342308361
Control45=IDC_RADIO_RUN,button,1342308361
Control46=IDC_STATIC,button,1342308359

[CLS:CRunThread]
Type=0
HeaderFile=RunThread.h
ImplementationFile=RunThread.cpp
BaseClass=CWinThread
Filter=N

