cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 14)
project(DiscoPong
  VERSION 0.0.0
)
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/window/Window.cpp
  src/math/Vec2.cpp
  src/math/Vec3.cpp
  src/math/Vec4.cpp
  src/math/Mat4.cpp
  src/shader/Shader.cpp
  src/buffers/Buffer.cpp
  src/buffers/IndexBuffer.cpp
  src/buffers/VertexArray.cpp
  src/renderer/Renderable2d.cpp
  src/renderer/Simple2dRenderer.cpp
)
configure_file(src/DiscoPongConfig.h.in DiscoPongConfig.h)

# Resoruces
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

# Git pull submodules recursively
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad2)

target_include_directories(${PROJECT_NAME}
  PRIVATE lib/glfw/include
  PRIVATE lib/glad2/include
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_directories(${PROJECT_NAME}
  PRIVATE lib/glfw/src
  PRIVATE lib/glad2/src
)

target_link_libraries(${PROJECT_NAME}
  glfw
  glad2
)

if (APPLE)
  target_link_libraries(${PROJECT_NAME}
    "-framework OpenGL"
  )
  add_definitions( -DGL_SILENCE_DEPRECATION )
endif()

if (WIN32)
  target_link_libraries(${PROJECT_NAME}
    opengl32
  )
endif()
