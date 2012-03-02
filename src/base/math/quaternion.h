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

	Quaternion(FVec3& axis, float angle);
	Quaternion();
	~Quaternion();

	FMat4& transform();
	void CreateMatrix(float *pMatrix);
	void CreateFromAxisAngle(const float &in_x,
			const float &in_y,
			const float &in_z,
			const float &in_degrees);

	Quaternion operator *(const Quaternion &q);

private:

	float x,
	y,
	z,
	w;
};

#endif
