#include "renderable.h"
#include <GL/glut.h>

Renderable::Renderable() {

}

Renderable::~Renderable() {

}

void Renderable::setMode(RenderMode mode){
	m_renderType = mode;
}

void Renderable::drawGL() const {
	//implement
}
//! Initialize the GLMesh (Allocate GL resources)
void Renderable::init() {
	//implement
}

//! Destroy the resource
void Renderable::destroy() {
	//implement
}

////! Update the GL buffer bindings or display lists of the GLMesh
void Renderable::updateGL() {
	//implement
}

//! Reset the GLMesh
void Renderable::clear() {
	//implement
}

//! Reset the GLMesh
void Renderable::drawImmediate() const {
	//implement
}
