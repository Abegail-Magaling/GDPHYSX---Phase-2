#include "MyVector.h"
#include <iostream>

using namespace physics;

float MyVector::Magnitude() const
{
	float x_sqr = this->x * this->x;
	float y_sqr = this->y * this->y;
	float z_sqr = this->z * this->z;
	return sqrt(x_sqr + y_sqr + z_sqr);
}

float physics::MyVector::SquareMagnitude() const
{
	float x_sqr = this->x * this->x;
	float y_sqr = this->y * this->y;
	float z_sqr = this->z * this->z;
	return x_sqr + y_sqr + z_sqr;
}

MyVector MyVector::direction() const
{
	float mag = Magnitude();
	if (mag == 0) {
		return MyVector(0, 0, 0);
	}
	else {
		float x_dir = this->x / mag;
		float y_dir = this->y / mag;
		float z_dir = this->z / mag;
		return MyVector(x_dir, y_dir, z_dir);
		
	}	
}

MyVector MyVector::operator+(const MyVector v)
{
	return MyVector(this-> x + v.x, this->y + v.y, this->z + v.z);
}

MyVector MyVector::operator-(const MyVector v)
{
	return MyVector(this->x - v.x, this->y - v.y, this->z - v.z);
}

MyVector MyVector::operator*(const MyVector v)
{
	return MyVector(this->x * v.x, this->y * v.y, this->z * v.z);
}

MyVector MyVector::operator/(const MyVector v)
{
	return MyVector(this->x / v.x, this->y / v.y, this->z / v.z);
}

void MyVector::operator+= (const MyVector v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void MyVector::operator-= (const MyVector v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

MyVector physics::MyVector::ScalarMultiplication(const float toScale) const
{
	return MyVector(toScale * this->x, toScale * this->y, toScale *this->z);
}

void MyVector::operator*= (const MyVector v) {
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}

float MyVector::DotProd(const MyVector v) const
{
	float dotX = this->x * v.x;
	float dotY = this->y * v.y;
	float dotZ = this->z * v.z;
	return dotX + dotY + dotZ;
}

MyVector physics::MyVector::crossProd(const MyVector v) const
{
	float crossX = (this->y * v.z) - (this->z * v.y);
	float crossY = (this->z * v.x) - (this->x * v.z);
	float crossZ = (this->x * v.y) - (this->y * v.x);
	return MyVector(crossX, crossY, crossZ);
}
