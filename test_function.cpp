#include "calc.hpp"

int main(){
    Point test(1, 20, 5);

    cout << test << endl;
    
    // while (test.init_data()){
    //     cout << "Perfect cache result: ";
    //     test.lfu_cache();
    //     cout << "LFU cache result: ";
    //     test.perfect_cache();
    // }

    return 0;
}
