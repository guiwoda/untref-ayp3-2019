add_library(TPFinal clientes.c lib/sqlite3.c common.c)
add_executable(TPFinalMain main.c)
target_link_libraries(TPFinalMain TPFinal)
