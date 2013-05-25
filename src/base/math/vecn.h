#ifndef VECN_H_
#define VECN_H_

#include "../types/types.h"
#include <iostream>

template<class T, UInt n>
class VecN {
public:
	VecN();

	//! Constructor (uninitialized data)
	VecN(Uninitialized);

	//! The number of components
	static const UInt numComponents = n;

	//! Access an element
	T& operator[](const Int& i);

	const T& operator[](const Int& i) const;

	//! Compute the squared length of the vector
	T sqrLength();

	//! Compute the length of the vector
	T length();

private:
	//! The data of the vector
	T m_data[n];

};

template<class T, UInt n>
T VecN<T, n>::sqrLength() {
	T result = 0;
	for (UInt i = 0; i < n; ++i)
		result += (*this)[i] * (*this)[i];
	return result;
}

template<class T, UInt n>
T VecN<T, n>::length() {
	return sqrt(sqrLength());
}

template<class T, UInt n>
VecN<T, n>::VecN() {
	for (UInt i = 0; i < n; ++i)
		(*this)[i] = T();
}

template<class T, UInt n>
VecN<T, n>::VecN(Uninitialized) {
}

template<class T, UInt n>
T& VecN<T, n>::operator[](const Int& i) {
	return m_data[i];
}

template<class T, UInt n>
const T& VecN<T,n>::operator[](const Int& i) const
{ return m_data[i]; }

#endif /* VECN_H_ */
