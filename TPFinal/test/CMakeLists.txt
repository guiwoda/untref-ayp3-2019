include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(TPFinalTest tests.c)
target_link_libraries(TPFinalTest cmocka TPFinal)

add_test(TPFinalTest TPFinalTest)