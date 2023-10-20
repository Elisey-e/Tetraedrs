// Смотрим в папку с тестами, проходимся по ней и считаем результат. Сверяемся с теми-же файлами в папке с ответами.

#include "calc.hpp"
#include <vector>
#include <set>
#include <filesystem>
#include <fstream>
#include <list>

namespace fs = std::filesystem;

int main(){


    //std::filesystem::current_path(std::filesystem::temp_directory_path());
    // std::filesystem::create_directories("sandbox/a/b");
    // std::ofstream("sandbox/file1.txt");
    // std::filesystem::create_symlink("a", "sandbox/syma");

    // Iterate over the std::filesystem::directory_entry elements explicitly

    
    
    
    for (auto const& dir_entry : fs::recursive_directory_iterator("../tests/src/test_files")){
        std::cout << "Testing: " << dir_entry << "\t\t";
        std::cout << "\n\tAnswer: ";
        std::fstream test_data;
        test_data.open(dir_entry.path().string());
        if (!test_data.is_open()){
            std::cout << "failed to open " << dir_entry << '\n';
            return 0;
        }

        std::vector <coord_t> correct_answer;
        
        std::fstream fans_data;
        fans_data.open(dir_entry.path().string().replace(dir_entry.path().string().find("/test_files") + 1,
                       dir_entry.path().string().find("/test_files") - 2, "test_ans"));
        if (!fans_data.is_open()){
            std::cout << "failed to open answer to" << dir_entry << '\n';
            return 0;
        }

        int ans_N;
        fans_data >> ans_N;
        for (int i = 0; i < ans_N; i++){
            coord_t curr;
            fans_data >> curr;
            correct_answer.push_back(curr);
        }

        bool is_ans_corr = true;

        try{
            int N;
            std::vector <Triangle<coord_t>> data;
            test_data >> N;
            data.reserve(N);
            std::vector <coord_t> k;
            k.reserve(9);
            std::set <int> ans;

            for (int i = 0; i < N; i++){
                for (int j = 0; j < 9; j++){
                    test_data >> k[j];
                }

                Triangle<coord_t> tr_i{{k[0], k[1], k[2]}, {k[3], k[4], k[5]}, {k[6], k[7], k[8]}};
                data[i] = tr_i;
                for (int j = 0; j < i; j++){
                    if (data[j].is_intersection(data[i])){
                        ans.insert(i + 1);
                        ans.insert(j + 1);
                    }
                }
            }
            int iter_c = 0;
            for (int i : ans){
                if(iter_c == static_cast<int>(correct_answer.size()) || correct_answer[iter_c] != i){
                    is_ans_corr = false;
                }
                std::cout << i << " ";
                ++iter_c;
            }
        }
        catch(const char* error_message)
        {
            std::cout << error_message << std::endl;
            std::cout << "FATAL ERROR\n";
            continue;
        }

        std::cout << "\n\tExpected: ";

        for (auto i : correct_answer){
            cout << i << " ";
        }

        std::cout << "Result: ";
        if (not is_ans_corr){
            std::cout << "WA";
        }
        else{
            std::cout << "OK";
        }

        std::cout << endl;
    }


    return 0;
}

