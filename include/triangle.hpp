#ifndef c_triangle
#define c_triangle

#include <iostream>

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
            }
            catch (...)
            {
                is_correct = false;
            }
        }

        bool is_intersection(const Triangle<point_t>& treug){
            // Тут какое нибудь частное непересечение
            if ((not treug.is_correct) || (not is_correct)){
                return false;
            }

            Point <point_t> inter = Pl.intersect_with_line(treug.L1);
            //cout << inter << inter.is_point_nan << endl;

            if (not inter.is_point_nan){
                //cout << "--------------------------\n";
                //cout << inter << endl;
                if(is_point_in_triangle(inter)){
                    return true;
                }
            }

            inter = Pl.intersect_with_line(treug.L2);
            //cout << inter << inter.is_point_nan << endl;
            if (not inter.is_point_nan){
                if(is_point_in_triangle(inter)){
                    return true;
                }
            }

            inter = Pl.intersect_with_line(treug.L3);
            //cout << inter << inter.is_point_nan << endl;
            if (not inter.is_point_nan){
                if(is_point_in_triangle(inter)){
                    return true;
                }
            }

            inter = treug.Pl.intersect_with_line(L1);
            //cout << inter << inter.is_point_nan << endl;
            if (not inter.is_point_nan){
                if(treug.is_point_in_triangle(inter)){
                    return true;
                }
            }

            inter = treug.Pl.intersect_with_line(L2);
            //cout << inter << inter.is_point_nan << endl;
            if (not inter.is_point_nan){
                if(treug.is_point_in_triangle(inter)){
                    return true;
                }
            }

            inter = treug.Pl.intersect_with_line(L3);
            //cout << inter << inter.is_point_nan << endl;
            if (not inter.is_point_nan){
                if(treug.is_point_in_triangle(inter)){
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

        bool is_correct = true;
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
            if ((len1 > 0 && len2 > 0 && len3 > 0) || (len1 < 0 && len2 < 0 && len3 < 0) || (len1 == 0) || (len2 == 0) || (len3 == 0)){
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