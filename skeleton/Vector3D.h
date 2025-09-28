#pragma once
class Vector3
{
public:
	Vector3(float x = 0, float y = 0, float z = 0) : _x(x), _y(y), _z(z) {};
	Vector3(const Vector3 & other);

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;

	void operator +=(const Vector3& other);
	void operator -=(const Vector3& other);

	Vector3 operator *(float num) const;

	float operator *(const Vector3& other) const; // producto escalar

	// producto vectorial
	Vector3 cross(const Vector3& other) const;


	Vector3 operator /(float num) const;
	Vector3 operator /(const Vector3& other) const;

	void operator =(const Vector3& other);

	float normalize();

	float getX() const;
	float getY() const;
	float getZ() const;

protected:
	float _x;
	float _y;
	float _z;
};
