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
#include "ObjectDoc.h"
#include "ObjectLeftView.h"
#include "ObjectRightView.h"

#include "MainFrm.h"


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

extern	int	render_browse_type;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
    if (!m_wndSplitter.CreateStatic(this, 1, 2))
    {
        return FALSE;
    }

	if ( !m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CObjectLeftView), CSize(300, 300), pContext)  ||
		 !m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CObjectRightView), CSize(100, 100), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	
	return	true;
}

