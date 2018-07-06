cmake_minimum_required (VERSION 3.11)
project(litter_bug)
set(CMAKE_CXX_STANDARD 11)
set(NO_GUI "-DNO_GUI")

set (CMAKE_CXX_FLAGS "${NO_GUI} ${CMAKE_CXX_FLAGS} -fexceptions -std=c++11 -Wall -O3 -march=native -mfpu=vfp -mfloat-abi=hard")

#opencv needs gtk2 and gtkglext and hdf5
find_package (OpenCV REQUIRED )
find_package (OpenCL REQUIRED)

add_executable(litter_bug_nogui Litter_detect.cpp edge_grouping.cpp scoring.cpp cl/kernels.cpp)
target_include_directories(litter_bug_nogui PUBLIC ${CMAKE_SOURCE_DIR}/QPULib/Lib)
target_link_libraries( litter_bug_nogui ${OpenCV_LIBS} ${OpenCL_LIBS})
