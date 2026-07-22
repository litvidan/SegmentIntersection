#pragma once

class Vector3D
{
public:
    Vector3D();
    Vector3D(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    Vector3D operator+(const Vector3D &other) const;
    Vector3D operator-(const Vector3D &other) const;
    Vector3D operator*(double scalar) const;

    double dot(const Vector3D &other) const;
    Vector3D cross(const Vector3D &other) const;

    double length() const;
    double lengthSquared() const;

private:
    double X;
    double Y;
    double Z;
};

Vector3D operator*(double scalar, const Vector3D &vec);
