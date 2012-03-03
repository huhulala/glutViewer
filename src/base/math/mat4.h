#ifndef MAT4_H_
#define MAT4_H_

#include "matn.h"

#include "../types/macros.h"
#include "vec3.h"
#include <math.h>
#include <GL/glut.h>

//! A 4x4 transformation matrix
/*! The arrangement of the matrix is column-like.
 The index of a specific position is:
 <pre>
 0  4   8  12
 1  5   9  13
 2  6  10  14
 3  7  11  15
 </pre>
 */
template<class T>
class Mat4: public MatN<T, 4> {
	//! Define a type for the parent class
	typedef MatN<T, 4> Inherited;

public:
	//! Default Constructor (identity)
	Mat4();
	//! Constructor using 16 values
	Mat4(const T& m0, const T& m1, const T& m2, const T& m3, const T& m4,
			const T& m5, const T& m6, const T& m7, const T& m8, const T& m9,
			const T& m10, const T& m11, const T& m12, const T& m13,
			const T& m14, const T& m15);

	//! Uninitializing Constructor
	Mat4(Uninitialized);

	//! Set a transformation
	Mat4(Vec3<T>& translate, Vec3<T>& rotate, Vec3<T>& scale);

	void CreateFromAxisAngle(FVec3& axis, float angle);

	void rotateAxisAngle(FVec3& axis, float angle);

	// Overloaded int cast
	operator const float*() {

		float* fMat = new float[16];
		for (int var = 0; var < 16; ++var)
			fMat[var] = (*this)[var];
		return fMat;
	}

	//! Compute the matrix product
	Mat4 operator*(const Mat4& other) const;

	//! Transform given direction vector with matrix
	Vec3<T> multAffineMatDir(Vec3<T>& v);

	//! Transform given point with matrix
	Vec3<T> multAffineMatPoint(Vec3<T>& p);

	void TranslateMatrix(float x, float y, float z);

	void RotateAboutY(float angle);
	void RotateAboutZ(float angle);

};

template<class T>
Mat4<T>::Mat4() {
}

template<class T>
Mat4<T>::Mat4(Uninitialized) :
	Inherited(UNINITIALIZED) {
}

template<class T>
Mat4<T>::Mat4(const T& m0, const T& m1, const T& m2, const T& m3, const T& m4,
		const T& m5, const T& m6, const T& m7, const T& m8, const T& m9,
		const T& m10, const T& m11, const T& m12, const T& m13, const T& m14,
		const T& m15) {
	(*this)[0] = m0;
	(*this)[1] = m1;
	(*this)[2] = m2;
	(*this)[3] = m3;
	(*this)[4] = m4;
	(*this)[5] = m5;
	(*this)[6] = m6;
	(*this)[7] = m7;
	(*this)[8] = m8;
	(*this)[9] = m9;
	(*this)[10] = m10;
	(*this)[11] = m11;
	(*this)[12] = m12;
	(*this)[13] = m13;
	(*this)[14] = m14;
	(*this)[15] = m15;
}

template<class T>
Mat4<T>::Mat4( Vec3<T>& translate,  Vec3<T>& rotate,
                                 Vec3<T>& scale)
{
  T rx = pv::macros::deg2rad(rotate[0]);
  T ry = pv::macros::deg2rad(rotate[1]);
  T rz = pv::macros::deg2rad(rotate[2]);

  Float sinX = sinf(rx);
  Float cosX = cosf(rx);
  Float sinY = sinf(ry);
  Float cosY = cosf(ry);
  Float sinZ = sinf(rz);
  Float cosZ = cosf(rz);

  Float sx = scale[0];
  Float sy = scale[1];
  Float sz = scale[2];

  Float tx = translate[0];
  Float ty = translate[1];
  Float tz = translate[2];

  (*this)[0]  = sx*cosY*cosZ;
  (*this)[1]  = sx*cosY*sinZ;
  (*this)[2]  = -sx*sinY;
  (*this)[3]  = 0.0f;
  (*this)[4]  = sy*(-cosX*sinZ + sinX*sinY*cosZ);
  (*this)[5]  = sy*(cosX*cosZ + sinX*sinY*sinZ);
  (*this)[6]  = sy*sinX*cosY;
  (*this)[7]  = 0;
  (*this)[8]  = sz*(sinX*sinZ + cosX*sinY*cosZ);
  (*this)[9]  = sz*(-sinX*cosZ + cosX*sinZ*sinY);
  (*this)[10] = sz*cosX*cosY;
  (*this)[11] = 0;
  (*this)[12] = tx;
  (*this)[13] = ty;
  (*this)[14] = tz;
  (*this)[15] = 1;
}

template<class T>
Mat4<T> Mat4<T>::operator*(const Mat4<T>& other) const {
	Mat4<T> result(UNINITIALIZED);
	for (Int i = 0; i < 4; i++)
		for (Int j = 0; j < 4; j++) {

			result(i, j) = (*this)(i, 0) * other(0, j) + (*this)(i, 1) * other(
					1, j) + (*this)(i, 2) * other(2, j) + (*this)(i, 3)
					* other(3, j);

		}

	return result;
}

template<class T>
Vec3<T> Mat4<T>::multAffineMatDir(Vec3<T>& v) {
	return Vec3<T> ((*this)[0] * v[0] + (*this)[4] * v[1] + (*this)[8] * v[2],
			(*this)[1] * v[0] + (*this)[5] * v[1] + (*this)[9] * v[2],
			(*this)[2] * v[0] + (*this)[6] * v[1] + (*this)[10] * v[2]);
}

