cmake_minimum_required(VERSION 3.10)
project(prepare-ycbv)

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules/")

find_package(TBB REQUIRED)
message(STATUS "TBB_VERSION: ${TBB_VERSION_MAJOR}.${TBB_VERSION_MINOR}")
message(STATUS "TBB_INTERFACE_VERSION: ${TBB_INTERFACE_VERSION}")
message(STATUS "TBB_INCLUDE_DIRS: ${TBB_INCLUDE_DIRS}")
message(STATUS "TBB_LIBRARIES: ${TBB_LIBRARIES}")

add_executable(main_tbb prepare_ycbv_tbb.cpp)
target_link_libraries(main_tbb PRIVATE TBB::tbb)
# target_compile_features(main PUBLIC cxx_std_17)
add_executable(main prepare_ycbv.cpp)
target_link_libraries(main)
# target_compile_features(main PUBLIC cxx_std_17)
