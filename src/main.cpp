#include "intersection.h"
#include "segment3d.h"
#include <iostream>
#include <variant>

// Helper function to display the intersection result
void printResult(const std::optional<IntersectionResult> &result)
{
    if (!result)
    {
        std::cout << "No intersection.\n";
        return;
    }
    std::visit(
        [](const auto &res) {
            using T = std::decay_t<decltype(res)>;
            if constexpr (std::is_same_v<T, Vector3D>)
            {
                std::cout << "Intersection point: (" << res.x() << ", "
                          << res.y() << ", " << res.z() << ")\n";
            }
            else if constexpr (std::is_same_v<T, Segment3D>)
            {
                std::cout << "Overlapping segment: [(" << res.start().x()
                          << ", " << res.start().y() << ", " << res.start().z()
                          << ") - (" << res.end().x() << ", " << res.end().y()
                          << ", " << res.end().z() << ")]\n";
            }
        },
        *result);
}

int main()
{
    // 1. Crossing at a single point
    Segment3D s1(Vector3D(0, 0, 0), Vector3D(2, 2, 0));
    Segment3D s2(Vector3D(0, 2, 0), Vector3D(2, 0, 0));
    std::cout << "Test 1 (cross): ";
    printResult(intersect(s1, s2));

    // 2. Skew segments (no intersection)
    Segment3D s3(Vector3D(0, 0, 0), Vector3D(1, 0, 0));
    Segment3D s4(Vector3D(0, 1, 1), Vector3D(1, 1, 1));
    std::cout << "Test 2 (skew): ";
    printResult(intersect(s3, s4));

    // 3. Touching at an endpoint
    Segment3D s5(Vector3D(0, 0, 0), Vector3D(1, 0, 0));
    Segment3D s6(Vector3D(1, 0, 0), Vector3D(1, 1, 0));
    std::cout << "Test 3 (touch at endpoint): ";
    printResult(intersect(s5, s6));

    // 4. Colinear segments with overlap
    Segment3D s7(Vector3D(0, 0, 0), Vector3D(3, 0, 0));
    Segment3D s8(Vector3D(1, 0, 0), Vector3D(4, 0, 0));
    std::cout << "Test 4 (overlap colinear): ";
    printResult(intersect(s7, s8));

    // 5. First segment is a point that lies on the second segment
    Segment3D s9(Vector3D(0, 0, 0), Vector3D(0, 0, 0));
    Segment3D s10(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
    std::cout << "Test 5 (first point): ";
    printResult(intersect(s9, s10));

    return 0;
}