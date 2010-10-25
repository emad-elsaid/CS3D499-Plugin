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


#ifndef CAM_H
#define CAM_H

#include "vec.h"

const   double  kCamDist = 2.5f;
const   CVec    kWorldUp(0,1,0);
	
class   CCam
{
	public:
		CCam();
		
		void    rotY(double angle, const CPos &target);
		void    pitch(double angle, const CPos &target);
						
		void    setEye(const CPos &eyePos) { eye = eyePos; }
		void    setTarget(const CPos &target);
		
		void    setFront(double x, double y, double z);
		void    setSide(double x, double y, double z);

		CPos    getTarget() const { return eye + (z * kCamDist); } 
		
		CPos    getEye() const { return eye; }
		CVec    getCamZ() const { return z; }
		CVec    getCamY() const { return y; }
		CVec    getCamX() const { return x; }
		
	private:	
		CVec    x, y, z;
		CPos    eye;
};

extern CCam *gCam;

#endif