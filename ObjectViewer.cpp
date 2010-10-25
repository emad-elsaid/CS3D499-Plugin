////////////////////////////////////////////////////////////////////////
//  Author:  Peter Bonsma
//  Date:    31 July 2010
//  Project: IFC Engine Series (example using DLL)
//
//  This code may be used and edited freely,
//  also for commercial projects in open and closed source software
//
//  In case of use of the DLL:
//  be aware of license fee for use of this DLL when used commercially
//  more info for commercial use:	peter.bonsma@tno.nl
//
//  more info for using the IFC Engine DLL in other languages
//	and creation of specific code examples:
//									pim.vandenhelm@tno.nl
//								    peter.bonsma@rdf.bg
////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "ObjectViewer.h"
#include "IFCEngine.h"

#include "MainFrm.h"
#include "ObjectDoc.h"
#include "ObjectLeftView.h"
#include "ObjectRightView.h"


extern	char	* ifcSchemaName;
extern  int     model;

/////////////////////////////////////////////////////////////////////////////
// CObjectApp

BEGIN_MESSAGE_MAP(CObjectApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectApp construction

CObjectApp::CObjectApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CObjectApp object

CObjectApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CObjectApp initialization

BOOL CObjectApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("IFC Viewer"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CObjectDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CObjectLeftView));
	AddDocTemplate(pDocTemplate);

// Register the application's document templates.  Document templates	//  serve as the connection between documents, frame windows and views.	CSingleDocTemplate* pDocTemplate;	pDocTemplate = new CSingleDocTemplate(		IDR_MAINFRAME,		RUNTIME_CLASS(CObjectDoc),		RUNTIME_CLASS(CMainFrame),       // main SDI frame window		RUNTIME_CLASS(CObjectLeftView));	AddDocTemplate(pDocTemplate);	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
		// No message handlers
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	// No message handlers
END_MESSAGE_MAP()

// App command to run the dialog
void CObjectApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CObjectApp message handlers


BOOL CObjectApp::InitApplication() 
{
	int	i = strlen(this->m_pszHelpFilePath) - strlen(this->m_pszExeName) - 4;

	ASSERT(ifcSchemaName == NULL  &&  i > 0);
	
	ifcSchemaName = new char[i+strlen("IFC2X3_TC1.exp")+1];
	memcpy(&ifcSchemaName[0], this->m_pszHelpFilePath, i);
	memcpy(&ifcSchemaName[i], "IFC2X3_TC1.exp", strlen("IFC2X3_TC1.exp")+1);
	
	return	CWinApp::InitApplication();
}


