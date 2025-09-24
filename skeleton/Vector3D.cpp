#include "Vector3D.h"
#include <math.h>

Vector3D::Vector3D(const Vector3D& other)
{
	_x = other._x;
	_y = other._y;
	_z = other._z;
}

Vector3D Vector3D::operator +(const Vector3D& other) const {
	return Vector3D(other._x + _x, other._y + _y, other._z + _z);
};

void Vector3D::operator +=(const Vector3D& other) {
	_x += other._x;
	_y += other._y;
	_z += other._z;
};

void Vector3D::operator -=(const Vector3D& other) {
	_x -= other._x;
	_y -= other._y;
	_z -= other._z;
};

Vector3D Vector3D::operator *(float num) const {
	return Vector3D(_x * num, _y * num, _z * num);
}

float Vector3D::operator*(const Vector3D& other) const
{
	return (_x * other._x + _y * other._y + _z * other._z);
}

Vector3D Vector3D::cross(const Vector3D& other) const
{
	return Vector3D(_y * other._z - _z * other._y, _z * other._x - _x* other._z, _x * other._y - _y * other._x);
}

Vector3D Vector3D::operator/(const Vector3D& other) const
{
	return Vector3D();
}

void Vector3D::operator=(const Vector3D& other)
{
	_x = other._x;
	_y = other._y;
	_z = other._z;
}



float Vector3D::normalize() {
	float _mod = sqrt((_x * _x) + (_y * _y) + (_z * _z));
	_x = _x / _mod;
	_y = _y / _mod;
	_z = _z / _mod;
	return _mod;
}

float Vector3D::getX() const
{
	return _x;
}
float Vector3D::getY() const
{
	return _y;
}
float Vector3D::getZ() const
{
	return _z;
}
;