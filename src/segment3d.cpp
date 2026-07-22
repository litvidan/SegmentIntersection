#include "segment3d.h"

Segment3D::Segment3D() : startVec(Vector3D()), endVec(Vector3D()) {}
Segment3D::Segment3D(const Vector3D &start, const Vector3D &end) : startVec(start), endVec(end) {}

const Vector3D &Segment3D::start() const
{
	return startVec;
}

const Vector3D &Segment3D::end() const
{
	return endVec;
}

void Segment3D::setStart(const Vector3D &start)
{
	startVec = start;
}

void Segment3D::setEnd(const Vector3D &end)
{
	endVec = end;
}

Vector3D Segment3D::direction() const
{
	return endVec - startVec;
}

double Segment3D::length() const
{
	return (endVec - startVec).length();
}