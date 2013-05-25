#ifndef PV_COL3_H_
#define PV_COL3_H_


#include "../types/types.h"
#include "../math/vecn.h"

BEGIN_PV_NAMESPACE

//! A 3 component color (rgb)
template<class T>
class Col3 : public VecN<T,3>
{
	//! Define a type for the parent class
	typedef VecN<T,3> Inherited;

public:
	//! Default Constructor (0,0,0)
	Col3();

	//! Uninitializing constructor
	Col3(Uninitialized);

	//! Constructor with given values
	Col3(const T& v0, const T& v1, const T& v2);
};

template<class T>
Col3<T>::Col3()
{
	(*this)[0] = T();
	(*this)[1] = T();
	(*this)[2] = T();
}

template<class T>
 Col3<T>::Col3(Uninitialized)
: Inherited(UNINITIALIZED)
{}

template<class T>
Col3<T>::Col3(const T& v0, const T& v1, const T& v2)
{
	(*this)[0] = v0;
	(*this)[1] = v1;
	(*this)[2] = v2;
}

//! Define a 3-component quantitzed color
typedef Col3<UChar> UCCol3;

//! Define a 3-component hdr color
typedef Col3<Float> FCol3;

END_PV_NAMESPACE

#endif /* COL3_H_ */
