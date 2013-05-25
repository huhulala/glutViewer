/*
 * Array.h
 *
 *  Created on: 29.03.2011
 *      Author: ajb_local
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include <vector>
#include <assert.h>
#include <iostream>


#include <stdio.h>
#include <cstring>

#include "Module.h"

template <class T>
class Array {
private:
	T * p_array;
	unsigned int p_size;

public:
	Array(){p_size=0;}
	Array(unsigned int size);
	//Array<T>(const Array<T> & a){*this = a;}
	virtual ~Array();
	unsigned int getSize() const
	{
		return p_size;
	}
	T& operator[](const unsigned int i)
	{
		assert((i<p_size));
		return p_array[i];
	}

	//not needed!
	/*const T& operator[](const unsigned int i) const
	{
		assert((i<p_size));
		return p_array[i];
	}*/

	/*Array(const Array<T>& other)
	: p_size(other.p_size)
	{
	   memcpy(p_array, other.p_array, sizeof(T) * p_size);
	}*/

	/*Array<T>& operator=(const Array<T>& other)
	{
	   p_size = other.p_size;
	   memcpy(p_array, other.p_array, sizeof(T) * p_size);
	   return *this;
	}*/

};

template<typename T>
Array<T>::Array(unsigned int size)
: p_array(new T[size]), p_size(size)
  {
  }

template<typename T>
Array<T>::~Array()
{
  delete [] p_array;
}

#endif /* ARRAY_H_ */
