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
        Point last() const {return P2;}

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

class Tetraedr{
    public:
        
    private:

};


#endif