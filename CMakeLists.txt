
# project
cmake_minimum_required (VERSION 3.3)
project(TinyGL LANGUAGES C)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# options
option(TINYGL_BUILD_EXAMPLES "Build TinyGL Examples" ON)
option(TINYGL_BUILD_TESTS "Build TinyGL Tests" OFF)
option(TINYGL_FIXED_POINT "Use Fixed-Point Math" OFF)
set(TINYGL_BPP 16 CACHE STRING "Native rendering bits-per-pixel")
set_property(CACHE TINYGL_BPP PROPERTY STRINGS 8 15 16 24 32)

# compile options
if(NOT WATCOM)
	add_compile_options(-std=c99 -pedantic -Wall -Wextra)
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		add_compile_options(-O3)
	else()
		add_compile_options(-g3 -fsanitize=address,undefined)
		add_link_options(-fsanitize=address,undefined)
	endif()
else()
	add_compile_options(-za99)
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		add_compile_options(-ox -d0)
	else()
		add_compile_options(-d3)
	endif()
endif()

# fixed point
if(TINYGL_FIXED_POINT)
	add_compile_definitions(-DTGL_FIXED=1)
endif()

# native rendering bpp
if(TINYGL_BPP STREQUAL 8)
	add_compile_definitions(-DTGL_FEATURE_RENDER_BITS=8)
elseif(TINYGL_BPP STREQUAL 15)
	add_compile_definitions(-DTGL_FEATURE_RENDER_BITS=15)
elseif(TINYGL_BPP STREQUAL 16)
	add_compile_definitions(-DTGL_FEATURE_RENDER_BITS=16)
elseif(TINYGL_BPP STREQUAL 24)
	add_compile_definitions(-DTGL_FEATURE_RENDER_BITS=24)
elseif(TINYGL_BPP STREQUAL 32)
	add_compile_definitions(-DTGL_FEATURE_RENDER_BITS=32)
endif()

# find math library
find_library(MATH m)
if(MATH)
	link_libraries(${MATH})
endif()

# sources
file(GLOB TINYGL_SOURCES ${PROJECT_SOURCE_DIR}/source/*.c)

# library
add_library(TinyGL STATIC ${TINYGL_SOURCES})
target_include_directories(TinyGL PUBLIC ${PROJECT_SOURCE_DIR}/include)

# tests
if(TINYGL_BUILD_TESTS)

	link_libraries(TinyGL)

	add_executable(zclut_test
		${PROJECT_SOURCE_DIR}/tests/zclut_test.c
		${PROJECT_SOURCE_DIR}/tests/gears.c
	)

endif()

# examples
if(TINYGL_BUILD_EXAMPLES AND NOT DJGPP AND NOT WATCOM AND NOT RISCV)

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

	add_executable(bounce
		${PROJECT_SOURCE_DIR}/examples/bounce.c
		${PROJECT_SOURCE_DIR}/examples/ui.c
	)

	add_executable(cube
		${PROJECT_SOURCE_DIR}/examples/cube.c
		${PROJECT_SOURCE_DIR}/examples/ui.c
	)

endif()
