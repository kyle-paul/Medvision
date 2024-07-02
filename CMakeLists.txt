cmake_minimum_required(VERSION 3.12.0)
project(Medvision VERSION 0.1.0)

add_subdirectory(dependencies/glfw EXCLUDE_FROM_ALL)
add_subdirectory(dependencies/glm EXCLUDE_FROM_ALL)

# Add the executable
add_executable(Medvision
    src/Application.cpp
    
)

target_include_directories(Medvision PRIVATE dependencies)
target_include_directories(Medvision PRIVATE src/vendor)

target_link_libraries(Medvision glfw)
target_link_libraries(Medvision glm)