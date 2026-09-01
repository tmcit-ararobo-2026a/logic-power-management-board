cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(logic_power_management STATIC 
    src/app.cpp
    src/fdcan_driver.cpp
)

target_include_directories(logic_power_management PUBLIC
    include/
)

target_compile_features(logic_power_management PUBLIC cxx_std_17)

target_link_libraries(logic_power_management PRIVATE gn10_can)
target_link_libraries(logic_power_management PRIVATE stm32cubemx)
