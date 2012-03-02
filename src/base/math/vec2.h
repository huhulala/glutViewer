#ifndef VEC2_H_
#define VEC2_H_

#include "vecn.h"
#include <math.h>

template<class T>
class Vec2: public VecN<T, 2> {

	//! Define a type for the parent class
	typedef VecN<T, 2> Inherited;

public:
	//! Default Constructor (identity)
	Vec2();
	//! Constructor using 2 values
	Vec2(const T& m0, const T& m1);

	//! Uninitializing Constructor
	Vec2(Uninitialized);

	/** @name Operations */
	  //@{
	  //! Subtraction operator
	Vec2 operator-(Vec2& other);
	//@}

};

template<class T>
Vec2<T>::Vec2() {
}

template<class T>
Vec2<T>::Vec2(Uninitialized) :
	Inherited(UNINITIALIZED) {
}

template<class T>
Vec2<T>::Vec2(const T& m0, const T& m1) {
	(*this)[0] = m0;
	(*this)[1] = m1;
}

template<class T>
Vec2<T> Vec2<T>::operator-( Vec2& other)
{ return Vec2((*this)[0]-other[0], (*this)[1]-other[1]); }


//! Define a 3-dimensional float vector
typedef Vec2<Float> FVec2;

//! Define a 3-dimensional float vector
typedef Vec2<Int> IVec2;

#endif /* VEC2_H_ */
