#ifndef MESH_H_
#define MESH_H_

//! A geometry resource on the graphic card
class GLMesh {
public:

	//! Constructor
	GLMesh();

	//! Destructor
	~GLMesh();

	//! Initialize the GLMesh (Allocate GL resources)
	void init();

	//! Destroy the resource
	virtual void destroy();

	////! Update the GL buffer bindings of the GLMesh
	void updateGL();

	//! Draw this GLMesh using OpenGL
	void drawGL() const;

	//! Reset the GLMesh
	void clear();


private:



};



#endif /* MESH_H_ */
