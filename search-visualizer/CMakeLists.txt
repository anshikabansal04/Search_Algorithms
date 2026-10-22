cmake_minimum_required(VERSION 3.15)
project(search_visualizer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# --- raylib (fetched automatically; no manual install needed) ---------------
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)  # don't build raylib's own examples
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
  GIT_SHALLOW ON
)
FetchContent_MakeAvailable(raylib)

# --- our executable ---------------------------------------------------------
file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(visualizer ${SOURCES})
target_include_directories(visualizer PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(visualizer PRIVATE raylib)

if(MSVC)
  target_compile_options(visualizer PRIVATE /W4)
else()
  target_compile_options(visualizer PRIVATE -Wall -Wextra)
endif()
