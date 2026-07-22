#pragma once
#include "segment3d.h"
#include <optional>
#include <variant>

using IntersectionResult = std::variant<Vector3D, Segment3D>;

std::optional<IntersectionResult> intersect(const Segment3D &A, const Segment3D &B, double eps = 1e-9);