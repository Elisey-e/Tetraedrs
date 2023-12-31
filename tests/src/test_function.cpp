#include "calc.hpp"
#include <vector>
#include <set>


int main(){

    try{
        int N;
        std::vector <Triangle<coord_t>> data;
        cin >> N;
        data.reserve(N);
        std::vector <coord_t> k;
        k.reserve(9);
        std::set <int> ans;

        for (int i = 0; i < N; i++){
            for (int j = 0; j < 9; j++){
                cin >> k[j];
            }

            Triangle<coord_t> tr_i{{k[0], k[1], k[2]}, {k[3], k[4], k[5]}, {k[6], k[7], k[8]}};
            data[i] = tr_i;
            for (int j = 0; j < i; j++){
                if (data[j].is_intersection(data[i])){
                    ans.insert(i);
                    ans.insert(j);
                }
            }
        }

        for (int i : ans){
            cout << i << endl;
        }
        cout << endl;
    }
    catch(const char* error_message)
    {
        cout << error_message << std::endl;
        cout << "FATAL ERROR\n";
    }

    return 0;
}

