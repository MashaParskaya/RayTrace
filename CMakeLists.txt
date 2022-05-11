cmake_minimum_required(VERSION 2.8)

project(CString)

set(CString_src main.cpp box.cpp object.cpp sphere.cpp tetrahedron.cpp vecmath.cpp)
set(CString_hdr box.hpp figures.hpp object.hpp sphere.hpp tetrahedron.hpp vec3.hpp vecmath.hpp factory.hpp factoryBox.hpp factorySphere.hpp factoryTetra.hpp)

add_executable(${PROJECT_NAME} ${CString_src} ${CString_hdr})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 /std:c++14")
