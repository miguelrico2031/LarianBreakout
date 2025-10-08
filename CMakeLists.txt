cmake_minimum_required(VERSION 3.28)

project(LarianBreakout LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SRC_CORE_FILES src/Core/*.cpp)
file(GLOB_RECURSE SRC_GAME_FILES src/Game/*.cpp)

add_executable(LarianBreakout ${SRC_CORE_FILES} ${SRC_GAME_FILES})

target_include_directories(LarianBreakout PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(LarianBreakout PRIVATE SFML::Graphics)


add_custom_command(
    TARGET LarianBreakout POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)
