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


#if !defined(AFX_OBJECTVIEWER_H__9921C27E_1900_4886_91EC_416649DC6568__INCLUDED_)
#define AFX_OBJECTVIEWER_H__9921C27E_1900_4886_91EC_416649DC6568__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __AFXWIN_H__

#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CObjectApp:
// See ObjectViewer.cpp for the implementation of this class
//

class CObjectApp : public CWinApp
{
public:
	CObjectApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	virtual BOOL InitApplication();

// Implementation
	DECLARE_MESSAGE_MAP()
};

#endif
