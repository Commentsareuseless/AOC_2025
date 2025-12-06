project(VaultLock)

add_executable("${PROJECT_NAME}" VaultLock.cpp)
add_executable("${PROJECT_NAME}_P2" VaultLockP2.cpp)

target_link_libraries("${PROJECT_NAME}" argh fmt::fmt commons::commons)
target_link_libraries("${PROJECT_NAME}_P2" argh fmt::fmt commons::commons)
