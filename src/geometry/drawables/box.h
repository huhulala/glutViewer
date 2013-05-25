#ifndef BOX_H_
#define  BOX_H_

#include "../renderable.h"
#include "../../structure/mesh.h"
#include <vector>
#include <GL/glut.h>

BEGIN_PV_NAMESPACE

//! A geometry resource on the graphic card
class Box: public Renderable {
public:

	//! Define a type for the parent class
	typedef Renderable Inherited;

	//! Default Constructor
	Box(FVec3 pos,FVec3 extend);

	//! Destructor
	virtual ~Box();

	//! Initialize the GLMesh (Allocate GL resources)
	void init();

	//! Destroy the resource
	virtual void destroy();

	////! Update the GL buffer bindings or display lists of the GLMesh
	void updateGL();

	//! Draw this GLMesh using OpenGL
	void drawGL() const;

	//! Draw the mesh with OpenGL glBegin/glEnd statements
	void drawImmediate() const;

	//! Reset the GLMesh
	void clear();

	const FVec3 center() ;

	const FVec3 extend() ;

private:

	//! Display list id
	GLuint m_listID;

	FVec3 m_center;

	FVec3 m_halfExtend;

};

END_PV_NAMESPACE

#endif /* MESH_H_ */

