#ifndef VEC3_H_
#define VEC3_H_

#include "vecn.h"
#include <math.h>

template<class T>
class Vec3: public VecN<T, 3> {

	//! Define a type for the parent class
	typedef VecN<T, 3> Inherited;

public:
	//! Default Constructor (identity)
	Vec3();
	//! Constructor using 3 values
	Vec3(const T& m0, const T& m1, const T& m2);

	//! Uninitializing Constructor
	Vec3(Uninitialized);

	/** @name Operations */
	//@{
	//! Addition operator
	Vec3 operator+(Vec3& other);

	//! Scalar multiplication operator
	Vec3 operator*(T& factor);

	//! Subtraction operator
	Vec3 operator-(Vec3& other);

	//! Division operator
	Vec3 operator/(T divisor);

	//! Cross product operator
	Vec3 operator^(Vec3& other);

	//! Compute the normalized vector
	Vec3 normalized();

	//! Compute the normalized vector
	void normalize();

	//@}

};

template<class T>
Vec3<T>::Vec3() {
}

template<class T>
Vec3<T>::Vec3(Uninitialized) :
	Inherited(UNINITIALIZED) {
}

template<class T>
Vec3<T>::Vec3(const T& m0, const T& m1, const T& m2) {
	(*this)[0] = m0;
	(*this)[1] = m1;
	(*this)[2] = m2;
}

template<class T>
Vec3<T> Vec3<T>::operator*(T& factor) {
	return Vec3(factor * (*this)[0], factor * (*this)[1], factor * (*this)[2]);
}

template<class T>
Vec3<T> Vec3<T>::operator+(Vec3& other) {
	return Vec3((*this)[0] + other[0], (*this)[1] + other[1],
			(*this)[2] + other[2]);
}

template<class T>
Vec3<T> Vec3<T>::operator-(Vec3& other) {
	return Vec3((*this)[0] - other[0], (*this)[1] - other[1],
			(*this)[2] - other[2]);
}

template<class T>
Vec3<T> Vec3<T>::operator^(Vec3& other) {
	Vec3 result(UNINITIALIZED);
	result[0] = (*this)[1] * other[2] - (*this)[2] * other[1];
	result[1] = (*this)[2] * other[0] - (*this)[0] * other[2];
	result[2] = (*this)[0] * other[1] - (*this)[1] * other[0];
	return result;
}

template<class T>
Vec3<T> Vec3<T>::operator/(T divisor) {
	return Vec3((*this)[0] / divisor, (*this)[1] / divisor,
			(*this)[2] / divisor);
}

template<class T>
Vec3<T> Vec3<T>::normalized() {

	return (*this) / this->length();
}

template<class T>
void Vec3<T>::normalize() {

	T length = this->length();
	if (length == 0)
		length = 1;

	(*this)[0] = (*this)[0] / length;
	(*this)[1] = (*this)[1] / length;
	(*this)[2] = (*this)[2] / length;
}

//! Define a 3-dimensional float vector
typedef Vec3<Float> FVec3;

//! Define a 3-dimensional ID vector
typedef Vec3<ID> IDVec3;

#endif /* VEC3_H_ */
