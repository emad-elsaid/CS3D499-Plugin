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
#include "IFCEngineInteract.h"
#include "cam.h"

#include "ObjectRightView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	STRUCT_INSTANCES	* first_instance;
extern	int		noVertices, noIndices, * pIndices;
extern	float	* pVertices;

float	* pVerticesDeviceBuffer, counter = 0;
bool	initialized = false;
int		DirectXStatus = 0;
const float kCamMoveAmt = 0.002f; // Amount to move camera by
const float kMaxAngle = 89.0f;
D3DXVECTOR3		m_vecOrigin;

/////////////////////////////////////////////////////////////////////////////
// CObjectRightView

IMPLEMENT_DYNCREATE(CObjectRightView, CFormView)

BEGIN_MESSAGE_MAP(CObjectRightView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()

CObjectRightView::CObjectRightView()
	: CFormView(CObjectRightView::IDD)
{
}

CObjectRightView::~CObjectRightView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CObjectRightView message handlers

void CObjectRightView::OnSize(UINT nType, int cx, int cy) 
{
	SetScrollSizes( MM_TEXT, CSize(cx, cy) );

	CFormView::OnSize(nType, cx, cy);

	if	(initialized) {
		CRect rc;

		m_iWidth = cx;
		m_iHeight = cy;

		// Save static reference to the render window
		CWnd* pGroup = GetDlgItem(IDC_RENDERWINDOW);
		pGroup->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
		pGroup->GetClientRect(&rc);
		pGroup->MapWindowPoints(this, &rc);

		m_hwndRenderWindow = GetDlgItem(IDC_RENDERWINDOW)->GetSafeHwnd();

		InitializeDevice();
		InitializeDeviceBuffer();

		Render();
	}
}

CPos	gCubePos(0,0,0);	// Position of cube in the world
int		iZoomMouseX, iZoomMouseY;

LRESULT CObjectRightView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	CVec	vec;	// Used to hold camera's forward vector
	CPos	eye;	// Used to hold camera's eye

	double	amt;
	int		iMouseX = LOWORD(lParam),
			iMouseY = HIWORD(lParam);
	static double pitchAmt = 0.0f;

	switch  (message)
    {
		case WM_LBUTTONDOWN:
			iZoomMouseX = iMouseX;
			iZoomMouseY = iMouseY;
			break;
		case WM_MOUSEMOVE:
			//
			//	Mouse moved
			//
			if	(MK_MBUTTON&wParam) 
			{
				//
				//	Mouse button pressed
				//
				vec = gCam->getCamX();
				eye = gCam->getEye();

				eye -= vec * (((float) (iMouseX-iZoomMouseX))/200);
				gCubePos -=  vec * (((float) (iMouseX-iZoomMouseX))/200);

				iZoomMouseX = iMouseX;

				gCam->setEye(eye);
				gCam->setTarget(gCubePos); // Set the camera to look at the cube
				//
				vec = gCam->getCamY();
				eye = gCam->getEye();

				eye += vec * (((float) (iMouseY-iZoomMouseY))/200);
				gCubePos +=  vec * (((float) (iMouseY-iZoomMouseY))/200);

				iZoomMouseY = iMouseY;

				gCam->setEye(eye);
				gCam->setTarget(gCubePos); // Set the camera to look at the cube
				//
				if  (initialized) {
					Render();
				}
			}
			else if	(MK_LBUTTON&wParam)
			{
				amt = (iMouseX - iZoomMouseX) * kCamMoveAmt * 300;
				gCam->rotY(((float) amt * 3.14159265f / 180.0f), gCubePos);
				iZoomMouseX = iMouseX;

				amt = -(iMouseY - iZoomMouseY) * kCamMoveAmt * 300;
				// Cap pitch
				if(pitchAmt + amt < -kMaxAngle)
				{
					amt = -kMaxAngle - pitchAmt;
					pitchAmt = -kMaxAngle;
				}
				else if(pitchAmt + amt > kMaxAngle)
				{
					amt = kMaxAngle - pitchAmt;
					pitchAmt = kMaxAngle;
				}
				else
				{
					pitchAmt += amt;
				}
				// Pitch the camera up/down
				gCam->pitch(((float) amt * 3.14159265f / 180.0f), gCubePos);
				iZoomMouseY = iMouseY;
				if  (initialized) {
					Render();
				}
			}
			else if	(MK_RBUTTON&wParam) 
			{
				vec = gCam->getCamZ();
				eye = gCam->getEye();

				eye += vec * (((float) (iMouseY-iZoomMouseY))/50);

				if	(eye.z > -0.001) {
					eye.z = -0.001f;
				}
				iZoomMouseY = iMouseY;

				gCam->setEye(eye);
				gCam->setTarget(gCubePos); // Set the camera to look at the cube
				if  (initialized) {
					Render();
				}
						
			}
			break;
		case ID_RESET_FRONT:
			m_vecOrigin.x = 0;
			m_vecOrigin.y = 0;
			m_vecOrigin.z = 0;
			gCubePos.x = 0;
			gCubePos.y = 0;
			gCubePos.z = 0;
			gCam->setFront(1,
							  gCubePos.y,
							  gCubePos.z);
			gCam->setTarget(gCubePos); // Set the camera to look at the cube

			if  (initialized) {
				Render();
			}
			break;
		case ID_RESET_SIDE:
			m_vecOrigin.x = 0;
			m_vecOrigin.y = 0;
			m_vecOrigin.z = 0;
			gCubePos.x = 0;
			gCubePos.y = 0;
			gCubePos.z = 0;
			gCam->setSide(1,
							 gCubePos.y,
							 gCubePos.z);
			gCam->setTarget(gCubePos); // Set the camera to look at the cube

			if  (initialized) {
				Render();
			}
			break;
		case 7:
		case 8:
		case 312:
		case  WM_PAINT:
		case  ID_UPDATE_RIGHT_VIEW:
			if  (initialized) {
				Render();
			}
			break;
		case  ID_INIT_RIGHT_VIEW:
			if	(g_pd3dDevice == NULL) {
				InitializeDevice();
			}
			InitializeDeviceBuffer();

			Render();
			break;
		default:
			break;
	}

	return	CFormView::WindowProc(message, wParam, lParam);
}

