# Common code to reuse

project(Commons)

add_library(${PROJECT_NAME} STATIC Logger.cpp FileHandler.cpp. Clap.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt argh)
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
                         $<INSTALL_INTERFACE:include>)

add_library(commons::commons ALIAS ${PROJECT_NAME})
