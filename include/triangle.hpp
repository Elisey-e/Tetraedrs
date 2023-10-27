#ifndef c_triangle
#define c_triangle

#include <iostream>
#include <point.hpp>
#include <v_line.hpp>
#include <plane.hpp>

template <typename point_t> std::ostream& operator<<(std::ostream& stream, const Triangle<point_t>& treg);

template <typename point_t>
class Triangle{
    friend std::ostream& operator << <>(std::ostream&, const Triangle&);
    public:
        Triangle(Point<point_t> A, Point<point_t> B, Point<point_t> C): Pl{A, B, C}, L1{A, B}, L2{B, C}, L3{C, A} {
            try{
                Pl.calc_coeff();
                L1.calc_len();
                L2.calc_len();
                L3.calc_len();
                Pl.print_point_form = true;
                reduce_triangle_to_2d();
                //cout << Pl << endl;
            }
            catch (...)
            {
                is_correct = false;
            }
        }

        bool is_intersection(const Triangle<point_t>& treug){
            // Тут какое нибудь частное непересечение
            V_Line<point_t> quick_test{treug.Pl.P1, Pl.P1};
            if (quick_test.calc_len().lenght > maximum(L1.lenght, L3.lenght) + maximum(treug.L1.lenght, treug.L3.lenght)){
                return false;
            }

            if ((not treug.is_correct) || (not is_correct)){
                return false;
            }

            //cout << treug.Pl << "-------" << Pl << endl;

            Point <point_t> inter = Pl.intersect_with_line(treug.L1);
            if(is_line_intersect(inter, *this)){
                return true;
            }

            inter = Pl.intersect_with_line(treug.L2);
            if(is_line_intersect(inter, *this)){
                return true;
            }

            inter = Pl.intersect_with_line(treug.L3);
            if(is_line_intersect(inter, *this)){
                return true;
            }

            inter = treug.Pl.intersect_with_line(L1);
            if(is_line_intersect(inter, treug)){
                return true;
            }

            inter = treug.Pl.intersect_with_line(L2);
            if(is_line_intersect(inter, treug)){
                return true;
            }

            inter = treug.Pl.intersect_with_line(L3);
            if(is_line_intersect(inter, treug)){
                return true;
            }

            return false;
        }

    private:
        Plane<point_t> Pl;
        V_Line<point_t> L1;
        V_Line<point_t> L2;
        V_Line<point_t> L3;

        point_t maximum(point_t a, point_t b){
            if (a > b){
                return a;
            }
            return b;
        }

        bool is_line_intersect(const Point<point_t>& inter, const Triangle<point_t>& treug){
            //cout << inter << inter.is_point_nan << endl;
            if (not inter.is_point_nan){
                if(treug.is_point_in_triangle(inter)){
                    return true;
                }
            }
            else if(inter.is_point_inf){
                return false;           // Возможно стоит добавить рассмотрение этого частного случая
            }
            return false;
        }

        bool is_correct = true;
        int num_of_2d_reduced_coord = 0;

        void reduce_triangle_to_2d(){
            point_t kx = fabs(Pl.CA);
            point_t ky = fabs(Pl.CB);
            point_t kz = fabs(Pl.CC);
            if (kx >= ky && kx >= kz){
                num_of_2d_reduced_coord = 1;
            }
            if (ky >= kx && ky >= kz){
                num_of_2d_reduced_coord = 2;
            }
            if (kz >= kx && kz >= ky){
                num_of_2d_reduced_coord = 3;
            }
            return;
        }

        bool is_point_in_triangle(const Point<point_t>& point) const{
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
            //cout << len1 << " " << len2 << " " << len3 << endl;
            if ((len1 >= 0 && len2 >= 0 && len3 >= 0) || (len1 <= 0 && len2 <= 0 && len3 <= 0)){
                return true;
            }
            return false;
        }
};

template <typename point_t>
std::ostream& operator << (std::ostream& stream, const Triangle<point_t>& treg){
    stream << treg.Pl;
    return stream;
}

#endif