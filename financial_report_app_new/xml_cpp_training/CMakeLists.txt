cmake_minimum_required(VERSION 3.10)
project(XmlCppTraining)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/googletest)

add_library(tinyxml2
    external/tinyxml2-master/tinyxml2.cpp
    external/tinyxml2-master/tinyxml2.h
)

add_library(xml_training_lib
    xml_training_lib.cpp
    xml_training_lib.h
)

target_link_libraries(xml_training_lib PRIVATE tinyxml2)

add_executable(test_xml tests/test_xml.cpp)

target_link_libraries(test_xml PRIVATE gtest_main xml_training_lib)

enable_testing()
add_test(NAME test_xml COMMAND test_xml)
