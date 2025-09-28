#include "Vector3D.h"
#include <math.h>

Vector3::Vector3(const Vector3& other)
{
	_x = other._x;
	_y = other._y;
	_z = other._z;
}

Vector3 Vector3::operator +(const Vector3& other) const {
	return Vector3(other._x + _x, other._y + _y, other._z + _z);
};

Vector3 Vector3::operator -(const Vector3& other) const {
	return Vector3(_x - other._x, _y - other._y, _z - other._z);
}; 

void Vector3::operator +=(const Vector3& other) {
	_x += other._x;
	_y += other._y;
	_z += other._z;
};

void Vector3::operator -=(const Vector3& other) {
	_x -= other._x;
	_y -= other._y;
	_z -= other._z;
};

Vector3 Vector3::operator *(float num) const {
	return Vector3(_x * num, _y * num, _z * num);
}

float Vector3::operator*(const Vector3& other) const
{
	return (_x * other._x + _y * other._y + _z * other._z);
}

Vector3 Vector3::cross(const Vector3& other) const
{
	return Vector3(_y * other._z - _z * other._y, _z * other._x - _x* other._z, _x * other._y - _y * other._x);
}

Vector3 Vector3::operator/(const Vector3& other) const
{
	return Vector3();
}

void Vector3::operator=(const Vector3& other)
{
	_x = other._x;
	_y = other._y;
	_z = other._z;
}



float Vector3::normalize() {
	float _mod = sqrt((_x * _x) + (_y * _y) + (_z * _z));
	_x = _x / _mod;
	_y = _y / _mod;
	_z = _z / _mod;
	return _mod;
}

float Vector3::getX() const
{
	return _x;
}
float Vector3::getY() const
{
	return _y;
}
float Vector3::getZ() const
{
	return _z;
}
;