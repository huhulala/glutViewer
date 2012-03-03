#ifndef QUATERION_H_
#define QUATERION_H_

#define PI 3.14159265358979323846

#include "../types/macros.h"
#include "vec3.h"
#include "mat4.h"
#include <math.h>
#include <GL/glut.h>

class Quaternion
{
public:

	//! Axis angle constructor
	Quaternion(FVec3& axis, float angle);
	//! Euler angle constructor
	Quaternion(double roll, double pitch, double yaw);
	//! Uninitialized d constructor
	Quaternion();
	~Quaternion();

	FMat4& transform();

	void mult(const Quaternion &q);

	void CreateMatrix(float *pMatrix);
	void CreateFromAxisAngle(const float &in_x,
			const float &in_y,
			const float &in_z,
			const float &in_degrees);

	Quaternion operator *(const Quaternion &q);

	//! returns the x member
	double getX() const;

	//! returns the y member
	double getY() const;

	//! returns the z member
	double getZ() const;

	double getW() const ;


private:

	float x,
	y,
	z,
	w;
};

#endif
