#include "quaternion.h"

Quaternion::Quaternion() :
	x(0.0f), y(0.0f), z(0.0f), w(1.0f) {

}

Quaternion::Quaternion(FVec3& axis, float in_degrees) {

	float angle = float((in_degrees / 180.0f) * PI);
	float result = float(sin(angle / 2.0f));
	w = float(cos(angle / 2.0f));

	// Calculate the x, y and z of the quaternion
	x = float(axis[0] * result);
	y = float(axis[1] * result);
	z = float(axis[2] * result);

}


/*!
 * Multiplies the quaternion with another quaternion.
 * The Rotation of this quaternion will be done first.
 * \param q A reference to the lhs of the multiplication.
 */
void Quaternion::mult(const Quaternion &q) {
	double a = (w + x) * (q.getW() + q.getX());
	double b = (z - y) * (q.getY() - q.getZ());
	double c = (w - x) * (q.getY() + q.getZ());
	double d = (y + z) * (q.getW() - q.getX());
	double e = (x + z) * (q.getX() + q.getY());
	double f = (x - z) * (q.getX() - q.getY());
	double g = (w + y) * (q.getW() - q.getZ());
	double h = (w - y) * (q.getW() + q.getZ());

	x = a - (e + f + g + h) / 2.0;
	y = c + (e - f + g - h) / 2.0;
	z = d + (e - f - g + h) / 2.0;
	w = b + (-e -f + g + h) / 2.0;
}



/*!
 * Constructor that creates a quaternion from Euler angles.
 * \param roll The roll Euler angle.
 * \param pitch The pitch Euler angle.
 * \param yaw The yaw Euler angle.
 */
Quaternion::Quaternion(double roll, double pitch, double yaw) {

	double cr = cos(roll / 2.0);
	double cp = cos(pitch / 2.0);
	double cy = cos(yaw / 2.0);

	double sr = sin(roll / 2.0);
	double sp = sin(pitch / 2.0);
	double sy = sin(yaw / 2.0);

	double cpcy = cp * cy;
	double spsy = sp * sy;

	x = sr * cpcy - cr * spsy;
	y = cr * sp * cy + sr * cp * sy;
	z = cr * cp * sy - sr * sp * cy;
	w = cr * cpcy + sr * spsy;
}

/*!
 * Returns the x component of the quaternion.
 * \return A double with the x component.
 */
double Quaternion::getX() const {
	return x;
}



/*!
 * Returns the y component of the quaternion.
 * \return A double with the xycomponent.
 */
double Quaternion::getY() const {
	return y;
}



/*!
 * Returns the z component of the quaternion.
 * \return A double with the z component.
 */
double Quaternion::getZ() const {
	return z;
}

/*!
 * Returns the w component of the quaternion.
 * \return A double with the w component.
 */
double Quaternion::getW() const {
	return w;
}



Quaternion::~Quaternion() {

}

void Quaternion::CreateFromAxisAngle(const float &in_x, const float &in_y,
		const float &in_z, const float &in_degrees) {

	float angle = float((in_degrees / 180.0f) * PI);
	float result = float(sin(angle / 2.0f));
	w = float(cos(angle / 2.0f));

	// Calculate the x, y and z of the quaternion
	x = float(in_x * result);
	y = float(in_y * result);
	z = float(in_z * result);
}

FMat4& Quaternion::transform() {

	FMat4 pMatrix = FMat4();
	// First row
	pMatrix[0] = 1.0f - 2.0f * (y * y + z * z);
	pMatrix[1] = 2.0f * (x * y - w * z);
	pMatrix[2] = 2.0f * (x * z + w * y);
	pMatrix[3] = 0.0f;

	// Second row
	pMatrix[4] = 2.0f * (x * y + w * z);
	pMatrix[5] = 1.0f - 2.0f * (x * x + z * z);
	pMatrix[6] = 2.0f * (y * z - w * x);
	pMatrix[7] = 0.0f;

	// Third row
	pMatrix[8] = 2.0f * (x * z - w * y);
	pMatrix[9] = 2.0f * (y * z + w * x);
	pMatrix[10] = 1.0f - 2.0f * (x * x + y * y);
	pMatrix[11] = 0.0f;

	// Fourth row
	pMatrix[12] = 0;
	pMatrix[13] = 0;
	pMatrix[14] = 0;
	pMatrix[15] = 1.0f;
	return pMatrix;

}

void Quaternion::CreateMatrix(float *pMatrix) {
	if (pMatrix) {
		// First row
		pMatrix[0] = 1.0f - 2.0f * (y * y + z * z);
		pMatrix[1] = 2.0f * (x * y - w * z);
		pMatrix[2] = 2.0f * (x * z + w * y);
		pMatrix[3] = 0.0f;

		// Second row
		pMatrix[4] = 2.0f * (x * y + w * z);
		pMatrix[5] = 1.0f - 2.0f * (x * x + z * z);
		pMatrix[6] = 2.0f * (y * z - w * x);
		pMatrix[7] = 0.0f;

		// Third row
		pMatrix[8] = 2.0f * (x * z - w * y);
		pMatrix[9] = 2.0f * (y * z + w * x);
		pMatrix[10] = 1.0f - 2.0f * (x * x + y * y);
		pMatrix[11] = 0.0f;

		// Fourth row
		pMatrix[12] = 0;
		pMatrix[13] = 0;
		pMatrix[14] = 0;
		pMatrix[15] = 1.0f;
	}
}

Quaternion Quaternion::operator *(const Quaternion &q) {
	Quaternion r;

	r.w = w * q.w - x * q.x - y * q.y - z * q.z;
	r.x = w * q.x + x * q.w + y * q.z - z * q.y;
	r.y = w * q.y + y * q.w + z * q.x - x * q.z;
	r.z = w * q.z + z * q.w + x * q.y - y * q.x;

	return r;
}
