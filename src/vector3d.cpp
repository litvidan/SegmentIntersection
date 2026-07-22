#include "vector3d.h"
#include <cmath>

Vector3D::Vector3D() : X(0), Y(0), Z(0) {}
Vector3D::Vector3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

double Vector3D::x() const
{
	return X;
}
double Vector3D::y() const
{
	return Y;
}
double Vector3D::z() const
{
	return Z;
}
void Vector3D::setX(double x)
{
	X = x;
}
void Vector3D::setY(double y)
{
	Y = y;
}
void Vector3D::setZ(double z)
{
	Z = z;
}

Vector3D Vector3D::operator+(const Vector3D &other) const
{
	return Vector3D(X + other.X, Y + other.Y, Z + other.Z);
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
	return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
}

Vector3D Vector3D::operator*(double scalar) const
{
	return Vector3D(X * scalar, Y * scalar, Z * scalar);
}

double Vector3D::dot(const Vector3D &other) const
{
	return X * other.X + Y * other.Y + Z * other.Z;
}

Vector3D Vector3D::cross(const Vector3D &other) const
{
	return Vector3D(
        Y * other.Z - Z * other.Y, 
        Z * other.X - X * other.Z, 
        X * other.Y - Y * other.X
    );
}

double Vector3D::length() const
{
	return std::sqrt(lengthSquared());
}

double Vector3D::lengthSquared() const
{
	return X * X + Y * Y + Z * Z;
}

Vector3D operator*(double scalar, const Vector3D &vec)
{
	return vec * scalar;
}