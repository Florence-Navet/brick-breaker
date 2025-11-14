cmake_minimum_required(VERSION 3.10)
project(sfml-test)


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Add executable from source files
add_executable(sfml-test 
    src/main.cpp
    src/ball.cpp
    src/paddle.cpp
    src/brick.cpp
    src/brickFactory.cpp
    src/gameManager.cpp
    src/music.cpp)


cmake_minimum_required(VERSION 3.10)


target_link_libraries(sfml-test
 sfml-graphics sfml-window sfml-system sfml-audio)