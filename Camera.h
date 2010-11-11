#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx9.h>
#include <d3d9.h>
#include <assert.h>



// CD3DCamera class
class CCamera {
public:
	CCamera(); // Constructor

	void resetCamera(); // Reset the camera
	void rotateCamera(); // Rotate the camera
	void walk(float fUnits); // Camera fo walking
	void strafe(float fUnits); // Camera for strafing
	void fly(float fUnits); // Camera for flying
	void yaw(float fAngle); // Camera for yawing
	void roll(float fAngle); // Camera for rolling
	void pitch(float fAngle); // Camera for pitching
	void zoom(float fUnits); // For zooming and out
	void setDevice(LPDIRECT3DDEVICE9); //Set the D3DDevice
	D3DXMATRIX *getViewMatrix(D3DXMATRIX *pmatView); // Get view transformation matrix

private:
	POINT m_point; // Screen coordinates

	D3DXMATRIXA16 m_matView; // View transformation matrix

	float m_fX, m_fY, m_fZ; // View positions
	
	LPDIRECT3DDEVICE9 m_d3ddev;
	
	D3DXVECTOR3 m_vecPosition, m_vecUp, m_vecRight, m_vecLookAt; // 3D vectors

	
};

extern CCamera *g_Camera; // Externed class pointer

#endif // D3DCAMERA_H
