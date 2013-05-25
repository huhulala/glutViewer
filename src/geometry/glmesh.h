#ifndef GLMESH_H_
#define  GLMESH_H_

#include "renderable.h"
#include "../structure/mesh.h"
#include <vector>
#include "../base/math/vec3.h"
#include <GL/glut.h>

BEGIN_PV_NAMESPACE

//! A geometry resource on the graphic card
class GLMesh: public Renderable {
public:

	//! Constructor
	GLMesh();

	//! Destructor
	virtual ~GLMesh();

	//! Initialize the GLMesh (Allocate GL resources)
	void init();

	//! Destroy the resource
	virtual void destroy();

	////! Update the GL buffer bindings or display lists of the GLMesh
	void updateGL();

	//! Draw this GLMesh using OpenGL
	void drawGL() const;

	//! Draw the mesh with OpenGL glBegin/glEnd statements
	virtual void drawImmediate() const;

	//! Reset the GLMesh
	void clear();

private:
	//! Rendermode
	RenderMode m_mode;

	//! Display list id
	GLuint m_listID;

};

END_PV_NAMESPACE

#endif /* MESH_H_ */