void CObjectRightView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	if	(!initialized) {
		g_pD3D       = NULL;
		g_pd3dDevice = NULL;
		g_pVB        = NULL;

		GetParentFrame()->RecalcLayout();
		ResizeParentToFit();

		m_hwndRenderWindow = GetDlgItem(IDC_RENDERWINDOW)->GetSafeHwnd();

		CRect rc;
		this->GetWindowRect( &rc );

		m_iWidth = rc.Width();
		m_iHeight = rc.Height();

		CWnd* pGroup = GetDlgItem(IDC_RENDERWINDOW);
		pGroup->SetWindowPos(NULL, 0, 0, m_iWidth, m_iHeight, SWP_NOZORDER);

		InitializeDevice();

		initialized = true;
	}
}

void CObjectRightView::InitializeDevice()
{
	if	(!DirectXStatus) {
		// Reset the device
		if( g_pVB != NULL ) {
			if( FAILED( g_pVB->Release() ) ) {
				DirectXStatus = -1;
				return;
			}
		}

		if( g_pd3dDevice != NULL ) {
			if( FAILED( g_pd3dDevice->Release() ) ) {
				DirectXStatus = -1;
				return;
			}
		}

		if( g_pD3D != NULL ) {
			if( FAILED( g_pD3D->Release() ) ) {
				DirectXStatus = -1;
				return;
			}
		}

		// Create the D3D object.
		if( NULL == ( g_pD3D = Direct3DCreate8( D3D_SDK_VERSION ) ) ) {
			return;
		}

		//
		//	Specific for DirectX 8.0
		//

		D3DDISPLAYMODE d3ddm;
		if	(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
			DirectXStatus = -1;
			return;
		}

		ZeroMemory( &d3dpp, sizeof(d3dpp) );
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = d3ddm.Format;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		// Create the D3DDevice
		if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwndRenderWindow,
										  D3DCREATE_HARDWARE_VERTEXPROCESSING,
										  &d3dpp, &g_pd3dDevice ) ) )
		{
			if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwndRenderWindow,
											  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											  &d3dpp, &g_pd3dDevice ) ) )
			{
				DirectXStatus = -1;
				return;
			}
		}

		// Turn off culling
		if( FAILED( g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ) ) ) {
			DirectXStatus = -1;
			return;
		}

		// Turn on the zbuffer
		if( FAILED( g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE ) ) ) {
			DirectXStatus = -1;
			return;
		}
	}
}

