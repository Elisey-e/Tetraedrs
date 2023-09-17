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
        Point(int a, int b, int c){
            c1 = a;
            c2 = b;
            c3 = c;
        }

        int x() const {return c1;}
        int y() const {return c2;}
        int z() const {return c3;}

        Point operator + (const Point& other){
            return Point{c1 + other.c1, c2 + other.c2, c3 + other.c3};
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

class Tetraedr{
    public:
        
    private:

};


#endif