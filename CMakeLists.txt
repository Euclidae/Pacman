cmake_minimum_required(VERSION 3.20)
project(PacmanGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

# SDL3
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

# SDL3_image
FetchContent_Declare(
    SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG main
)
FetchContent_MakeAvailable(SDL3_image)

# SDL3_ttf
FetchContent_Declare(
    SDL3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG main
)
FetchContent_MakeAvailable(SDL3_ttf)

# Gather all source files in the root directory
file(GLOB SOURCES
    *.cpp
)

add_executable(Pacman ${SOURCES})

target_include_directories(Pacman PRIVATE
    ${SDL3_SOURCE_DIR}/include
    ${SDL3_image_SOURCE_DIR}/include
    ${SDL3_ttf_SOURCE_DIR}/include
    .
)

target_link_libraries(Pacman
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)

# Copy assets to bin directory after build
add_custom_command(TARGET Pacman POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Pacman>/assets
)