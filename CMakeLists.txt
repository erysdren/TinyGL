
# project
cmake_minimum_required(VERSION 3.3)
project(TinyGL DESCRIPTION "Software-rendered OpenGL" HOMEPAGE_URL https://github.com/erysdren/TinyGL LANGUAGES C VERSION 0.4.2)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# options
option(TINYGL_BUILD_EXAMPLES "Build TinyGL Examples" ON)
option(TINYGL_BUILD_SHARED "Build TinyGL Shared Library" OFF)
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

# tinycc
if(CMAKE_C_COMPILER_ID STREQUAL "TinyCC")
	add_compile_definitions(-DSDL_DISABLE_IMMINTRIN_H=1)
endif()

# native rendering bpp
add_compile_definitions(-DTGL_FEATURE_RENDER_BITS=${TINYGL_BPP})

# find math library
find_library(MATH m)
if(MATH)
	link_libraries(${MATH})
endif()

# sources
file(GLOB TINYGL_SOURCES ${PROJECT_SOURCE_DIR}/source/*.c)

# headers
file(GLOB TINYGL_HEADERS ${PROJECT_SOURCE_DIR}/include/GL/*.h)

# library
if(TINYGL_BUILD_SHARED)
	add_library(TinyGL SHARED ${TINYGL_SOURCES})
else()
	add_library(TinyGL STATIC ${TINYGL_SOURCES})
endif()
target_include_directories(TinyGL PUBLIC ${PROJECT_SOURCE_DIR}/include)

# pkg-config
configure_file(${PROJECT_SOURCE_DIR}/cmake/TinyGL.pc.in ${PROJECT_BINARY_DIR}/TinyGL.pc @ONLY) 

# install
install(TARGETS TinyGL DESTINATION ${CMAKE_INSTALL_PREFIX}/TinyGL/lib)
install(FILES ${TINYGL_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/TinyGL/include/GL)
install(FILES ${PROJECT_BINARY_DIR}/TinyGL.pc DESTINATION lib/pkgconfig)

link_libraries(TinyGL)

# headless examples
if(TINYGL_BUILD_EXAMPLES AND NOT WATCOM)

	add_executable(gears_headless
		${PROJECT_SOURCE_DIR}/examples/gears.c
		${PROJECT_SOURCE_DIR}/examples/ui_headless.c
	)

	add_executable(mech_headless
		${PROJECT_SOURCE_DIR}/examples/mech.c
		${PROJECT_SOURCE_DIR}/examples/ui_headless.c
	)

	add_executable(spin_headless
		${PROJECT_SOURCE_DIR}/examples/spin.c
		${PROJECT_SOURCE_DIR}/examples/ui_headless.c
	)

	add_executable(texobj_headless
		${PROJECT_SOURCE_DIR}/examples/texobj.c
		${PROJECT_SOURCE_DIR}/examples/ui_headless.c
	)

	add_executable(bounce_headless
		${PROJECT_SOURCE_DIR}/examples/bounce.c
		${PROJECT_SOURCE_DIR}/examples/ui_headless.c
	)

	add_executable(cube_headless
		${PROJECT_SOURCE_DIR}/examples/cube.c
		${PROJECT_SOURCE_DIR}/examples/ui_headless.c
	)

endif()

# sdl2 examples
find_package(SDL2)
if(TINYGL_BUILD_EXAMPLES AND SDL2_FOUND)

	link_libraries(SDL2::SDL2)

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