void CObjectRightView::InitializeDeviceBuffer()
{
	if	(noVertices) {
		if	(!DirectXStatus) {
			if( FAILED( g_pd3dDevice->CreateVertexBuffer( noIndices * sizeof(CUSTOMVERTEX),
														  0, D3DFVF_CUSTOMVERTEX,
														  D3DPOOL_DEFAULT, &g_pVB ) ) )
			{
				DirectXStatus = -1;
				return;
			}

			if( FAILED( g_pVB->Lock( 0, 0, (unsigned char **)&pVerticesDeviceBuffer, 0 ) ) ) {
				DirectXStatus = -1;
				return;
			}

			int i = 0;
			while  (i < noIndices) {
				ASSERT(pIndices[i] < noVertices);
				memcpy(&(((CUSTOMVERTEX *) pVerticesDeviceBuffer)[i]), &(((CUSTOMVERTEX *) pVertices)[pIndices[i]]), sizeof(CUSTOMVERTEX));

				i++;
			}

			if	(FAILED( g_pVB->Unlock())) {
				DirectXStatus = -1;
				return;
			}
		}
	}
}

void	CObjectRightView::Render()
{
	if	(!DirectXStatus) {
		// Clear the backbuffer and the zbuffer
		if( FAILED( g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
										 D3DCOLOR_XRGB(0,0,255), 1.0f, 0 ) ) ) {
			DirectXStatus = -1;
			return;
		}

		// Begin the scene
		if	(SUCCEEDED(g_pd3dDevice->BeginScene()))
		{
			// Setup the lights and materials
			if	(SetupLights()) {
				DirectXStatus = -1;
				return;
			}

			// Setup the world, view, and projection matrices
			if	(SetupMatrices()) {
				DirectXStatus = -1;
				return;
			}


			if	(g_pd3dDevice->SetStreamSource(0, g_pVB, sizeof(CUSTOMVERTEX))) {
				DirectXStatus = -1;
				return;
			}

			if	(g_pd3dDevice->SetVertexShader(D3DFVF_CUSTOMVERTEX)) {
				DirectXStatus = -1;
				return;
			}

			D3DMATERIAL8	mtrl;
			mtrl.Diffuse.r = mtrl.Ambient.r = mtrl.Specular.r = 0.4f;
			mtrl.Diffuse.g = mtrl.Ambient.g = mtrl.Specular.g = 0.1f;
			mtrl.Diffuse.b = mtrl.Ambient.b = mtrl.Specular.b = 0.7f;
			mtrl.Diffuse.a = mtrl.Ambient.a = mtrl.Specular.a = 1.0f;
			mtrl.Emissive.r = 0.1f;
			mtrl.Emissive.g = 0.4f;
			mtrl.Emissive.b = 0.02f;
			mtrl.Emissive.a = 0.5f;

			g_pd3dDevice->SetMaterial(&mtrl);

			STRUCT_INSTANCES	* instance = first_instance;
			while  (instance) {
				if	( (instance->parent)  &&
					  (instance->select == ITEM_CHECKED) ){
					g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, instance->startIndex, instance->primitiveCount);  
				}

				instance = instance->next;
			}

			// End the scene
			if( FAILED( g_pd3dDevice->EndScene() ) ) {
				DirectXStatus = -1;
				return;
			}
		}

		// Present the backbuffer contents to the display
		if( FAILED( g_pd3dDevice->Present( NULL, NULL, NULL, NULL ) ) ) {
			DirectXStatus = -1;
			return;
		}
	}
}

