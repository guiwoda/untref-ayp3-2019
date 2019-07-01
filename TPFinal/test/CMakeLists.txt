include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(TPFinalTest tests.c test_utils.c)
add_dependencies(TPFinalTest TPFinalTest)
add_test(TPFinalTest TPFinalTest)
target_link_libraries(TPFinalTest TPFinal cmocka)
