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

class Point{
    public:

        Point(int a, int b, int c): c1(a), c2(b), c3(c) {}

        int x() const {return c1;}
        int y() const {return c2;}
        int z() const {return c3;}

        Point operator + (const Point& other){
            return Point{c1 + other.c1, c2 + other.c2, c3 + other.c3};
        }

        Point operator = (const Point& other){
            c1 = other.c1;
            c2 = other.c2;
            c3 = other.c3;
            return *this;
        }

        Point operator - (const Point& other){
            return Point{c1 - other.c1, c2 - other.c2, c3 - other.c3};
        }

    private:
        int c1;
        int c2;
        int c3;
};

std::ostream& operator << (std::ostream& stream, const Point& point){
    stream << "(" << point.x() << ", " << point.y() << ", " << point.z() << ")";
    return stream;
}

class V_Line{                   // Вектор, ориентированная линия
    public:
        V_Line(Point A, Point B): P1(A), P2(B) {}

        Point first() const {return P1;}
        Point last()  const {return P2;}

        V_Line operator + (const V_Line& other){
            return V_Line(P1, P2 + other.P2 - other.P1);
        }

        V_Line operator - (const V_Line& other){
            return V_Line(P1, P2 - other.P2 + other.P1);
        }

        V_Line operator = (const V_Line& other){
            P1 = other.P1;
            P2 = other.P2;
            return *this;
        }

    private:
        Point P1;
        Point P2;
};

std::ostream& operator << (std::ostream& stream, const V_Line& line){
    stream << "[" << line.first() << " / " << line.last() << "]";
    return stream;
}

class Plane{
    public:
        Plane(Point A, Point B, Point C): P1(A), P2(B), P3(C) {}

        bool intersection(const V_Line& otrezok){
            if (not is_coeff_calced){
                calc_coeff();
                is_coeff_calced = true;
            }

            long long int first_d = otrezok.first().x() * CA + otrezok.first().y() * CB + otrezok.first().z() * CC - CD;
            long long int last_d  = otrezok.last() .x() * CA + otrezok.last() .y() * CB + otrezok.last() .z() * CC - CD;

            if (first_d == 0 || last_d == 0 || first_d > 0 && last_d < 0 || first_d < 0 && last_d > 0){
                return true;
            }

            return false;
        }

        int side_of_point(const Point& point){
            if (not is_coeff_calced){
                calc_coeff();
                is_coeff_calced = true;
            }

            long long int side = point.x() * CA + point.y() * CB + point.z() * CC - CD;
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
        Point P1;
        Point P2;
        Point P3;
        long long int CA;
        long long int CB;
        long long int CC;
        long long int CD;
        bool is_coeff_calced = false;
};

class Tetraedr{
    public:
        Tetraedr(Point A, Point B, Point C, Point D): P1(A), P2(B), P3(C), P4(D) {}

        bool Intersection(const Tetraedr& X, const Tetraedr& Y){
            return false;
        }

    private:
        Point P1;
        Point P2;
        Point P3;
        Point P4;
};


#endif