template<class T>
Vec3<T> Mat4<T>::multAffineMatPoint(Vec3<T>& p) {
	return Vec3<T> (
			(*this)[0] * p[0] + (*this)[4] * p[1] + (*this)[8] * p[2]
					+ (*this)[11],

			(*this)[1] * p[0] + (*this)[5] * p[1] + (*this)[9] * p[2]
					+ (*this)[12],

			(*this)[2] * p[0] + (*this)[6] * p[1] + (*this)[10] * p[2]
					+ (*this)[13]);
}

template<class T>
void Mat4<T>::CreateFromAxisAngle(FVec3& axis, float angle) {

	float sine = (float) sin(-angle);
	float cosine = (float) cos(-angle);
	float t = 1.0f - cosine;

	axis.normalize();
	(*this)[0] = t * axis[0] * axis[0] + cosine;
	(*this)[1] = t * axis[0] * axis[1] - sine * axis[2];
	(*this)[2] = t * axis[0] * axis[2] + sine * axis[1];
	(*this)[3] = 0.0f;
	(*this)[4] = t * axis[0] * axis[1] + sine * axis[2];
	(*this)[5] = t * axis[1] * axis[1] + cosine;
	(*this)[6] = t * axis[1] * axis[2] - sine * axis[0];
	(*this)[7] = 0.0f;
	(*this)[8] = t * axis[0] * axis[2] - sine * axis[1];
	(*this)[9] = t * axis[1] * axis[2] + sine * axis[0];
	(*this)[10] = t * axis[2] * axis[2] + cosine;
	(*this)[11] = 0.0f;
	(*this)[12] = 0;
	(*this)[13] = 0;
	(*this)[14] = 0;
	(*this)[15] = 1;
}

template<class T>
void Mat4<T>::rotateAxisAngle(FVec3& axis, float angle) {

	// convert to radians
	angle = pv::macros::deg2rad(angle);

	// make a normalized quaternion
	double w = cos(0.5 * angle);
	double f = sin(0.5 * angle) / sqrt(
			axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
	axis[0] *= f;
	axis[1] *= f;
	axis[2] *= f;

	// convert the quaternion to a matrix
	//double matrix[4][4];

	double ww = w * w;
	double wx = w * axis[0];
	double wy = w * axis[1];
	double wz = w * axis[2];

	double xx = axis[0] * axis[0];
	double yy = axis[1] * axis[1];
	double zz = axis[2] * axis[2];

	double xy = axis[0] * axis[1];
	double xz = axis[0] * axis[2];
	double yz = axis[1] * axis[2];

	double s = ww - xx - yy - zz;

	Mat4<T> rotation = Mat4<T> ();
	rotation(0, 0) = xx * 2 + s;
	rotation(1, 0) = (xy + wz) * 2;
	rotation(2, 0) = (xz - wy) * 2;

	rotation(0, 1) = (xy - wz) * 2;
	rotation(1, 1) = yy * 2 + s;
	rotation(2, 1) = (yz + wx) * 2;

	rotation(0, 2) = (xz + wy) * 2;
	rotation(1, 2) = (yz - wx) * 2;
	rotation(2, 2) = zz * 2 + s;

	(*this) = (*this) * rotation;
}

template<class T>
void Mat4<T>::RotateAboutY(float angle) {

	Mat4<T> rotation = Mat4<T> ();
	float sine = (float) sin(angle);
	float cosine = (float) cos(angle);

	rotation[0] = cosine;
	rotation[8] = sine;
	rotation[2] = -sine;
	rotation[10] = cosine;
	(*this) = (*this) * rotation;
}

template<class T>
void Mat4<T>::RotateAboutZ(float angle) {

	Mat4<T> rotation = Mat4<T> ();
	float sine = (float) sin(angle);
	float cosine = (float) cos(angle);

	rotation[0] = cosine;
	rotation[1] = -sine;
	rotation[4] = sine;
	rotation[5] = cosine;
	(*this) = (*this) * rotation;
}

template<class T>
void Mat4<T>::TranslateMatrix(float x, float y, float z) {

	(*this)[12] = x;
	(*this)[13] = y;
	(*this)[14] = z;
}

//template<class T>
//void Mat4<T>::CreateFromAxisAngle(FVec3& axis, float angle)
//{
//	Float angle1 = -angle;
//float cos = (float)cos(angle1);
//float cosine = (float) cos(-angle);
//float sin = (float)sin(angle1);
//float t = 1.0f - cos;

//axis.Normalize();

//result = new Matrix4(t * axis.X * axis.X + cos, t * axis.X * axis.Y - sin * axis.Z, t * axis.X * axis.Z + sin * axis.Y, 0.0f,
//		t * axis.X * axis.Y + sin * axis.Z, t * axis.Y * axis.Y + cos, t * axis.Y * axis.Z - sin * axis.X, 0.0f,
//		t * axis.X * axis.Z - sin * axis.Y, t * axis.Y * axis.Z + sin * axis.X, t * axis.Z * axis.Z + cos, 0.0f,
//		0, 0, 0, 1);
//}


//! Define a 3-dimensional float matrix
typedef Mat4<Float> FMat4;

#endif /* MAT4_H_ */
