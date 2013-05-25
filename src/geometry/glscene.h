#ifndef PV_SCENE_H_
#define PV_SCENE_H_

#include "renderable.h"
#include <vector>
#include "glmesh.h"
#include <GL/glut.h>

BEGIN_PV_NAMESPACE

//! A collection of flat GLMesh objects
class GLScene: Renderable {
public:

	//! Constructor
	GLScene();
	~GLScene();

	//! The render type
	enum RenderType {
		IMMEDIATE,
		DISPLAYLIST,
		DISPLAYLISTS,
	};

	//! Initialize the GLScene (Allocate GL resources)
	void init();

	//! Destroy the resource
	virtual void destroy();

	//! Update the GL buffer bindings or display lists of the GLMesh
	void updateGL();

	//! Draw this GLScene using OpenGL
	void drawGL() const;

	//! Reset the GLScene
	void clear();

	//Add to vector
	void add(Renderable* mesh);

	//Add to vector
	std::vector<Renderable*> getRenderables();

private:

	//! Display list id
	GLuint m_listID;

	RenderType m_renderType;

	//! The data vector
	std::vector<Renderable*> m_vmeshes;

};

END_PV_NAMESPACE

#endif /* MESH_H_ */

