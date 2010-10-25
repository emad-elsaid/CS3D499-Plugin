; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CObjectApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ObjectViewer.h"
LastPage=0

ClassCount=5
Class1=CObjectApp
Class2=CObjectDoc
Class3=CObjectLeftView
Class4=CMainFrame

ResourceCount=11
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource8=IDD_ABOUTBOX (English (U.S.))
Class5=CAboutDlg
Resource9=IDR_MAINFRAME (English (U.S.))
Resource10=IDD_FORMVIEW
Resource11=IDD_FORMVIEW (Dutch (Netherlands))

[CLS:CObjectApp]
Type=0
HeaderFile=ObjectViewer.h
ImplementationFile=ObjectViewer.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=ID_FILE_SAVEASIFC

[CLS:CObjectDoc]
Type=0
HeaderFile=ObjectDoc.h
ImplementationFile=ObjectDoc.cpp
Filter=N

[CLS:CObjectLeftView]
Type=0
HeaderFile=ObjectLeftView.h
ImplementationFile=ObjectLeftView.cpp
Filter=C
BaseClass=CTreeView
VirtualFilter=VWC
LastObject=CObjectLeftView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_3DVIEW_RESETFRONT




[CLS:CAboutDlg]
Type=0
HeaderFile=ObjectViewer.cpp
ImplementationFile=ObjectViewer.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308480

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVEASIFC
Command3=ID_FILE_SAVEASIFCXML
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_3DVIEW_ZOOM
Command7=ID_3DVIEW_ROTATE
Command8=ID_3DVIEW_PAN
Command9=ID_3DVIEW_RESETSIDE
Command10=ID_3DVIEW_RESETFRONT
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308480

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_3DVIEW_ZOOM
Command5=ID_3DVIEW_ROTATE
Command6=ID_3DVIEW_PAN
Command7=ID_3DVIEW_RESETSIDE
Command8=ID_3DVIEW_RESETFRONT
Command9=ID_APP_ABOUT
CommandCount=9

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_FORMVIEW]
Type=1
Class=?
ControlCount=1
Control1=IDC_RENDERWINDOW,static,1342177287

[DLG:IDD_FORMVIEW (Dutch (Netherlands))]
Type=1
Class=?
ControlCount=1
Control1=IDC_RENDERWINDOW,static,1342177287

