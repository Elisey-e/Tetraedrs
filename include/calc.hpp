#ifndef c_tetraedrs
#define c_tetraedrs

#include <iostream>

using std::cin, std::cout, std::endl;

using coord_t = double;

template <typename point_t> class Point;
template <typename point_t> class V_Line;
template <typename point_t> class Plane;
template <typename point_t> class Triangle;
template <typename point_t> std::ostream& operator<<(std::ostream& stream, const Plane<point_t>& plane);
template <typename point_t> std::ostream& operator<<(std::ostream& stream, const Triangle<point_t>& treg);

#include "point.hpp"
#include "v_line.hpp"
#include "plane.hpp"
#include "triangle.hpp"

#endif