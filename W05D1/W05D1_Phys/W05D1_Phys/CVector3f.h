#ifndef _CVector3f_HG_
#define _CVector3f_HG_

class CVector3f
{
public:
	CVector3f() : x(0.0f), y(0.0f), z(0.0f) {}
	CVector3f( float init_x, float init_y, float init_z ) : x(init_x), y(init_y), z(init_z) {};
	~CVector3f() {};
	float x, y, z;
};

#endif 