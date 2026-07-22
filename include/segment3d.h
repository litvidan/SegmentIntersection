#pragma once
#include "vector3d.h"

class Segment3D
{
public:
	Segment3D();
	Segment3D(const Vector3D &start, const Vector3D &end);

	const Vector3D &start() const;
	const Vector3D &end() const;
	void setStart(const Vector3D &start);
	void setEnd(const Vector3D &end);

	Vector3D direction() const;
	double length() const;

private:
	Vector3D startVec;
	Vector3D endVec;
};