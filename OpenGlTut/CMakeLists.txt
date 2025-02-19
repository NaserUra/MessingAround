cmake_minimum_required(VERSION 3.0.0)
project(testOpGL VERSION 0.1.0)

add_executable(testOpGL Main.cc)

 target_link_libraries(testOpGL g GL GLEW SDL2 Xext X11 m glut Xi Xmu)
