#ifndef RENDERABLE_H_
#define RENDERABLE_H_

//! A geometry resource on the graphic card
class Renderable {
public:

	enum RenderMode {
		IMMEDIATE, DISPLAYLIST
	};

	//! Constructor
	Renderable();

	//! Destructor
	virtual ~Renderable();

	//! Initialize the GLMesh (Allocate GL resources)
	void setMode(RenderMode mode);

	//! Initialize the GLMesh (Allocate GL resources)
	virtual void init();

	//! Destroy the resource
	virtual void destroy();

	////! Update the GL buffer bindings or display lists of the GLMesh
	virtual void updateGL();

	//! Draw this GLMesh using OpenGL
	virtual void drawGL() const;

	//! Draw the mesh with OpenGL glBegin/glEnd statements
	virtual void drawImmediate() const ;

	//! Reset the GLMesh
	virtual void clear();

protected:

	RenderMode m_renderType;

private:



};

#endif /* RENDERABLE_H_ */
