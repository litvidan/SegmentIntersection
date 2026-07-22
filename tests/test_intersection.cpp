#include <gtest/gtest.h>
#include "intersection.h"
#include <variant>

// Auxillary function. Checks if result is point
void expectPoint(const std::optional<IntersectionResult>& res,
                 double x, double y, double z)
{
    ASSERT_TRUE(res.has_value());
    ASSERT_TRUE(std::holds_alternative<Vector3D>(*res));
    const Vector3D& pt = std::get<Vector3D>(*res);
    EXPECT_NEAR(pt.x(), x, 1e-9);
    EXPECT_NEAR(pt.y(), y, 1e-9);
    EXPECT_NEAR(pt.z(), z, 1e-9);
}

// Checks if result is segment
void expectSegment(const std::optional<IntersectionResult>& res,
                   double x1, double y1, double z1,
                   double x2, double y2, double z2)
{
    ASSERT_TRUE(res.has_value());
    ASSERT_TRUE(std::holds_alternative<Segment3D>(*res));
    const Segment3D& seg = std::get<Segment3D>(*res);
    EXPECT_NEAR(seg.start().x(), x1, 1e-9);
    EXPECT_NEAR(seg.start().y(), y1, 1e-9);
    EXPECT_NEAR(seg.start().z(), z1, 1e-9);
    EXPECT_NEAR(seg.end().x(), x2, 1e-9);
    EXPECT_NEAR(seg.end().y(), y2, 1e-9);
    EXPECT_NEAR(seg.end().z(), z2, 1e-9);
}

// ================== Tests ==================

// 1
TEST(Intersection, SkewSegments_NoIntersection)
{
    Segment3D a(Vector3D(0,0,0), Vector3D(1,0,0));
    Segment3D b(Vector3D(0,1,1), Vector3D(1,1,1));
    EXPECT_FALSE(intersect(a, b).has_value());
}
// 2
TEST(Intersection, CrossAtSinglePoint)
{
    Segment3D a(Vector3D(0,0,0), Vector3D(2,2,0));
    Segment3D b(Vector3D(0,2,0), Vector3D(2,0,0));
    auto res = intersect(a, b);
    expectPoint(res, 1.0, 1.0, 0.0);
}
// 3 
TEST(Intersection, TouchAtEndpoint)
{
    Segment3D a(Vector3D(0,0,0), Vector3D(1,0,0));
    Segment3D b(Vector3D(1,0,0), Vector3D(1,1,0));
    auto res = intersect(a, b);
    expectPoint(res, 1.0, 0.0, 0.0);
}
// 4
TEST(Intersection, ColinearTouchAtOnePoint)
{
    Segment3D a(Vector3D(0,0,0), Vector3D(2,0,0));
    Segment3D b(Vector3D(2,0,0), Vector3D(4,0,0));
    auto res = intersect(a, b);
    expectPoint(res, 2.0, 0.0, 0.0);
}
// 5
TEST(Intersection, ColinearOverlappingPartial)
{
    Segment3D a(Vector3D(0,0,0), Vector3D(3,0,0));
    Segment3D b(Vector3D(1,0,0), Vector3D(4,0,0));
    auto res = intersect(a, b);
    expectSegment(res, 1,0,0, 3,0,0);
}
// 6
TEST(Intersection, ColinearOverlappingFull)
{
    Segment3D a(Vector3D(0,0,0), Vector3D(2,0,0));
    Segment3D b(Vector3D(0,0,0), Vector3D(2,0,0));
    auto res = intersect(a, b);
    expectSegment(res, 0,0,0, 2,0,0);
}
// 7
TEST(Intersection, ParallelButNotColinear_NoIntersection)
{
    Segment3D a(Vector3D(0,0,0), Vector3D(1,0,0));
    Segment3D b(Vector3D(0,1,0), Vector3D(1,1,0));
    EXPECT_FALSE(intersect(a, b).has_value());
}
// 8
TEST(Intersection, DegenerateFirstSegment_PointOnSecond)
{
    Segment3D a(Vector3D(0.5, 0.5, 0.5), Vector3D(0.5, 0.5, 0.5));
    Segment3D b(Vector3D(0,0,0), Vector3D(1,1,1));
    auto res = intersect(a, b);
    expectPoint(res, 0.5, 0.5, 0.5);
}
// 9
TEST(Intersection, DegenerateSecondSegment_PointOnFirst)
{
    Segment3D a(Vector3D(2, 2, 0), Vector3D(2, 2, 4));
    Segment3D b(Vector3D(2, 2, 2), Vector3D(2, 2, 2));
    auto res = intersect(a, b);
    expectPoint(res, 2, 2, 2);
}
// 10
TEST(Intersection, DegenerateFirstSegment_PointNotOnSecond)
{
    Segment3D a(Vector3D(0.5, 0.5, 0.5), Vector3D(0.5, 0.5, 0.5));
    Segment3D b(Vector3D(0,0,0), Vector3D(1,0,0));
    auto res = intersect(a, b);
    EXPECT_FALSE(res.has_value());
}
// 11
TEST(Intersection, BothSegmentsDegenerateToSamePoint)
{
    Segment3D a(Vector3D(7,7,7), Vector3D(7,7,7));
    Segment3D b(Vector3D(7,7,7), Vector3D(7,7,7));
    auto res = intersect(a, b);
    expectPoint(res, 7,7,7);
}
// 12
TEST(Intersection, BothSegmentsDegenerateDifferentPoints)
{
    Segment3D a(Vector3D(1,1,1), Vector3D(1,1,1));
    Segment3D b(Vector3D(2,2,2), Vector3D(2,2,2));
    auto res = intersect(a, b);
    EXPECT_FALSE(res.has_value());
}
// 13
TEST(Intersection, OverlapWithReversedDirection)
{
    Segment3D a(Vector3D(0,0,0), Vector3D(3,0,0));
    Segment3D b(Vector3D(4,0,0), Vector3D(2,0,0));
    auto res = intersect(a, b);
    expectSegment(res, 2,0,0, 3,0,0);
}