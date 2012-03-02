#include "camera.h"
#include "../base/types/macros.h"
#include <iostream>

BEGIN_PV_NAMESPACE

Camera::Camera():
m_frustrum(FVec2(1.0,1000.0)),
m_eye(FVec3(0.0,0.0,0.0)),
m_center(FVec3(0.0,0.0,0.0)) ,
m_up(FVec3(0.0,0.0,0.0)) {
	m_fovY = 30.0;
	m_distance = 999.0;
}

Camera::~Camera() {

}

void Camera::lookAtScene() {
	//implement
}

void Camera::project(IVec2& viewSize) {
	//implement
}

void Camera::print() {
	std::cout <<"------------------------------------------"<<endl;
	std::cout <<"eye: "<<m_eye[0]<<" "<<m_eye[1]<<" "<<m_eye[2]<< endl;
	std::cout <<"center: "<<m_center[0]<<" "<<m_center[1]<<" "<<m_center[2]<< endl;
	std::cout <<"up: "<<m_up[0]<<" "<<m_up[1]<<" "<<m_up[2]<< endl;
	std::cout <<"view: "<<m_view[0]<<" "<<m_view[1]<<" "<<m_view[2]<< endl;
	std::cout <<"normal: "<<m_normal[0]<<" "<<m_normal[1]<<" "<<m_normal[2]<< endl;
}

void Camera::setEye(Float cX, Float cY, Float cZ) {
	m_eye[0]=cX;
	m_eye[1]=cY;
	m_eye[2]=cZ;
}

void Camera::setFov(Float fov) {
	m_fovY=fov;
}

void Camera::setCenter(Float cX, Float cY, Float cZ) {
	m_center[0]=cX;
	m_center[1]=cY;
	m_center[2]=cZ;
	calculateNormal();
}

void Camera::setUp(Float cX, Float cY, Float cZ) {
	m_up[0]=cX;
	m_up[1]=cY;
	m_up[2]=cZ;
}

void Camera::roll(Float angle) {

	FMat4 rotation = FMat4 ();
	rotation.CreateFromAxisAngle(m_view,angle);
	m_normal = rotation.multAffineMatDir(m_normal);
	m_up = rotation.multAffineMatDir(m_up);
}

void Camera::pitch(Float delta)
{
	FMat4 rotation = FMat4 ();
	rotation.CreateFromAxisAngle(m_normal,delta);
	m_view = rotation.multAffineMatDir(m_view);
	m_up = rotation.multAffineMatDir(m_up);
	m_center = m_eye+m_view;
}

void Camera::yaw(Float delta)
{
	FMat4 matrix = FMat4 ();
	matrix.CreateFromAxisAngle(m_up,delta);
	m_view = matrix.multAffineMatDir(m_view);
	m_normal = matrix.multAffineMatDir(m_normal);
	m_center = m_eye+m_view;
}

void Camera::moveRight(Float dist)
{
	FVec3 temp = m_normal*dist;
	m_eye = m_eye + temp;
	m_center = m_center + temp;
}

void Camera::setImageSize(Int w, Int h) {
	m_imageSize[0]=w;
	m_imageSize[1]=h;
}

void Camera::moveLeft(Float dist)
{
	Float negate=-dist;
	FVec3 temp = m_normal*negate;
	m_eye = m_eye + temp;
	m_center = m_center + temp;
}

// Up and down are along the camera's up and down vector
void Camera::moveUp(Float dist)
{
	FVec3 temp = m_up*dist;
	m_eye = m_eye + temp;
	m_center = m_center + temp;
}

void Camera::moveDown(Float dist)
{
	Float negate=-dist;
	FVec3 temp = m_up*negate;
	m_eye = m_eye + temp;
	m_center = m_center + temp;
}

void Camera::dolly(Float dist) {

	FVec3 temp = m_view*dist;
	m_eye = m_eye + temp;
	//m_center = m_center + temp;
	ComputeDistance();
}

void Camera::ComputeDistance()
{
	FVec3 delta = m_center - m_eye;
	m_distance = delta.length();
}

void Camera::zoom(Float amount)
{
	this->setFov(fov()/amount);
}

void Camera::pan(const Float speed,int x, int y) {

	std::cout<<"x: "<<x<<" "<<"y: "<<y<<endl;

	float dx = (float) (x) / (float) (m_imageSize[0]);
	float dy = (float) (y) / (float) (m_imageSize[1]);

	if (0) {
		//Do parallel here
	} else {
		double scale = 2 * tan(macros::deg2rad(m_fovY / 2));
		scale *= m_distance;
		dx *= scale;
		dy *= scale;
	}

	std::cout<<"dx: "<<dx<<" "<<"dy: "<<dy<<endl;

	// Performs the following vector math:
	// pos += dx*right + dy*up;
	// fp += dx*right + dy*up;
	double tmp;
	FVec3 pos =m_eye;
	FVec3 fp = m_center;
	tmp = (m_normal[0] * dx + m_up[0] * dy);
	pos[0] += tmp*speed;
	fp[0] += tmp*speed;
	tmp = (m_normal[1]* dx + m_up[1]* dy);
	pos[1] += tmp*speed;
	fp[1] += tmp*speed;
	tmp = (m_normal[2] * dx + m_up[2] * dy);
	pos[2] += tmp*speed;
	fp[2] += tmp*speed;

	m_eye = pos;
	m_center = fp;
}

