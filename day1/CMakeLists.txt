project(VaultLock)

add_executable("${PROJECT_NAME}" VaultLock.cpp)

target_link_libraries("${PROJECT_NAME}" argh fmt::fmt commons::commons)
target_link_libraries("${PROJECT_NAME}2" argh fmt::fmt commons::commons)
