
# project
cmake_minimum_required (VERSION 3.3)
project(TinyGL LANGUAGES C)
set(CMAKE_BUILD_TYPE Release)

# compile options
add_compile_options(-pedantic -Wall -Wextra)

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	add_compile_options(-O3)
endif()

if(NOT WIN32)
	link_libraries(m)
endif()

# sources
file(GLOB TINYGL_SOURCES ${PROJECT_SOURCE_DIR}/source/*.c)

# library
add_library(TinyGL STATIC ${TINYGL_SOURCES})
target_include_directories(TinyGL PUBLIC ${PROJECT_SOURCE_DIR}/include)

# examples
option(TINYGL_BUILD_EXAMPLES "Build TinyGL Examples" ON)

if(TINYGL_BUILD_EXAMPLES)

	find_package(SDL2 REQUIRED)
	link_libraries(TinyGL SDL2::SDL2)

	add_executable(gears
		${PROJECT_SOURCE_DIR}/examples/gears.c
		${PROJECT_SOURCE_DIR}/examples/ui.c
	)

	add_executable(mech
		${PROJECT_SOURCE_DIR}/examples/mech.c
		${PROJECT_SOURCE_DIR}/examples/ui.c
	)

	add_executable(spin
		${PROJECT_SOURCE_DIR}/examples/spin.c
		${PROJECT_SOURCE_DIR}/examples/ui.c
	)

	add_executable(texobj
		${PROJECT_SOURCE_DIR}/examples/texobj.c
		${PROJECT_SOURCE_DIR}/examples/ui.c
	)

endif()
