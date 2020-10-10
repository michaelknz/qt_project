cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(qt_project LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui OpenGL PATHS ${CMAKE_SOURCE_DIR}/Qt/5.15.1/msvc2019_64/lib/cmake/Qt5)

set(project_source 
    src/main.cpp 
    src/main_window.cpp
    src/start_screen.cpp
    src/Opengl_Window.cpp
    src/Shader.cpp
    src/Mesh.cpp
    src/Matrix.cpp
    src/Camera.cpp
    src/Player.cpp)
    
set(project_header
    src/main_window.h
    src/start_screen.h
    src/Opengl_Window.h
    src/Shader.h
    src/Mesh.h
    src/Matrix.h
    src/Camera.h
    src/Player.h)

set (project_ui
    src/start_screen.ui)

qt5_wrap_ui(project_header_wrapped ${project_ui})
qt5_wrap_cpp(project_source_mac ${project_header})

include_directories(include)

add_executable(${PROJECT_NAME} ${project_header} ${project_source} 
    ${project_source_mac} ${project_header_wrapped})

file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/basic.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug )
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/basic.fs DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug )
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/basic.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/basic.fs DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/sheet.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )


target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::OpenGL
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libxl.lib)