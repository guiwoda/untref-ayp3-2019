add_library(TPFinal clientes.h clientes.c)
add_executable(TPFinalMain main.c)
target_link_libraries(TPFinalMain TPFinal)
