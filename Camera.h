#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx9.h>
#include <d3d9.h>
#include <assert.h>



// CD3DCamera class
class CCamera
{
private:
	D3DXVECTOR3 m_position; // camera position
	float m_yaw;  // rotation around the y axis
	float m_pitch; // rotation around the x axis
	
	D3DXVECTOR3 m_up,m_look,m_right; // camera axis

	float restrictAngleTo360Range(float angle) const;
public:
	CCamera(D3DXVECTOR3 startPos);
	~CCamera(void);

	void calculateViewMatrix(D3DXMATRIX *viewMatrix);

	// Gets
	float getYaw() const {return m_yaw;}
	float getPitch() const {return m_pitch;}
	D3DXVECTOR3 getPosition() const {return m_position;}	

	// Move operations
	void moveForward(float amount) {m_position+=m_look*amount;}
	void moveRight(float amount) {m_position+=m_right*amount;}
	void moveUp(float amount) {m_position+=m_up*amount;}

	// Rotations
	void yaw(float amount); // rotate around x axis
	void pitch(float amount); // rotate around x axis
	
	

	void rotateCamera(float x, float y);
};


extern CCamera *g_Camera; // Externed class pointer

#endif // D3DCAMERA_H
