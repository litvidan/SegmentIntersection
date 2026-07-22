#include <gtest/gtest.h>
#include <cmath>
#include "vector3d.h"

TEST(Vector3D, DefaultConstructorCreatesZero)
{
    Vector3D v;
    EXPECT_DOUBLE_EQ(v.x(), 0.0);
    EXPECT_DOUBLE_EQ(v.y(), 0.0);
    EXPECT_DOUBLE_EQ(v.z(), 0.0);
}

TEST(Vector3D, ParameterizedConstructorSetsCoordinates)
{
    Vector3D v(1.0, -2.5, 3.14);
    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), -2.5);
    EXPECT_DOUBLE_EQ(v.z(), 3.14);
}

TEST(Vector3D, SettersModifyCoordinates)
{
    Vector3D v;
    v.setX(10.0);
    v.setY(20.0);
    v.setZ(30.0);
    EXPECT_DOUBLE_EQ(v.x(), 10.0);
    EXPECT_DOUBLE_EQ(v.y(), 20.0);
    EXPECT_DOUBLE_EQ(v.z(), 30.0);
}

TEST(Vector3D, AdditionOperator)
{
    Vector3D a(1, 2, 3);
    Vector3D b(4, 5, 6);
    Vector3D sum = a + b;
    EXPECT_DOUBLE_EQ(sum.x(), 5);
    EXPECT_DOUBLE_EQ(sum.y(), 7);
    EXPECT_DOUBLE_EQ(sum.z(), 9);
}

TEST(Vector3D, SubtractionOperator)
{
    Vector3D a(5, 7, 9);
    Vector3D b(4, 5, 6);
    Vector3D diff = a - b;
    EXPECT_DOUBLE_EQ(diff.x(), 1);
    EXPECT_DOUBLE_EQ(diff.y(), 2);
    EXPECT_DOUBLE_EQ(diff.z(), 3);
}

TEST(Vector3D, MultiplicationByScalar)
{
    Vector3D v(1, -2, 3);
    Vector3D scaled = v * 2.5;
    EXPECT_DOUBLE_EQ(scaled.x(), 2.5);
    EXPECT_DOUBLE_EQ(scaled.y(), -5.0);
    EXPECT_DOUBLE_EQ(scaled.z(), 7.5);
}

TEST(Vector3D, ScalarMultiplicationFromLeft)
{
    Vector3D v(1, -2, 3);
    Vector3D scaled = -1.0 * v;
    EXPECT_DOUBLE_EQ(scaled.x(), -1.0);
    EXPECT_DOUBLE_EQ(scaled.y(), 2.0);
    EXPECT_DOUBLE_EQ(scaled.z(), -3.0);
}

TEST(Vector3D, DotProduct)
{
    Vector3D a(1, 3, -5);
    Vector3D b(4, -2, -1);
    EXPECT_DOUBLE_EQ(a.dot(b), 3.0);
}

TEST(Vector3D, CrossProduct)
{
    Vector3D x(1, 0, 0);
    Vector3D y(0, 1, 0);
    Vector3D z = x.cross(y);
    EXPECT_DOUBLE_EQ(z.x(), 0);
    EXPECT_DOUBLE_EQ(z.y(), 0);
    EXPECT_DOUBLE_EQ(z.z(), 1);
}

TEST(Vector3D, LengthOfUnitVectorIsOne)
{
    Vector3D v(1, 0, 0);
    EXPECT_DOUBLE_EQ(v.length(), 1.0);
}

TEST(Vector3D, LengthOf345Triangle)
{
    Vector3D v(3, 4, 0);
    EXPECT_DOUBLE_EQ(v.length(), 5.0);
}

TEST(Vector3D, LengthSquared)
{
    Vector3D v(3, 4, 0);
    EXPECT_DOUBLE_EQ(v.lengthSquared(), 25.0);
}