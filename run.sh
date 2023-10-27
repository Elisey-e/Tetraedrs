#chmod +x ./myscript

#cmake -S .. -B release -DCMAKE_BUILD_TYPE=Release && cmake --build release
cmake ..
make
echo "------------------------------"

#../tmp/tests/src/unit_tests/unit_tests     # Running all unit tests for all modules.

#../tmp/tests/src/e2e_tests/e2e_tests       # Running end to end tests for all files in test_files directiry. Note: add correct answer in test_ans directory.

#../tmp/tests/src/e2e_tests/generator       # Generate long test in test_files directory. This test doesn't contain any intersections.

#../tmp/tests/test_function < ../tests/src/test_files/test2.dat     # Simple test of class function.

echo "------------------------------"
