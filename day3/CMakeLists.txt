project(BatteryJoltage)

add_executable("${PROJECT_NAME}" BatteryJoltage.cpp)
# add_executable("${PROJECT_NAME}_P2" PresentDatabaseP2.cpp)

target_link_libraries("${PROJECT_NAME}" argh fmt::fmt commons::commons)
# target_link_libraries("${PROJECT_NAME}_P2" argh fmt::fmt commons::commons)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wpedantic -Wextra)
