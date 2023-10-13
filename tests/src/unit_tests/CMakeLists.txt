aux_source_directory(./src SRC_LIST)

add_executable(e2e_tests ${SRC_LIST})

target_link_libraries(e2e_tests
                      PRIVATE ${GTEST_LIBRARIES}
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                      PRIVATE m)

target_include_directories(e2e_tests
                           PRIVATE ${INCLUDE_DIR})

gtest_discover_tests(e2e_tests)
