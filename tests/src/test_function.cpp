#include "calc.hpp"
#include <vector>


int main(){
    // Point <coord_t> test(-1, -1, -1);
    // Point <coord_t> test2(5, 5, 5);

    // cout << test << endl;

    // vector <Point> ok;

    // ok.push_back(test);

    // cout << ok[0] << endl;

    //Triangle <coord_t> treg{{10, 10, 0}, {-10, 10, 0}, {0, -15, 0}};

    // V_Line lne{test, test2};

    //cout << treg << endl;

    // Plane <coord_t> pl{{1, 1, 1}, {56, 27, 1}, {1, 5, 1}};
    // pl.calc_coeff();

    // cout << pl.normal_distance(test) << endl;

    // cout << pl.intersect_with_line(lne) << endl;

    // cout << pl << endl;

    // Triangle <coord_t> treg2{{0, 0, 1}, {1, 1, -1}, {-1, 1, -1}};

    // cout << treg.is_intersection(treg2) << endl;

    int N;
    std::vector <Triangle<coord_t>> data;
    cin >> N;
    data.reserve(N);
    std::vector <coord_t> k;
    k.reserve(9);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < 9; j++){
            cin >> k[j];
        }

        Triangle<coord_t> tr_i{{k[0], k[1], k[2]}, {k[3], k[4], k[5]}, {k[6], k[7], k[8]}};
        data[i] = tr_i;
    }

    for (int i = 0; i < N; i++){
        cout << data[i] << endl;
    }

    return 0;
}

