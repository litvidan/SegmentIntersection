#include "intersection.h"
#include <algorithm>
#include <cmath>

namespace
{
std::optional<IntersectionResult> intersectSkewOrCrossing(
    const Vector3D &dirA, const Vector3D &dirB,
    const Vector3D &startA, const Vector3D &startB,
    double eps)
{
    const double dirA_len2 = dirA.dot(dirA);
    const double dirB_len2 = dirB.dot(dirB);
    const double dirA_dot_dirB = dirA.dot(dirB);
    const Vector3D w = startA - startB;
    const double dirA_dot_w = dirA.dot(w);
    const double dirB_dot_w = dirB.dot(w);

    const double determinant =
        dirA_len2 * dirB_len2 - dirA_dot_dirB * dirA_dot_dirB;

    // Lines are not parallel, determinant > eps
    if (determinant <= eps)
    {
        return std::nullopt;
    }

    // Parameters of the closest points on infinite lines
    const double paramOnA_unclamped =
        (dirA_dot_dirB * dirB_dot_w - dirB_len2 * dirA_dot_w) / determinant;
    const double paramOnB_unclamped =
        (dirA_len2 * dirB_dot_w - dirA_dot_dirB * dirA_dot_w) / determinant;

    // Clamp parameters to the segment [0, 1]
    const double clampedA = std::clamp(paramOnA_unclamped, 0.0, 1.0);
    const double clampedB = std::clamp(paramOnB_unclamped, 0.0, 1.0);

    const Vector3D pointOnA = startA + dirA * clampedA;
    const Vector3D pointOnB = startB + dirB * clampedB;

    if ((pointOnA - pointOnB).length() <= eps)
    {
		// Return the middle of intersection
        return IntersectionResult{
            Vector3D((pointOnA.x() + pointOnB.x()) * 0.5,
                     (pointOnA.y() + pointOnB.y()) * 0.5,
                     (pointOnA.z() + pointOnB.z()) * 0.5)};
    }

    return std::nullopt;
}

// Finds the overlap of two non-degenerate collinear segments.
std::optional<IntersectionResult> intersectColinear(
    const Vector3D &dirA, const Vector3D &startA,
    const Segment3D &B, double eps)
{
    const double dirA_len2 = dirA.dot(dirA);

    // Project a point onto the direction of segment A
    auto project = [&](const Vector3D &point) -> double {
        return dirA.dot(point - startA) / dirA_len2;
    };

    double projA_start = 0.0; // A.start
    double projA_end   = 1.0; // A.end
    double projB_start = project(B.start());
    double projB_end   = project(B.end());

    // Sort projections for each segment
    if (projA_start > projA_end)
        std::swap(projA_start, projA_end);
    if (projB_start > projB_end)
        std::swap(projB_start, projB_end);

    const double overlap_start = std::max(projA_start, projB_start);
    const double overlap_end   = std::min(projA_end, projB_end);

    if (overlap_start > overlap_end + eps)
    {
        return std::nullopt; // no overlap
    }

    if (overlap_end - overlap_start <= eps)
    {
        // Overlap is a point
        const double mid = (overlap_start + overlap_end) * 0.5;
        return IntersectionResult{startA + dirA * mid};
    }

    // Return the overlapping segment
    return IntersectionResult{
        Segment3D(startA + dirA * overlap_start,
                  startA + dirA * overlap_end)};
}

} // namespace

std::optional<IntersectionResult> intersect(const Segment3D &A,
                                            const Segment3D &B, double eps)
{
    Vector3D dirA = A.direction();
    Vector3D dirB = B.direction();
    const double lenA2 = dirA.dot(dirA);
    const double lenB2 = dirB.dot(dirB);

    // ----------------------- Both segments degenerate are points ------------------------
    if (lenA2 <= eps && lenB2 <= eps)
    {
        if ((A.start() - B.start()).length() <= eps)
            return IntersectionResult{A.start()};
        else
            return std::nullopt;
    }

    // ----------------------- A is a point, B is a proper segment ----------------------
    if (lenA2 <= eps)
    {
        const Vector3D pointA = A.start();
        const Vector3D w = pointA - B.start();

        // Check collinearity: point must lie on the line of B
        if (dirB.cross(w).length() > eps)
            return std::nullopt;

        // Check if the point projects inside the segment
        const double t = dirB.dot(w) / lenB2;
        if (t >= -eps && t <= 1.0 + eps)
            return IntersectionResult{pointA};
        else
            return std::nullopt;
    }

    // ---------------------- B is a point, A is a proper segment ---------------------------
    if (lenB2 <= eps)
    {
        const Vector3D pointB = B.start();
        const Vector3D w = pointB - A.start();

        if (dirA.cross(w).length() > eps)
            return std::nullopt;

        const double t = dirA.dot(w) / lenA2;
        if (t >= -eps && t <= 1.0 + eps)
            return IntersectionResult{pointB};
        else
            return std::nullopt;
    }

    // ---------------------- Both segments are not points ---------------------
    const Vector3D w = A.start() - B.start();

    // Check for parallel / collinear via cross product
    const double crossLength = dirA.cross(dirB).length();
    if (crossLength > eps)
    {
        // Lines are not parallel – look for possible intersection or touch
        return intersectSkewOrCrossing(dirA, dirB, A.start(), B.start(), eps);
    }

    // Lines are parallel. Check if they lie on the same line.
    if (dirA.cross(w).length() > eps)
    {
        return std::nullopt; // parallel but not on the same line
    }

    // Segments are collinear
    return intersectColinear(dirA, A.start(), B, eps);
}