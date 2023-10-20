#ifndef c_point
#define c_point

#include <iostream>

template <typename point_t> class Plane;
template <typename point_t> class Triangle;

template <typename point_t>
class Point{
    friend class Plane<point_t>;
    friend class Triangle<point_t>;
    public:
        bool is_point_nan = false;

        Point(point_t a, point_t b, point_t c): c1(a), c2(b), c3(c) {}

        point_t x() const {return c1;}
        point_t y() const {return c2;}
        point_t z() const {return c3;}

        Point operator + (const Point<point_t>& other){
            return Point{c1 + other.c1, c2 + other.c2, c3 + other.c3};
        }

        // Point operator = (const Point<point_t>& other){
        //     c1 = other.c1;
        //     c2 = other.c2;
        //     c3 = other.c3;
        //     is_point_nan = other.is_point_nan;
        //     return *this;
        // }

        Point operator - (const Point<point_t>& other){
            return Point{c1 - other.c1, c2 - other.c2, c3 - other.c3};
        }

        bool operator == (const Point<point_t>& other){
            if (c1 == other.c1 && c2 == other.c2 && c3 == other.c3){
                return true;
            }
            return false;
        }

        // ~Point() = default;

        // Point(const Point& other) = default;

        // Point(Point&& other) = default;

        // Point& operator = (Point&& other) = default;



    private:
        point_t c1;
        point_t c2;
        point_t c3;
};

template <typename point_t>
std::ostream& operator << (std::ostream& stream, const Point<point_t>& point){
    stream << "(" << point.x() << ", " << point.y() << ", " << point.z() << ")";
    return stream;
}

#endif