int	 CObjectRightView::SetupLights()
{
	float	max = 1;
    // Set up a white, directional light, with an oscillating direction.
    // Note that many lights may be active at a time (but each one slows down
    // the rendering of our scene). However, here we are just using one. Also,
    // we need to set the D3DRS_LIGHTING renderstate to enable lighting
    D3DXVECTOR3 vecDir;
    D3DLIGHT8 light;
    ZeroMemory(&light, sizeof(D3DLIGHT8));
    light.Type       = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r  = 3.4f;
	light.Diffuse.g  = 3.4f;
	light.Diffuse.b  = 3.4f;
	light.Diffuse.a  = 3.4f;
	light.Specular.r = 0.1f;
	light.Specular.g = 0.1f;
	light.Specular.b = 0.1f;
	light.Specular.a = 0.5f;
	light.Ambient.r  = 0.5f;
	light.Ambient.g  = 0.5f;
	light.Ambient.b  = 0.5f;
	light.Ambient.a  = 1.0f;
    light.Position.x = (float) -2.0f;
    light.Position.y = (float) -2.0f;
    light.Position.z = (float) -2.0f;
    vecDir.x = -2.0f;
    vecDir.y = -6.0f;
    vecDir.z = -1.0f;
    D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
    light.Range       = 5.0f;
	if	(FAILED(g_pd3dDevice->SetLight(0, &light))) {
		DirectXStatus = -1;
		return	1;
	}

	if	(FAILED(g_pd3dDevice->LightEnable(0, TRUE))) {
		DirectXStatus = -1;
		return	1;
	}

    D3DLIGHT8 light1;
    ZeroMemory(&light1, sizeof(D3DLIGHT8));
    light1.Type       = D3DLIGHT_DIRECTIONAL;
	light1.Diffuse.r  = 3.4f;
	light1.Diffuse.g  = 3.4f;
	light1.Diffuse.b  = 3.4f;
	light1.Diffuse.a  = 3.4f;
	light1.Specular.r = 0.1f;
	light1.Specular.g = 0.1f;
	light1.Specular.b = 0.1f;
	light1.Specular.a = 0.5f;
	light1.Ambient.r  = 0.5f;
	light1.Ambient.g  = 0.5f;
	light1.Ambient.b  = 0.5f;
	light1.Ambient.a  = 1.0f;
    light1.Position.x = (float) 2.0f;
    light1.Position.y = (float) 2.0f;
    light1.Position.z = (float) 2.0f;
    vecDir.x = 2.0f;
    vecDir.y = 6.0f;
    vecDir.z = 1.0f;
    D3DXVec3Normalize((D3DXVECTOR3*)&light1.Direction, &vecDir);
    light1.Range       = 5.0f;
	if	(FAILED(g_pd3dDevice->SetLight(1, &light1))) {
		DirectXStatus = -1;
		return	1;
	}

	if	(FAILED(g_pd3dDevice->LightEnable(1, TRUE))) {
		DirectXStatus = -1;
		return	1;
	}

	if	(FAILED(g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE))) {
		DirectXStatus = -1;
		return	1;
	}

    // Finally, turn on some ambient light.
    g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00707070);

	return	0;
}

int		CObjectRightView::SetupMatrices()
{
    // For our world matrix, we will just leave it as the identity
    D3DXMATRIX	matWorld;
    D3DXMatrixIdentity( &matWorld );
	
	matWorld._22 = -1.0f;

	D3DXVec3TransformCoord((D3DXVECTOR3 *) &matWorld._41, &m_vecOrigin, &matWorld);

	if( FAILED( g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld ) ) ) {
		DirectXStatus = -1;
		return	1;
	}

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.

    D3DXVECTOR3 vEyePt(2.0f, 3 * ((float) sin(counter)), 4 * ((float) cos(counter)));
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
    D3DXMATRIX matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	if( FAILED( g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView ) ) ) {
		DirectXStatus = -1;
		return	1;
	}

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4,  (float) m_iWidth/(float) m_iHeight, 0.03f, 10.0f );
	if( FAILED( g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj ) ) ) {
		DirectXStatus = -1;
		return	1;
	}

	D3DXMATRIXA16 matrix;

	// Create "D3D Vector" versions of our camera's eye, look at position, and up vector
	D3DXVECTOR3 eye(gCam->getEye().z, gCam->getEye().x, gCam->getEye().y);
	D3DXVECTOR3 lookAt(gCam->getTarget().z, gCam->getTarget().x, gCam->getTarget().y);
	D3DXVECTOR3 up(0, 0, 1); // The world's up vector

	// We create a matrix that represents our camera's view of the world.  Notice
	// the "LH" on the end of the function.  That says, "Hey create this matrix for
	// a left handed coordinate system".
	D3DXMatrixLookAtLH(&matrix, &eye, &lookAt, &up);
	if( FAILED( g_pd3dDevice->SetTransform( D3DTS_VIEW, &matrix ) ) ) {
		DirectXStatus = -1;
	}

	return	0;
}


