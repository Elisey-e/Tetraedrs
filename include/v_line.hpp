#ifndef c_v_line
#define c_v_line

#include <iostream>
#include <cmath>
#include <point.hpp>

template <typename point_t>
class V_Line{                   // Вектор, ориентированная линия
    friend class Plane<point_t>;
    friend class Triangle<point_t>;
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

        bool operator == (const V_Line<point_t>& other){
            if (P1 == other.P1 && P2 == other.P2){
                return true;
            }
            return false;
        }

        V_Line calc_len(){
            lenght=sqrt((P1.x() - P2.x()) * (P1.x() - P2.x()) +
                        (P1.y() - P2.y()) * (P1.y() - P2.y()) +
                        (P1.z() - P2.z()) * (P1.z() - P2.z()));
            is_lenght_calced = true;
            return *this;
        }

        point_t len(){
            return lenght;
        }

    private:
        Point<point_t> P1;
        Point<point_t> P2;
        point_t lenght;
        bool is_lenght_calced = false;
};

template <typename point_t>
std::ostream& operator << (std::ostream& stream, const V_Line<point_t>& line){
    stream << "[" << line.first() << " / " << line.last() << "]";
    return stream;
}

#endif