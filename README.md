# Segment Intersection

A C++ 20 library for robust detection of intersections between two 3D line segments.

## Requirements
- C++ 20 compatible compiler
- CMake 4.4.0 or newer (can work with earlier versions, didn't test)
- Git (For fetching GoogleTest during the first CMake build)

## Build & Run
### Build
#### Windows
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Debug
```

#### Linux/macOS:
```bash
mkdir build 
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

### Run demo
#### Windows
(inside build folder)
```bash
.\Debug\SegmentIntersection3D.exe
```
#### Linux/macOS
(inside build folder)
```bash
./SegmentIntersecion3D
```

### Run tests
#### Windows
(inside build folder)
```bash
ctest -C Debug --output-on-failure
```
#### Linux/macOS
(inside build folder)
```bash
ctest --output-on-failure
```

## API
```cpp
std::optional<IntersectionResult> intersect(const Segment3D& A, 
                                            const Segment3D& B,
                                            double eps = 1e-9);
```

- Returns `std::nullopt` if the segments do not intersect  
- Otherwise returns `IntersectionResult` which is a `std::variant`:
    - `Vector3D` - intersection is a single point 
    - `Segment3D`- overlapping segment

## Project Structure
- `include/` - public headers(`Vector3D`, `Segment3D`, `intersect` function)
- `src/` - implementation
- `tests/` - unit tests
- CMakeLists.txt - build configuration