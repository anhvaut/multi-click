; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWBPDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WBP.h"

ClassCount=3
Class1=CWBPApp
Class2=CWBPDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_WBP_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_MENU_DEMO

[CLS:CWBPApp]
Type=0
HeaderFile=WBP.h
ImplementationFile=WBP.cpp
Filter=N

[CLS:CWBPDlg]
Type=0
HeaderFile=WBPDlg.h
ImplementationFile=WBPDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_DEMO_PAGESETUP

[CLS:CAboutDlg]
Type=0
HeaderFile=WBPDlg.h
ImplementationFile=WBPDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WBP_DIALOG]
Type=1
Class=CWBPDlg
ControlCount=1
Control1=IDC_EXPLORER1,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816

[MNU:IDR_MENU_DEMO]
Type=1
Class=CWBPDlg
Command1=ID_DEMO_PAGESETUP
Command2=ID_DEMO_PRINTPREVIEW
CommandCount=2

