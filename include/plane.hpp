#ifndef c_plane
#define c_plane

#include <iostream>

template <typename point_t> class Triangle;
template <typename point_t> std::ostream& operator<<(std::ostream& stream, const Plane<point_t>& plane);

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
                dist1 = fabs(dist1);
                dist2 = fabs(dist2);
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
            if (CA == 0 && CB == 0 && CC == 0){
                throw "Is not plane!";
            }
            
            return;
        }

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

#endif