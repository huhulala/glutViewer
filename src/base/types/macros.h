#ifndef MACROS_H_
#define MACROS_H_

#include "types.h"
#include <cmath>

BEGIN_PV_NAMESPACE

//! This namespace provides generic static helper functions
namespace macros {

	template<class T> T deg2rad(const T& angle)
	{	return angle * M_PI / 180.0;}

	template<class T> T rad2deg(const T& angle)
	{	return angle *180.0 / M_PI;}

	template<class T1, class T2>
	PtrInt byteOffset(const T1* p1, const T2* p2)
	{	return reinterpret_cast<const Byte*>(p2) - reinterpret_cast<const Byte*>(p1);}

	template<class T>
	T clip(const T& v, const T& low, const T& high)
	{
		ASSERT(low<=high);
		if(v<low)
		return low;
		else if(v>high)
		return high;
		return v;
	}

} // End macros namespace
END_PV_NAMESPACE

#endif /* MACROS_H_ */
