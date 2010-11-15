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


#if !defined(AFX_OBJECTLEFTVIEW_H__E26B6933_A349_44D9_95E9_7F4D1A7F9B03__INCLUDED_)
#define AFX_OBJECTLEFTVIEW_H__E26B6933_A349_44D9_95E9_7F4D1A7F9B03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif


class CObjectLeftView : public CTreeView
{
protected: // create from serialization only
	CObjectLeftView();
	DECLARE_DYNCREATE(CObjectLeftView)

// Attributes
public:
	CObjectDoc* GetDocument();

// Operations
public:

// Overrides
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();

// Implementation
public:
	virtual ~CObjectLeftView();

protected:

// Generated message map functions
protected:
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

inline CObjectDoc* CObjectLeftView::GetDocument()
{ 
	return (CObjectDoc*)m_pDocument;
}

#endif
