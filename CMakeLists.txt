cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME Rasterizer)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Use C++ 11
set(CMAKE_CXX_STANDARD 17)

# Application sources
set(SOURCES ${SRC_DIR}/main.cpp)
set(HEADERS ${SRC_DIR}/settings.hpp)

set(RENDERER_SOURCES
	${SRC_DIR}/renderer/rasterizer.cpp
	${SRC_DIR}/renderer/model.cpp)

set(RENDERER_HEADERS
	${SRC_DIR}/renderer/rasterizer.hpp
	${SRC_DIR}/renderer/structures.hpp
	${SRC_DIR}/renderer/model.hpp)

# Add SFML
set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_deps/SFML)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/_deps/SFML)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Source groups to keep the source code nice and tidy
source_group("Application" FILES ${SOURCES} ${HEADERS})
source_group("Renderer" FILES ${RENDERER_SOURCES} ${RENDERER_HEADERS})

if(MSVC)
    # Warning level 4 and treat all warnings as errors
    add_compile_options(/W4 /WX)

    # Set the Visual Studio start-up project
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
else()
    # Lots of warnings and treat all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# Create the executable
add_executable(
    ${PROJECT_NAME}
    ${SOURCES} ${HEADERS}
	${RENDERER_SOURCES} ${RENDERER_HEADERS})

# Include all files for the project
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_DIR}/include)

# Link against SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics)