cmake_minimum_required(VERSION 3.5)
project(TinyGL DESCRIPTION "Software-rendered OpenGL" HOMEPAGE_URL "https://github.com/erysdren/TinyGL" LANGUAGES C VERSION 0.4.2)

option(TINYGL_BUILD_EXAMPLES "Build TinyGL Examples" ON)
set(TINYGL_BPP 16 CACHE STRING "Native rendering bits-per-pixel")
set_property(CACHE TINYGL_BPP PROPERTY STRINGS 8 15 16 24 32)

set(TINYGL_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/source/api.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/arrays.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/clear.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/clip.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/error.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/get.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/glu.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/image_util.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/init.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/light.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/list.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/matrix.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/memory.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/misc.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/msghandling.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/ostinygl.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/select.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/specbuf.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/texture.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/vertex.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/zbuffer.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/zdither.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/zline.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/zmath.c
	${CMAKE_CURRENT_SOURCE_DIR}/source/ztriangle.c
)

set(TINYGL_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/GL/gl.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/GL/glu.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/GL/ostinygl.h
)

add_library(tinygl STATIC ${TINYGL_SOURCES})
target_include_directories(tinygl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(tinygl PUBLIC TGL_FEATURE_RENDER_BITS=${TINYGL_BPP})

find_library(MATH m)
if(MATH)
	target_link_libraries(tinygl PUBLIC ${MATH})
endif()

if(TINYGL_BUILD_EXAMPLES)

	add_library(tinygl_ui_headless STATIC ${CMAKE_CURRENT_SOURCE_DIR}/examples/ui_headless.c)
	target_link_libraries(tinygl_ui_headless PUBLIC tinygl)

	foreach(example gears mech spin texobj bounce cube)
			add_executable(${example}_headless ${CMAKE_CURRENT_SOURCE_DIR}/examples/${example}.c)
			target_link_libraries(${example}_headless PUBLIC tinygl_ui_headless)
	endforeach()

endif()

find_package(SDL2)
if(TINYGL_BUILD_EXAMPLES AND SDL2_FOUND)

	add_library(tinygl_ui_sdl2 STATIC ${CMAKE_CURRENT_SOURCE_DIR}/examples/ui.c)
	target_link_libraries(tinygl_ui_sdl2 PUBLIC tinygl)
	target_link_libraries(tinygl_ui_sdl2 PUBLIC ${SDL2_LIBRARIES})
	target_include_directories(tinygl_ui_sdl2 PUBLIC ${SDL2_INCLUDE_DIRS})

	foreach(example gears mech spin texobj bounce cube)
			add_executable(${example}_sdl2 ${CMAKE_CURRENT_SOURCE_DIR}/examples/${example}.c)
			target_link_libraries(${example}_sdl2 PUBLIC tinygl_ui_sdl2)
			if(CMAKE_C_COMPILER_ID STREQUAL "TinyCC")
				target_compile_definitions(${example}_sdl2 PUBLIC SDL_DISABLE_IMMINTRIN_H)
			endif()
	endforeach()

endif()

include(GNUInstallDirs)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinygl.pc.in ${CMAKE_CURRENT_BINARY_DIR}/tinygl.pc @ONLY)
install(TARGETS tinygl DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${TINYGL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tinygl/GL)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/tinygl.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
