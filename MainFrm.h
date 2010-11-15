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


#if !defined(AFX_MAINFRM_H__01281587_78F2_4030_BFAE_6D42EC611F40__INCLUDED_)
#define AFX_MAINFRM_H__01281587_78F2_4030_BFAE_6D42EC611F40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	CSplitterWnd m_wndSplitter;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
// Implementation
public:
	virtual ~CMainFrame();

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void On3dviewResetside();
	afx_msg void On3dviewResettop();
	afx_msg void On3dviewResetfront();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
