#include <gtest/gtest.h>
#include "segment3d.h"

TEST(Segment3D, DefaultConstructorCreatesZeroSegment)
{
    Segment3D s;
    EXPECT_DOUBLE_EQ(s.start().x(), 0.0);
    EXPECT_DOUBLE_EQ(s.end().x(), 0.0);
    EXPECT_DOUBLE_EQ(s.start().y(), 0.0);
    EXPECT_DOUBLE_EQ(s.end().y(), 0.0);
    EXPECT_DOUBLE_EQ(s.start().z(), 0.0);
    EXPECT_DOUBLE_EQ(s.end().z(), 0.0);
}

TEST(Segment3D, ConstructedSegmentPreservesEndpoints)
{
    Vector3D start(1, 2, 3);
    Vector3D end(4, 6, 8);
    Segment3D s(start, end);
    EXPECT_DOUBLE_EQ(s.start().x(), 1);
    EXPECT_DOUBLE_EQ(s.start().y(), 2);
    EXPECT_DOUBLE_EQ(s.start().z(), 3);
    EXPECT_DOUBLE_EQ(s.end().x(), 4);
    EXPECT_DOUBLE_EQ(s.end().y(), 6);
    EXPECT_DOUBLE_EQ(s.end().z(), 8);
}

TEST(Segment3D, DirectionIsEndMinusStart)
{
    Segment3D s(Vector3D(1, 2, 3), Vector3D(4, 6, 8));
    Vector3D dir = s.direction();
    EXPECT_DOUBLE_EQ(dir.x(), 3);
    EXPECT_DOUBLE_EQ(dir.y(), 4);
    EXPECT_DOUBLE_EQ(dir.z(), 5);
}

TEST(Segment3D, LengthMatchesDistanceBetweenEndpoints)
{
    Segment3D s(Vector3D(0, 0, 0), Vector3D(3, 4, 0));
    EXPECT_DOUBLE_EQ(s.length(), 5.0);
}

TEST(Segment3D, ZeroLengthSegmentHasZeroDirection)
{
    Segment3D s(Vector3D(5, 5, 5), Vector3D(5, 5, 5));
    Vector3D dir = s.direction();
    EXPECT_DOUBLE_EQ(dir.x(), 0);
    EXPECT_DOUBLE_EQ(dir.y(), 0);
    EXPECT_DOUBLE_EQ(dir.z(), 0);
    EXPECT_DOUBLE_EQ(s.length(), 0.0);
}

TEST(Segment3D, SettersUpdateEndpoints)
{
    Segment3D s;
    s.setStart(Vector3D(1, 2, 3));
    s.setEnd(Vector3D(4, 5, 6));
    EXPECT_DOUBLE_EQ(s.start().x(), 1);
    EXPECT_DOUBLE_EQ(s.start().y(), 2);
    EXPECT_DOUBLE_EQ(s.start().z(), 3);
    EXPECT_DOUBLE_EQ(s.end().x(), 4);
    EXPECT_DOUBLE_EQ(s.end().y(), 5);
    EXPECT_DOUBLE_EQ(s.end().z(), 6);
}