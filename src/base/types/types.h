#ifndef TYPES_H_
#define TYPES_H_

#include <iostream>
#include <cassert>
#include <stdint.h>
#include  <string>
using namespace std;

#define BEGIN_PV_NAMESPACE namespace pv {
#define END_PV_NAMESPACE }
#define USE_PV_NAMESPACE using namespace pv;

//! Define an integer of the same size as a pointer
typedef intptr_t PtrInt;
//! Define an unsigned integer of the same size as a pointer
typedef uintptr_t PtrUInt;

// Define some standard types
typedef string String;
typedef bool Bool;
typedef char Char;
typedef int Int;
typedef unsigned char Byte;
typedef unsigned char UChar;
typedef unsigned int UInt;
typedef float Float;
typedef UInt ID;
#define ID_NONE ID(-1)
#define TRUE Bool(1);
#define FALSE Bool(0);

//! A type, used for providing constructors that don't initialize their members
/*! Those uninitializing constructors can be used, if the object's content will
 be set completely before the first usage of the object. This doesn't provide
 any speed improvements in release builds, because the compiler strips the
 unnecessary initialization of the members in the default constructor anyway,
 but in debug builds it can provide a significant speed improvement.
 */
enum Uninitialized {
	UNINITIALIZED
};

#endif /* TYPES_H_ */
