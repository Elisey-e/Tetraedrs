#include "calc.hpp"

int main(){
    Point <int> test(1, 20, 5);
    Point <int> test2(0, 1, 5);

    cout << test << endl;

    // vector <Point> ok;

    // ok.push_back(test);

    // cout << ok[0] << endl;



    V_Line <int> line(test, test2);

    cout << line << endl;

    
    
    // while (test.init_data()){
    //     cout << "Perfect cache result: ";
    //     test.lfu_cache();
    //     cout << "LFU cache result: ";
    //     test.perfect_cache();
    // }

    return 0;
}

