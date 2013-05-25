#ifndef MATN_H_
#define MATN_H_

#include "../types/types.h"
#include <iostream>

template<class T, UInt n>
class MatN {

public:
	MatN();

	//! Constructor (uninitialized data)
	MatN(Uninitialized);

	//! Access an element
	T& operator[](const Int& i);

	//! Access an element
	const T& operator()(const Int& i, const Int& j) const;

	//! Access an element
	T& operator()(const Int& i, const Int& j);

	//! Cast operator to const T*
	operator const T*() const;

	//! Cast operator to const T*
	operator  T*() ;

	//! Initialize the matrix to identity
	void setIdentity();

	//! Is  the matrix identity
	Bool isIdentity();

	T& get(const Int& i, const Int& j);

	void print();

protected:

private:
	//! The data of the small matrix
	T m_data[n * n];

};

template<class T, UInt n>
MatN<T, n>::MatN() {
	setIdentity();
}

template<class T, UInt n>
MatN<T, n>::MatN(Uninitialized) {
}

template<class T, UInt n>
T& MatN<T, n>::operator[](const Int& i) {
	return m_data[i];
}

template<class T, UInt n>
T& MatN<T, n>::get(const Int& i, const Int& j) {
	return m_data[i + j * n];
}

template<class T, UInt n>
const T& MatN<T, n>::operator()(const Int& i, const Int& j) const {
	return m_data[i + j * n];
}

template<class T, UInt n>
T& MatN<T, n>::operator()(const Int& i, const Int& j) {
	return m_data[i + j * n];
}

template<class T, UInt n>
void MatN<T, n>::setIdentity() {
	for (UInt j = 0; j < n; ++j) {
		for (UInt i = 0; i < n; ++i)
			(*this)(i, j) = (i == j) ? 1 : 0;
	}
}

template<class T, UInt n>
void MatN<T, n>::print() {
	for (UInt j = 0; j < n; ++j) {
		std::cout << std::endl;
		for (UInt i = 0; i < n; ++i)
			std::cout << (*this)(j, i) << " ";
	}
}

template<class T, UInt n>
MatN<T, n>::operator const T*() const {
	return m_data;
}

template<class T, UInt n>
MatN<T, n>::operator  T*()  {
	return m_data;
}


template<class T, UInt n>
Bool MatN<T, n>::isIdentity() {
	Bool identity = TRUE;
	for (Int j = 0; j < n; ++j) {
		for (Int i = 0; i < n; ++i)
			if (i == j) {
				if (((*this)(i, j)) != 1) {
					identity = FALSE;
					break;
				}
			} else {
				if (((*this)(i, j)) != 0) {
					identity = FALSE;
					break;
				}
			}
	}
	return identity;
}

#endif
