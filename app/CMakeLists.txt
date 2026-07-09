cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(App_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/logic_power_management_board/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/adc_monitor/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/fdcan/Inc
)

set(App_App_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/logic_power_management_board/Src/logic_power_management_board.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/adc_monitor/Src/adc_monitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fdcan/Src/fdcan_driver.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${App_App_Dirs})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${App_Include_Dirs})
