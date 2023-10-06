#include "calc.hpp"

int main(){
    Point <coord_t> test(1, 20, 5);
    Point <coord_t> test2(0, 1, 5);

    cout << test << endl;

    // vector <Point> ok;

    // ok.push_back(test);

    // cout << ok[0] << endl;



    V_Line <coord_t> line(test, test2);

    cout << line << endl;

    Triangle <coord_t> treg{{1, 1, 2}, {0, 0, 0}, {1, 2, 0}};

    //cout << treg << endl;

    Plane <coord_t> pl{{1, 1, 5}, {3, 2, 3}, {4, 4, 4}};
    pl.calc_coeff();

    cout << pl << endl;

    
    // while (test.init_data()){
    //     cout << "Perfect cache result: ";
    //     test.lfu_cache();
    //     cout << "LFU cache result: ";
    //     test.perfect_cache();
    // }

    return 0;
}