void Camera::rotate(const Float speedFactor,int x, int y) {

	std::cout<<"x: "<<x<<"y: "<<y<<endl;

	double scale = m_eye.length();

	FVec3 scaledEye =FVec3(m_eye[0] / scale,m_eye[1] / scale, m_eye[2] / scale);
	FVec3 scaledCenter =FVec3(m_center[0] / scale,m_center[1] / scale, m_center[2] / scale);

	//cam.SetFocalPoint(temp[0] / scale, temp[1] / scale, temp[2] / scale);
	//temp = cam.GetPosition();
	//cam.SetPosition(temp[0] / scale, temp[1] / scale, temp[2] / scale);

	// translate to center
	//rotTransform.Identity();
	//rotTransform.Translate(COR.x / scale, COR.y / scale, COR.z / scale);

	// azimuth
	calculateNormal();
	//FMat4 rotation = FMat4 ();
	Quaternion azimuth = Quaternion();
	azimuth.CreateFromAxisAngle(m_up[0],m_up[1],m_up[2],360.0 * x * speedFactor/ m_imageSize[0]);
	//if(x!=0)
	///rotation.rotateAxisAngle(m_up,360.0 * x * speedFactor/ m_imageSize[0]);

	Quaternion elevation = Quaternion();
	elevation.CreateFromAxisAngle(m_normal[0],m_normal[1],m_normal[2],-360.0 * y * speedFactor / m_imageSize[1]);

	// elevation
	//FMat4 rotation1 = FMat4 ();
	//m_normal = m_view^m_up;
	//m_normal=m_normal.normalized();
	//rotation.rotateAxisAngle(m_normal,-360.0 * y * speedFactor / m_imageSize[1]);

	//rotation=rotation1*rotation;

	Quaternion rot = elevation*azimuth;

	FMat4 rotation = rot.transform();

	m_eye = scaledEye;
	m_center = scaledCenter;
	applyTransform(rotation);
	calculateNormal();
	m_eye =FVec3(m_eye[0] *scale,m_eye[1] *scale, m_eye[2] * scale);
	m_center =FVec3(m_center[0] * scale,m_center[1] * scale, m_center[2] * scale);

}

void Camera::applyTransform( FMat4& transform) {

	FVec3 posOld =m_eye;
	FVec3 fpOld =m_center;
	FVec3 vuOld =m_view;

	vuOld = vuOld +posOld;

	FVec3 posNew = transform.multAffineMatPoint(posOld);
	FVec3 fpNew = transform.multAffineMatPoint(fpOld);
	FVec3 vuNew = transform.multAffineMatPoint(vuOld);

	vuNew = vuNew - posNew;

	m_eye = posNew;
	m_center = fpNew;
	m_view = vuNew;
}

void Camera::calculateNormal()
{
	m_view = m_center-m_eye;
	m_normal = m_view^m_up;
	m_normal=m_normal.normalized();
}

void Camera::reset()
{
	m_eye = FVec3(0.5f, 0.04f, -0.3f);
	m_view = FVec3(0, 0, -1);
	m_normal = FVec3(1, 0, 0);
	m_up = FVec3(0, 1, 0);

}

