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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_3DVIEW_RESETSIDE, On3dviewResetside)
	ON_COMMAND(ID_3DVIEW_RESETTOP, On3dviewResettop)
	ON_COMMAND(ID_3DVIEW_RESETFRONT, On3dviewResetfront)
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
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

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

void CMainFrame::On3dviewResetside() 
{
	CWnd * wnd = this;
	wnd = wnd->GetWindow(GW_CHILD);
	wnd = wnd->GetWindow(GW_CHILD);
	wnd = wnd->GetNextWindow();
	wnd->SendMessage(ID_RESET_SIDE, 0, 0);
}

void CMainFrame::On3dviewResettop() 
{
	CWnd * wnd = this;
	wnd = wnd->GetWindow(GW_CHILD);
	wnd = wnd->GetWindow(GW_CHILD);
	wnd = wnd->GetNextWindow();
	wnd->SendMessage(ID_RESET_TOP, 0, 0);
}

void CMainFrame::On3dviewResetfront() 
{
	CWnd * wnd = this;
	wnd = wnd->GetWindow(GW_CHILD);
	wnd = wnd->GetWindow(GW_CHILD);
	wnd = wnd->GetNextWindow();
	wnd->SendMessage(ID_RESET_FRONT, 0, 0);
}
