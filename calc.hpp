#ifndef c_tetraedrs
#define c_tetraedrs

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <algorithm>

using std::cin, std::cout, std::endl, std::unordered_map, std::vector, std::list, std::set;

#define ONE_USED  1
#define ZERO_USED 0

template <typename point_t>
class Point{
    public:

        Point(point_t a, point_t b, point_t c): c1(a), c2(b), c3(c) {}

        point_t x() const {return c1;}
        point_t y() const {return c2;}
        point_t z() const {return c3;}

        Point operator + (const Point<point_t>& other){
            return Point{c1 + other.c1, c2 + other.c2, c3 + other.c3};
        }

        Point operator = (const Point<point_t>& other){
            c1 = other.c1;
            c2 = other.c2;
            c3 = other.c3;
            return *this;
        }

        Point operator - (const Point<point_t>& other){
            return Point{c1 - other.c1, c2 - other.c2, c3 - other.c3};
        }

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

template <typename point_t>
class V_Line{                   // Вектор, ориентированная линия
    public:
        V_Line(Point<point_t> A, Point<point_t> B): P1(A), P2(B) {}

        Point<point_t> first() const {return P1;}
        Point<point_t> last()  const {return P2;}

        V_Line operator + (const V_Line<point_t>& other){
            return V_Line(P1, P2 + other.P2 - other.P1);
        }

        V_Line operator - (const V_Line<point_t>& other){
            return V_Line(P1, P2 - other.P2 + other.P1);
        }

        V_Line operator = (const V_Line<point_t>& other){
            P1 = other.P1;
            P2 = other.P2;
            return *this;
        }

    private:
        Point<point_t> P1;
        Point<point_t> P2;
};

template <typename point_t>
std::ostream& operator << (std::ostream& stream, const V_Line<point_t>& line){
    stream << "[" << line.first() << " / " << line.last() << "]";
    return stream;
}

template <typename point_t>
class Plane{
    public:
        Plane(Point<point_t> A, Point<point_t> B, Point<point_t> C): P1(A), P2(B), P3(C) {}

        bool intersection(const V_Line<point_t>& otrezok){
            if (not is_coeff_calced){
                calc_coeff();
                is_coeff_calced = true;
            }

            long long point_t first_d = otrezok.first().x() * CA + otrezok.first().y() * CB + otrezok.first().z() * CC - CD;
            long long point_t last_d  = otrezok.last() .x() * CA + otrezok.last() .y() * CB + otrezok.last() .z() * CC - CD;

            if (first_d == 0 || last_d == 0 || first_d > 0 && last_d < 0 || first_d < 0 && last_d > 0){
                return true;
            }

            return false;
        }

        int side_of_point(const Point<point_t>& point){
            if (not is_coeff_calced){
                calc_coeff();
                is_coeff_calced = true;
            }

            long long point_t side = point.x() * CA + point.y() * CB + point.z() * CC - CD;
            if      (side > 0){
                return 1;           // Point is above the plane in right basis
            }
            else if (side < 0){
                return -1;          // Point is below the plane in right basis
            }
            else{
                return 0;           // Point is on the plane
            }
        }

        void calc_coeff()
        {
            CA = (P2.y() - P2.x()) * P3.z() + (P2.x() - P2.z()) * P3.y() + (P2.z() - P2.y()) * P3.x();
            CB = (P3.y() - P3.x()) * P1.z() + (P3.x() - P3.z()) * P1.y() + (P3.z() - P3.y()) * P1.x();
            CC = (P1.y() - P1.x()) * P2.z() + (P1.x() - P1.z()) * P2.y() + (P1.z() - P1.y()) * P2.x();
            CD =  P1.x() * P2.y() * P3.z()
                - P1.x() * P2.z() * P3.y()
                - P1.y() * P2.x() * P3.z()
                + P1.y() * P2.z() * P3.x()
                + P1.z() * P2.x() * P3.y()
                - P1.z() * P2.y() * P3.x();
            return;
        }

    private:
        Point<point_t> P1;
        Point<point_t> P2;
        Point<point_t> P3;
        long long point_t CA;
        long long point_t CB;
        long long point_t CC;
        long long point_t CD;
        bool is_coeff_calced = false;
};

#endif