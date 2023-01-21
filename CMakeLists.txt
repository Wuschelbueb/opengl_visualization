cmake_minimum_required(VERSION 3.2)
project(opengl_visualization)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(libs/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(libs/assimp)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")

    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

add_subdirectory(libs/nativefiledialog-extended)

include_directories(include/
    include/imgui
    libs/assimp/include/
    libs/glad/include/
    libs/glfw/include/
    libs/glm/
    libs/stb/)

file(GLOB LIBS_SOURCES libs/glad/src/glad.c)
file(GLOB PROJECT_HEADERS include/*.hpp
    include/imgui/*.hpp   
)
file(GLOB PROJECT_SOURCES src/*.cpp
    src/imgui/*.cpp)
file(GLOB PROJECT_RESOURCES res/*.png)
file(GLOB PROJECT_SHADERS shaders/*.comp
    shaders/*.frag
    shaders/*.geom
    shaders/*.vert
)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
    Readme.md
    .gitattributes
    .gitignore
    .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Resources" FILES ${PROJECT_RESOURCES})
source_group("Libs" FILES ${LIBS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
    -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_SHADERS}
    ${PROJECT_CONFIGS}
    ${PROJECT_RESOURCES}
    ${LIBS_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    assimp
    glfw
    ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES}
    PRIVATE nfd
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_RESOURCES}
)
