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


#if !defined(AFX_OBJECTRIGHTVIEW_H__7CB4DD8B_5770_4AD1_A4DC_D7D508A4EF49__INCLUDED_)
#define AFX_OBJECTRIGHTVIEW_H__7CB4DD8B_5770_4AD1_A4DC_D7D508A4EF49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "d3d8.h"
#include "d3dx8.h"

#include "stdafx.h"
#include "ObjectViewer.h"

#define		D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL)

typedef struct CUSTOMVERTEX {
	float	x;
	float	y;
	float	z;
	float	nx;
	float	ny;
	float	nz;
}	customvertex;



/////////////////////////////////////////////////////////////////////////////
// CObjectRightView window

class CObjectRightView : public CFormView
{
// Construction
public:
	CObjectRightView();

// Attributes
public:

// Operations
public:
    HWND m_hwndRenderWindow;

// Overrides
	enum { IDD = IDD_FORMVIEW };

	virtual void OnInitialUpdate();

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG *pMSG);

// Implementation
public:

	// Generated message map functions
protected:
	virtual ~CObjectRightView();
	DECLARE_DYNCREATE(CObjectRightView)

	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

	LPDIRECT3D8             g_pD3D;			// Used to create the D3DDevice
	LPDIRECT3DDEVICE8       g_pd3dDevice;	// Our rendering device
	LPDIRECT3DVERTEXBUFFER8 g_pVB;			// Buffer to hold vertices

    D3DPRESENT_PARAMETERS	d3dpp;

	int		m_iWidth;
	int		m_iHeight;

	void	InitializeDevice();
	void	InitializeDeviceBuffer();
	void	Render();
	int		SetupLights();
	int		SetupMatrices();

private:
	const FLOAT MULTIPLY_RATIO ;
	
};


#endif 