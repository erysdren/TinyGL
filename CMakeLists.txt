
# project
cmake_minimum_required (VERSION 3.3)
project(TinyGL LANGUAGES C)
set(CMAKE_BUILD_TYPE Release)

# options
option(TINYGL_BUILD_EXAMPLES "Build TinyGL Examples" ON)
option(TINYGL_BUILD_TESTS "Build TinyGL Tests" OFF)
option(TINYGL_FIXED_POINT "Use Fixed-Point Math" OFF)

# compile options
if(NOT WATCOM)
	add_compile_options(-pedantic -Wall -Wextra)
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		add_compile_options(-O3)
	endif()
	if(NOT WIN32 AND NOT DJGPP)
		link_libraries(m)
	endif()
else()
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		add_compile_options(-ox -d0 -za99)
	endif()
endif()

if(TINYGL_FIXED_POINT)
	add_compile_definitions(-DTGL_FIXED=1)
	message(WARNING "This doesn't do anything yet.")
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
