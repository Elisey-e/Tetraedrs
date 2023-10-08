#include "calc.hpp"


int main(){
    Point <coord_t> test(-1, -1, -1);
    Point <coord_t> test2(5, 5, 5);

    cout << test << endl;

    // vector <Point> ok;

    // ok.push_back(test);

    // cout << ok[0] << endl;

    Triangle <coord_t> treg{{10, 10, 0}, {-10, 10, 0}, {0, -15, 0}};

    // V_Line lne{test, test2};

    //cout << treg << endl;

    // Plane <coord_t> pl{{1, 1, 1}, {56, 27, 1}, {1, 5, 1}};
    // pl.calc_coeff();

    // cout << pl.normal_distance(test) << endl;

    // cout << pl.intersect_with_line(lne) << endl;

    // cout << pl << endl;

    Triangle <coord_t> treg2{{0, 0, 1}, {1, 1, -1}, {-1, 1, -1}};

    cout << treg.is_intersection(treg2) << endl;

    return 0;
}

