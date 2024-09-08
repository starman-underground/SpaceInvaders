cmake_minimum_required(VERSION 3.15...3.30)
project(SpaceInvaders VERSION 1.0
		      DESCRIPTION "My First C++ Game"
		      LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared library" OFF)

include(FetchContent)
FetchContent_Declare(SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.x
	GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets
    ${PROJECT_BINARY_DIR}/bin/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/shaders
    ${PROJECT_BINARY_DIR}/bin/shaders
    COMMENT "Copying resources into binary directory"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

