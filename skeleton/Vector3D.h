#pragma once
class Vector3D
{
public:
	Vector3D(float x = 0, float y = 0, float z = 0) : _x(x), _y(y), _z(z) {};
	Vector3D(const Vector3D & other);

	Vector3D operator+(const Vector3D& other) const;

	void operator +=(const Vector3D& other);
	void operator -=(const Vector3D& other);

	Vector3D operator *(float num) const;

	float operator *(const Vector3D& other) const; // producto escalar

	// producto vectorial
	Vector3D cross(const Vector3D& other) const;


	Vector3D operator /(float num) const;
	Vector3D operator /(const Vector3D& other) const;

	void operator =(const Vector3D& other);

	float normalize();

	float getX() const;
	float getY() const;
	float getZ() const;

protected:
	float _x;
	float _y;
	float _z;
};
