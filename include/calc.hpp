#ifndef c_tetraedrs
#define c_tetraedrs

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <algorithm>
#include <cmath>

using std::cin, std::cout, std::endl, std::unordered_map, std::vector, std::list, std::set;

#define ONE_USED  1
#define ZERO_USED 0

using coord_t = double;

template <typename point_t> class Point;
template <typename point_t> class V_Line;
template <typename point_t> class Plane;
template <typename point_t> class Triangle;
template <typename point_t> std::ostream& operator<<(std::ostream& stream, const Plane<point_t>& plane);

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

template <typename point_t>
class V_Line{                   // Вектор, ориентированная линия
    friend class Plane<point_t>;
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

        void calc_len(){
            lenght=sqrt((P1.x() - P2.x()) * (P1.x() - P2.x()) +
                        (P1.y() - P2.y()) * (P1.y() - P2.y()) +
                        (P1.z() - P2.z()) * (P1.z() - P2.z()));
            is_lenght_calced = true;
            return;
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

template <typename point_t>
class Plane{
    friend class Triangle<point_t>;
    friend std::ostream& operator << <>(std::ostream&, const Plane&);
    public:
        Plane(Point<point_t> A, Point<point_t> B, Point<point_t> C): P1(A), P2(B), P3(C) {}

        // bool intersection(const V_Line<point_t>& otrezok){
        //     if (not is_coeff_calced){
        //         calc_coeff();
        //     }

        //     point_t first_d = otrezok.first().x() * CA + otrezok.first().y() * CB + otrezok.first().z() * CC - CD;
        //     point_t last_d  = otrezok.last() .x() * CA + otrezok.last() .y() * CB + otrezok.last() .z() * CC - CD;

        //     if (first_d == 0 || last_d == 0 || first_d > 0 && last_d < 0 || first_d < 0 && last_d > 0){
        //         return true;
        //     }

        //     return false;
        // }

        // int side_of_point(const Point<point_t>& point){
        //     if (not is_coeff_calced){
        //         calc_coeff();
        //     }

        //     point_t side = point.x() * CA + point.y() * CB + point.z() * CC - CD;
        //     if      (side > 0){
        //         return 1;           // Point is above the plane in right basis
        //     }
        //     else if (side < 0){
        //         return -1;          // Point is below the plane in right basis
        //     }
        //     else{
        //         return 0;           // Point is on the plane
        //     }
        // }

        point_t normal_distance(const Point<point_t>& point) const{
            if (not is_coeff_calced){
                throw "coefficients not calced!";       // Can be raised only if method used by user
            }
            return (CA * point.x() + CB * point.y() + CC * point.z() + CD) / abs_of_normal_vector;
        }

        Point <point_t> intersect_with_line(const V_Line<point_t>& line) const{
            point_t dist1 = normal_distance(line.P1);
            point_t dist2 = normal_distance(line.P2);

            if ((dist1 > 0 && dist2 > 0) || (dist1 < 0 && dist2 < 0)){
                Point <point_t> ans(0, 0, 0);
                ans.is_point_nan = true;
                return ans;
            }
            else{
                dist1 = abs(dist1);
                dist2 = abs(dist2);
                Point <point_t> ans((line.P1.c1 * dist2 + line.P2.c1 * dist1) / (dist1 + dist2),
                                    (line.P1.c2 * dist2 + line.P2.c2 * dist1) / (dist1 + dist2),
                                    (line.P1.c3 * dist2 + line.P2.c3 * dist1) / (dist1 + dist2));
                return ans;
            }
        }

        void calc_coeff(){
            CA =  (P2.y() - P1.y()) * (P3.z() - P1.z()) - (P3.y() - P1.y()) * (P2.z() - P1.z());
            CB = -(P2.x() - P1.x()) * (P3.z() - P1.z()) + (P3.x() - P1.x()) * (P2.z() - P1.z());
            CC =  (P2.x() - P1.x()) * (P3.y() - P1.y()) - (P3.x() - P1.x()) * (P2.y() - P1.y());
            CD = -(CA * P1.x() + CB * P1.y() + CC * P1.z());
            abs_of_normal_vector = std::sqrt(CA * CA + CB * CB + CC * CC);
            is_coeff_calced = true;
            
            return;
        }

        // int is_planes_equal(Plane<point_t> Pl){
        //     if ((not is_coeff_calced) || (not Pl.is_coeff_calced))
        //         return -1;
        //     else{
        //         if (CD > Pl.CD){
        //             if (CD % Pl.CD == 0){
        //                 point_t k = CD / Pl.CD;
        //                 if (Pl.CC * k == CC && Pl.CB * k == CB && Pl.CA * k == CA){
        //                     return 1;
        //                 }
        //             }
        //             return 0;
        //         }
        //         else if (){

        //         }
        //     }
        // }

    private:
        Point<point_t> P1;
        Point<point_t> P2;
        Point<point_t> P3;
        point_t CA;
        point_t CB;
        point_t CC;
        point_t CD;

        point_t abs_of_normal_vector;
        
        bool is_coeff_calced = false;
        bool print_point_form = false;
};

template <typename point_t>
std::ostream& operator << (std::ostream& stream, const Plane<point_t>& plane){
    if (not plane.is_coeff_calced && not plane.print_point_form){
        stream << "Undefined coefficients";
    }
    else if (plane.print_point_form){
        stream << "(" << plane.P1 << ", " << plane.P2 << ", " << plane.P3 << ")";
    }
    else{
        stream << std::round(plane.CA * 100) / 100 << "X + " << std::round(plane.CB * 100) / 100 << "Y + " << std::round(plane.CC * 100) / 100 << "Z + " << std::round(plane.CD * 100) / 100 << " = 0";
    }
    return stream;
}


template <typename point_t>
class Triangle{
    public:
        Triangle(Point<point_t> A, Point<point_t> B, Point<point_t> C): Pl{A, B, C}, L1{A, B}, L2{B, C}, L3{C, A} {
            Pl.calc_coeff();
            L1.calc_len();
            L2.calc_len();
            L3.calc_len();
            reduce_triangle_to_2d();
        }

        bool is_intersection(const Triangle<point_t>& treug){
            // Тут какое нибудь частное непересечение

            // Смотрим, насколько близки коэффициенты плоскостей; если меньше эпсилон, то проецируем треугольники на одну плоскость и далее проверяем почти также, как ниже, только для точек треугольников

            Point <point_t> inter = Pl.intersect_with_line(treug.L1);

            if (not inter.is_point_nan){
                if(is_point_in_triangle(inter)){
                    return true;
                }
            }

            inter = Pl.intersect_with_line(treug.L2);
            if (not inter.is_point_nan){
                if(is_point_in_triangle(inter)){
                    return true;
                }
            }

            inter = Pl.intersect_with_line(treug.L3);
            if (not inter.is_point_nan){
                if(is_point_in_triangle(inter)){
                    return true;
                }
            }

            inter = treug.Pl.intersect_with_line(L1);
            if (not inter.is_point_nan){
                return is_point_in_triangle(inter);
            }

            inter = treug.Pl.intersect_with_line(L2);
            if (not inter.is_point_nan){
                if(is_point_in_triangle(inter)){
                    return true;
                }
            }

            inter = treug.Pl.intersect_with_line(L3);
            if (not inter.is_point_nan){
                if(is_point_in_triangle(inter)){
                    return true;
                }
            }

            return false;
        }

    private:
        Plane<point_t> Pl;
        V_Line<point_t> L1;
        V_Line<point_t> L2;
        V_Line<point_t> L3;

        int num_of_2d_reduced_coord = 0;

        void reduce_triangle_to_2d(){
            if (Pl.CA >= Pl.CB && Pl.CA >= Pl.CC){
                num_of_2d_reduced_coord = 1;
            }
            if (Pl.CB >= Pl.CA && Pl.CB >= Pl.CC){
                num_of_2d_reduced_coord = 2;
            }
            if (Pl.CC >= Pl.CA && Pl.CC >= Pl.CB){
                num_of_2d_reduced_coord = 3;
            }
            return;
        }
        
        bool is_point_in_triangle(const Point<point_t>& point){
            if (not num_of_2d_reduced_coord){
                throw "triangle not reduced to 2d!";
            }
            point_t len1 = 0;
            point_t len2 = 0;
            point_t len3 = 0;
            switch (num_of_2d_reduced_coord)
            {
            case 1:
                len1 = (Pl.P1.c2 - point.c2) * (Pl.P2.c3 - Pl.P1.c3) - (Pl.P2.c2 - Pl.P1.c2) * (Pl.P1.c3 - point.c3);
                len2 = (Pl.P2.c2 - point.c2) * (Pl.P3.c3 - Pl.P2.c3) - (Pl.P3.c2 - Pl.P2.c2) * (Pl.P2.c3 - point.c3);
                len3 = (Pl.P3.c2 - point.c2) * (Pl.P1.c3 - Pl.P3.c3) - (Pl.P1.c2 - Pl.P3.c2) * (Pl.P3.c3 - point.c3);
                break;
            case 2:
                len1 = (Pl.P1.c1 - point.c1) * (Pl.P2.c3 - Pl.P1.c3) - (Pl.P2.c1 - Pl.P1.c1) * (Pl.P1.c3 - point.c3);
                len2 = (Pl.P2.c1 - point.c1) * (Pl.P3.c3 - Pl.P2.c3) - (Pl.P3.c1 - Pl.P2.c1) * (Pl.P2.c3 - point.c3);
                len3 = (Pl.P3.c1 - point.c1) * (Pl.P1.c3 - Pl.P3.c3) - (Pl.P1.c1 - Pl.P3.c1) * (Pl.P3.c3 - point.c3);
                break;
            case 3:
                len1 = (Pl.P1.c1 - point.c1) * (Pl.P2.c2 - Pl.P1.c2) - (Pl.P2.c1 - Pl.P1.c1) * (Pl.P1.c2 - point.c2);
                len2 = (Pl.P2.c1 - point.c1) * (Pl.P3.c2 - Pl.P2.c2) - (Pl.P3.c1 - Pl.P2.c1) * (Pl.P2.c2 - point.c2);
                len3 = (Pl.P3.c1 - point.c1) * (Pl.P1.c2 - Pl.P3.c2) - (Pl.P1.c1 - Pl.P3.c1) * (Pl.P3.c2 - point.c2);
                break;
            default:
                break;
            }
            cout << point << " ";
            cout << len1 << " " << len2 << " " << len3 << endl;
            if ((len1 > 0 && len2 > 0 && len3 > 0) || (len1 < 0 && len2 < 0 && len3 < 0)){
                return true;
            }
            return false;
        }
};

// template <typename point_t>
// std::ostream& operator << (std::ostream& stream, const Triangle<point_t>& treg){
//     stream << "(" << std::round(treg.Pl.P1 * 100) << ", " << std::round(treg.Pl.P2 * 100) << ", " << std::round(treg.Pl.P3 * 100) << ")";
//     return stream;
// }


#endif