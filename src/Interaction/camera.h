#ifndef PV_CAMERA_H
#define PV_CAMERA_H

#include <GL/glut.h>

#include "../base/types/types.h"
#include "../base/math/mat4.h"
#include "../base/math/vec2.h"
#include "../base/math/vec3.h"
#include "../base/math/quaternion.h"

BEGIN_PV_NAMESPACE

//! This class represents a virtual camera
class Camera
{
public:
	Camera();
	virtual ~Camera();

	//! The projection type
	enum ProjectionType {
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

	void rotatePoint( double dx, double dy);

	//! Uses the camera attributes to compute a view matrix
	virtual void lookAtScene();

	//! Uses the camera attributes to set the projection
	virtual void project(IVec2& viewSize);

	//! Left and right are along the normal vector to the camera - normals
	// only change under a rotation.
	void moveLeft(Float dist);

	//! Left and right are along the normal vector to the camera - normals
	// only change under a rotation.
	void moveRight(Float dist);

	//" Up and down are along the camera's up and down vector
	void moveUp(Float dist);

	//" Up and down are along the camera's up and down vector
	void moveDown(Float dist);

	//! Dolly along the view vector
	void dolly(Float dist);

	//! Zoom along the view vector
	void zoom(Float dist);

	//! Reset camera position
	void reset();

	//! Print camera values
	void print();

	//! Compute a projection matrix based on the GLRenderViewport given values
	FMat4 projection( IVec2& viewSize, FVec2& sample);

	//virtual FMat4 projection(const IVec2& viewSize) const;
	void calculateNormal();

	//! Sets image
	void setImageSize(Int w, Int h);

	//! Sets center position
	void setCenter(Float cX, Float cY, Float cZ);

	//! Sets up vector
	void setUp(Float cX, Float cY, Float cZ);

	//! Sets eye position
	void setEye(Float cX, Float cY, Float cZ);

	//! Sets fov
	void setFov(Float fov);

	//! Query eye position
	FVec3& eye();

	//! Query center position
	FVec3& center();

	//! Query up position
	FVec3& up();

	//! Query distance
	Float& distance();

	//! Query near
	Float& near();

	//! Query fov
	Float& fov();

	//! Query near/far
	FVec2& frustrum();

	//! Camera roll (rotate around view vector)
	void roll(Float angle);

	//! Camera pitch (rotate around normal vector)
	void pitch(Float delta);

	//! Camera yaw (rotate around up vector)
	void yaw(Float delta);

	//! Camera yaw (rotate around up vector)
	void pan(const Float speed,int x, int y);

	//! Camera yaw (rotate around up vector)
	void rotate(const Float speed,int x, int y);

	void applyTransform( FMat4& transform);

	void ComputeDistance();

protected:
	//! Compute a projection matrix
	//virtual void updateProjectionMatrix();

private:

	//! near far planes
	FVec2 m_frustrum;

	//! The distance to the focal point
	Float m_distance;

	//! Eye position
	FVec3 m_eye;

	//! Center position
	FVec3 m_center;

	//! Up vector
	FVec3 m_up;

	//! Normal to the eye position
	FVec3 m_normal;

	// View to scene center vector
	FVec3 m_view;

	//! The size of the intended image (specifies aspect ratio)
	IVec2 m_imageSize;

	IVec2 m_mouseStartPos;

	//! The field of view
	Float m_fovY;

	//! The projection matrix for the rendered image
	FMat4 projectionMatrix;

	// Cumulative eye rotation
	double rotationEyeX;
	double rotationEyeY;

};

inline FVec2& Camera::frustrum() {
	return m_frustrum;
}

inline FVec3& Camera::eye() {
	return m_eye;
}

inline FVec3& Camera::center() {
	return m_center;
}

inline FVec3& Camera::up() {
	return m_up;
}

inline Float& Camera::fov() {
	return m_fovY;
}

inline Float& Camera::distance() {
	return m_frustrum[1];
}

END_PV_NAMESPACE

#endif

