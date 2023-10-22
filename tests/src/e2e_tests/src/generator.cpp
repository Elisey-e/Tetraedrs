// Смотрим в папку с тестами, проходимся по ней и считаем результат. Сверяемся с теми-же файлами в папке с ответами.

#include "calc.hpp"
#include <vector>
#include <set>
#include <filesystem>
#include <fstream>
#include <list>

namespace fs = std::filesystem;

int main(){

    std::ofstream gen_data;
    gen_data.open("../tests/src/test_files/long_test.dat");

    for (int i = 0; i < 12; ++i){
        for (int j = 0; j < 12; ++j){
            for(int k = 0; k < 12; ++k){
                gen_data << i * 3 + 0.5 + 2 * (rand() + 0.0) / RAND_MAX << " " 
                         << j * 3 + 0.5 + 2 * (rand() + 0.0) / RAND_MAX << " "
                         << k * 3 + 0.5 + 2 * (rand() + 0.0) / RAND_MAX << " "
                         << i * 3 + 0.5 + 2 * (rand() + 0.0) / RAND_MAX << " " 
                         << j * 3 + 0.5 + 2 * (rand() + 0.0) / RAND_MAX << " "
                         << k * 3 + 0.5 + 2 * (rand() + 0.0) / RAND_MAX << " "
                         << i * 3 + 0.5 + 2 * (rand() + 0.0) / RAND_MAX << " " 
                         << j * 3 + 0.5 + 2 * (rand() + 0.0) / RAND_MAX << " "
                         << k * 3 + 0.5 + 2 * (rand() + 0.0) / RAND_MAX << " " << endl;
            }
        }
    }

    gen_data.close();

    return 0;
}

