#ifndef c_tetraedrs
#define c_tetraedrs

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <algorithm>

using std::cin, std::cout, std::endl, std::unordered_map, std::vector, std::list, std::set;

#define ONE_USED  1
#define ZERO_USED 0

class Tetraedrs{
    public:

        int hash_f(int x){
            return x % 1000;
        }
        
    private:
        vector <int> data = {};
        int size_of_cache = 0;
        int el_count = 0;
};


#endif