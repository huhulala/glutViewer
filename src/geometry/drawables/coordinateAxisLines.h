#ifndef PV__COORDINATE_AXIS_H__
#define PV__COORDINATE_AXIS_H__

#include "../../base/types/types.h"
#include "../renderable.h"


BEGIN_PV_NAMESPACE

//! Class that draws 3 coordinate axis with opengl calls 
/*!
 A class that draws just three lines that represent the x-, y- and z-axis in their
 typical color.
 */
class CoordinateAxisLines : Renderable {
public:
	//! Default Constructor
	CoordinateAxisLines(Float size);

	//! Method that draws the axis
	void drawGL() const;

private:
	Float m_size;

};

END_PV_NAMESPACE

#endif

