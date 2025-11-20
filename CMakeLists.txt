cmake_minimum_required(VERSION 3.10)
project(ReciclaMundo)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)

file(GLOB_RECURSE SRC_FILES
    "src/*.cpp"
)

add_executable(ReciclaMundo ${SRC_FILES})

target_include_directories(ReciclaMundo PRIVATE include)

target_link_libraries(ReciclaMundo
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
