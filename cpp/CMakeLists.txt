cmake_minimum_required(VERSION 3.23.0)
project(YahooFinanceCpp VERSION 0.1.0 LANGUAGES CXX)
set(Boost_NO_WARN_NEW_VERSIONS ON)

include(D:/src/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(CURL CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

add_subdirectory(libs)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Boost::program_options
    CURL::libcurl
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)