void Camera::rotatePoint( double dx, double dy)
{
	// Calculate the vector from the current view to the point
	setCenter(0,0,0);
	calculateNormal();

	double rotate[16];
	double newUpX, newUpY, newUpZ;
	double newSceneX, newSceneY, newSceneZ;
	double newSceneX1, newSceneY1, newSceneZ1;

	// Allow limiting of rotation (see main)
	rotationEyeX += dx;
	rotationEyeY += dy;

	// Rotate about the Up/Down Plane
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glRotated(dy, m_normal[0], m_normal[1], m_normal[2]);
	glGetDoublev(GL_MODELVIEW_MATRIX, rotate);

	// We now need to calculate a new up direction
	newUpX = (rotate[0]*m_up[0] + rotate[1]*m_up[1] + rotate[2]*m_up[2] + rotate[3]);
	newUpY = (rotate[4]*m_up[0] + rotate[5]*m_up[1] + rotate[6]*m_up[2] + rotate[7]);
	newUpZ = (rotate[8]*m_up[0] + rotate[9]*m_up[1] + rotate[10]*m_up[2] + rotate[11]);

	m_up[0] = newUpX;
	m_up[1] = newUpY;
	m_up[2] = newUpZ;

	newSceneX = (rotate[0]*-m_view[0] + rotate[1]*-m_view[1] + rotate[2]*-m_view[2] + rotate[3]);
	newSceneY = (rotate[4]*-m_view[0] + rotate[5]*-m_view[1] + rotate[6]*-m_view[2] + rotate[7]);
	newSceneZ = (rotate[8]*-m_view[0] + rotate[9]*-m_view[1] + rotate[10]*-m_view[2] + rotate[11]);

	glLoadIdentity();
	glRotated(dx, m_up[0], m_up[1], m_up[2]);
	glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
	glPopMatrix();

	newSceneX1 = (rotate[0]*newSceneX + rotate[1]*newSceneY + rotate[2]*newSceneZ + rotate[3]);
	newSceneY1 = (rotate[4]*newSceneX + rotate[5]*newSceneY + rotate[6]*newSceneZ + rotate[7]);
	newSceneZ1 = (rotate[8]*newSceneX + rotate[9]*newSceneY + rotate[10]*newSceneZ + rotate[11]);

	m_eye[0] = newSceneX1;
	m_eye[1] = newSceneY1;
	m_eye[2] = newSceneZ1;

	// Make sure the vectors are up to date
	calculateNormal();
}

FMat4 Camera::projection( IVec2& viewSize, FVec2& sample)
{
	m_fovY = 55;
	// TODO: Introduce a new property for the projection type
	ProjectionType projectionType = ORTHOGRAPHIC;

	Float renderAspect = (static_cast<Float>(m_imageSize[0]) /
			static_cast<Float>(m_imageSize[1]));
	Float deviceAspect = (static_cast<Float>(viewSize[0]) /
			static_cast<Float>(viewSize[1]));

	Float verticalFov = macros::deg2rad(m_fovY * 0.5f);

	Float top = 0.0f;
	if(projectionType == PERSPECTIVE) {
		top = tan(verticalFov)*m_frustrum[0];
	} else if(projectionType == ORTHOGRAPHIC) {
		Float viewHeight = m_fovY;
		top = viewHeight * 0.5f;
	}

	if(renderAspect>deviceAspect)
	top *= renderAspect/deviceAspect;

	Float bottom = -top;
	Float left = bottom*deviceAspect;
	Float right = -left;

	Float nearWidth = right-left;
	Float nearHeight = top-bottom;

	Float dx = sample[0] * nearWidth / static_cast<Float>(viewSize[0]);
	Float dy = sample[1] * nearHeight / static_cast<Float>(viewSize[1]);
	right += dx;
	left += dx;
	top += dy;
	bottom += dy;

	FMat4 result;
	Float invRightMinusLeft = 1.0f/(right-left);
	Float invTopMinusBottom = 1.0f/(top-bottom);
	Float invFarMinusNear = 1.0f/(m_frustrum[1]-m_frustrum[0]);

	if(projectionType == PERSPECTIVE) {
		Float twoN = 2.0f*m_frustrum[0];
		result(0,0) = twoN*invRightMinusLeft;
		result(1,0) = 0;
		result(2,0) = 0;
		result(3,0) = 0;
		result(0,1) = 0;
		result(1,1) = twoN*invTopMinusBottom;
		result(2,1) = 0;
		result(3,1) = 0;
		result(0,2) = (right+left)*invRightMinusLeft;
		result(1,2) = (top+bottom)*invTopMinusBottom;
		result(2,2) = -(m_frustrum[1]+m_frustrum[0])*invFarMinusNear;
		result(3,2) = -1;
		result(0,3) = 0;
		result(1,3) = 0;
		result(2,3) = -m_frustrum[1]*twoN*invFarMinusNear;
		result(3,3) = 0;
	} else if(projectionType == ORTHOGRAPHIC) {
		result(0,0) = 2.0f*invRightMinusLeft;
		result(1,0) = 0;
		result(2,0) = 0;
		result(3,0) = 0;
		result(0,1) = 0;
		result(1,1) = 2.0f*invTopMinusBottom;
		result(2,1) = 0;
		result(3,1) = 0;
		result(0,2) = 0;
		result(1,2) = 0;
		result(2,2) = -2.0f*invFarMinusNear;
		result(3,2) = 0;
		result(0,3) = -(right+left)*invRightMinusLeft;
		result(1,3) = -(top+bottom)*invTopMinusBottom;
		result(2,3) = -(m_frustrum[1]+m_frustrum[0])*invFarMinusNear;
		result(3,3) = 1;
	}

	return result;
}

END_PV_NAMESPACE

