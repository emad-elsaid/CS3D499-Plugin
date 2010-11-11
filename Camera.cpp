#include "Camera.h"


CCamera::CCamera()
{
	m_vecPosition = D3DXVECTOR3(0.0f, 0.0f, -2.5f); // Position vector
	m_vecLookAt = D3DXVECTOR3(0.0f, 0.0f, 1.0f); // Look vector
	m_vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // Up vector
	m_vecRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f); // Right vector
	m_d3ddev = NULL;
}

//------------------------------------------------------------------
// Name: resetCamera
// Desc: Reset the camera
//------------------------------------------------------------------
void CCamera::resetCamera()
{
	m_vecPosition = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	m_vecLookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecUp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMatrixLookAtLH(&m_matView, &m_vecPosition, &m_vecLookAt, &m_vecUp);
	m_d3ddev->SetTransform(D3DTS_VIEW, &m_matView);
}

//------------------------------------------------------------------
// Name: rotateCamera
// Desc: Rotate the camera to an arbitrary axis
//------------------------------------------------------------------
void CCamera::rotateCamera()
{
}

//------------------------------------------------------------------
// Name: walk
// Desc: Camera for walking
//------------------------------------------------------------------
void CCamera::walk(float fUnits)
{
	m_vecPosition += m_vecLookAt * fUnits;
}

//------------------------------------------------------------------
// Name: strafe
// Desc: Camera for strafing
//------------------------------------------------------------------
void CCamera::strafe(float fUnits)
{
// Move only on the XZ plane when the camera is on the land
	m_vecPosition += m_vecRight * fUnits;
}

//------------------------------------------------------------------
// Name: fly
// Desc: Camera for flying
//------------------------------------------------------------------
void CCamera::fly(float fUnits)
{
// Move only on y-axis when the camera is on the land
	m_vecPosition += m_vecUp * fUnits;
}

//------------------------------------------------------------------
// Name: yaw
// Desc: Camera for yawing
//------------------------------------------------------------------

void CCamera::yaw(float fAngle)
{
	::D3DXMatrixRotationAxis(&m_matView, &m_vecUp, fAngle); // Rotate the up vector

	// Rotate right and look vectors around y-axis
	::D3DXVec3TransformCoord(&m_vecRight, &m_vecRight, &m_matView);
	::D3DXVec3TransformCoord(&m_vecLookAt, &m_vecLookAt, &m_matView);
}

//------------------------------------------------------------------
// Name: roll
// Desc: Camera for rolling
//------------------------------------------------------------------
void CCamera::roll(float fAngle)
{
	// Check to see if the camera is on the air

	// Rotate the look-at vector by the specified amount
	::D3DXMatrixRotationAxis(&m_matView, &m_vecLookAt, fAngle);

	// Rotate up and right vectors around look vector
	::D3DXVec3TransformCoord(&m_vecUp, &m_vecUp, &m_matView);
	::D3DXVec3TransformCoord(&m_vecRight, &m_vecRight, &m_matView);
}

//------------------------------------------------------------------
// Name: pitch
// Desc: Camera for pitching
//------------------------------------------------------------------
void CCamera::pitch(float fAngle)
{
	// Rotate around the x-axis
	::D3DXMatrixRotationAxis(&m_matView, &m_vecRight, fAngle);

	// Rotate up and look vectors around the right vector
	::D3DXVec3TransformCoord(&m_vecUp, &m_vecUp, &m_matView);
	::D3DXVec3TransformCoord(&m_vecLookAt, &m_vecLookAt, &m_matView);
}

//------------------------------------------------------------------
// Name: zoom
// Desc: For zooming in and out
//------------------------------------------------------------------
void CCamera::zoom(float fUnits)
{
	m_vecPosition.z = fUnits;
}

void CCamera::setDevice(LPDIRECT3DDEVICE9 d3ddev)
{
	m_d3ddev = d3ddev;
	assert(m_d3ddev);
}
//------------------------------------------------------------------
// Name: getViewMatrix
// Desc: Get the view transformation matrix
//------------------------------------------------------------------
D3DXMATRIX *CCamera::getViewMatrix(D3DXMATRIX *pmatView)
{
	// Normalize the look-at vector
	::D3DXVec3Normalize(&m_vecLookAt, &m_vecLookAt);

	// Keep up vector orthogonal to the look and right vectors
	::D3DXVec3Cross(&m_vecUp, &m_vecLookAt, &m_vecRight);

	// Normalize the up vector
	::D3DXVec3Normalize(&m_vecUp, &m_vecUp);

	// Keep right vector orthogonal to right and up vectors
	::D3DXVec3Cross(&m_vecRight, &m_vecUp, &m_vecLookAt);

	// Normalize the right vector
	::D3DXVec3Normalize(&m_vecRight, &m_vecRight);

	// Build the view matrix
	m_fX = -::D3DXVec3Dot(&m_vecRight, &m_vecPosition); // X-coordinate
	m_fY = -::D3DXVec3Dot(&m_vecUp, &m_vecPosition); // Y-coordinate
	m_fZ = -::D3DXVec3Dot(&m_vecLookAt, &m_vecPosition); // Z-coordinate

	// Modify the values of view transformation matrix
	(*pmatView)(0, 0) = m_vecRight.z; (*pmatView)(0, 1) = m_vecUp.z; (*pmatView)(0, 2) = m_vecLookAt.z; (*pmatView)(0, 3) = 0.0f;
	(*pmatView)(1, 0) = m_vecRight.x; (*pmatView)(1, 1) = m_vecUp.x; (*pmatView)(1, 2) = m_vecLookAt.x; (*pmatView)(1, 3) = 0.0f;
	(*pmatView)(2, 0) = m_vecRight.y; (*pmatView)(2, 1) = m_vecUp.y; (*pmatView)(2, 2) = m_vecLookAt.y; (*pmatView)(2, 3) = 0.0f;
	(*pmatView)(3, 0) = m_fX; (*pmatView)(3, 1) = m_fY; (*pmatView)(3, 2) = m_fZ; (*pmatView)(3, 3) = 1.0f;

	return pmatView;
}