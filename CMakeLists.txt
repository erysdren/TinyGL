cmake_minimum_required(VERSION 3.10)
project(TinyGL DESCRIPTION "Software-rendered OpenGL" HOMEPAGE_URL "https://github.com/erysdren/TinyGL" LANGUAGES C VERSION 0.4.2)

option(TINYGL_BUILD_EXAMPLES "Build TinyGL Examples" ON)
set(TINYGL_BPP 16 CACHE STRING "Native rendering bits-per-pixel")
set_property(CACHE TINYGL_BPP PROPERTY STRINGS 8 15 16 24 32)

file(GLOB TINYGL_SOURCES "${PROJECT_SOURCE_DIR}/source/*.c")
file(GLOB TINYGL_HEADERS "${PROJECT_SOURCE_DIR}/source/*.h")

add_library(tinygl ${TINYGL_SOURCES})
target_include_directories(tinygl PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(tinygl PRIVATE TGL_FEATURE_RENDER_BITS=${TINYGL_BPP})
set_target_properties(tinygl PROPERTIES C_STANDARD_REQUIRED ON C_STANDARD 99)

if(NOT MSVC)
	find_library(libmath m)
	if(libmath)
		target_link_libraries(tinygl PRIVATE ${libmath})
	endif()
endif()

if(MSVC)
	target_compile_definitions(tinygl PRIVATE _CRT_SECURE_NO_WARNINGS)
	target_compile_options(tinygl PRIVATE /wd4244) # disable int truncation warnings
	target_compile_options(tinygl PRIVATE /wd4305) # disable float truncation warnings
endif()

set(TINYGL_EXAMPLES gears mech spin texobj bounce cube morph3d teapot)

if(TINYGL_BUILD_EXAMPLES)
	add_library(tinygl_ui_headless STATIC ${PROJECT_SOURCE_DIR}/examples/ui_headless.c)
	target_link_libraries(tinygl_ui_headless PUBLIC tinygl)
	foreach(example IN LISTS TINYGL_EXAMPLES)
		add_executable(${example}_headless ${PROJECT_SOURCE_DIR}/examples/${example}.c)
		target_link_libraries(${example}_headless PUBLIC tinygl_ui_headless)
		if(MSVC)
			target_compile_definitions(${example}_headless PRIVATE _CRT_SECURE_NO_WARNINGS)
			target_compile_options(${example}_headless PRIVATE /wd4244) # disable int truncation warnings
			target_compile_options(${example}_headless PRIVATE /wd4305) # disable float truncation warnings
		endif()
	endforeach()
endif()

find_package(SDL2)
if(TINYGL_BUILD_EXAMPLES AND SDL2_FOUND)
	add_library(tinygl_ui_sdl2 STATIC ${PROJECT_SOURCE_DIR}/examples/ui_sdl2.c)
	target_link_libraries(tinygl_ui_sdl2 PUBLIC tinygl)
	target_link_libraries(tinygl_ui_sdl2 PUBLIC ${SDL2_LIBRARIES})
	target_include_directories(tinygl_ui_sdl2 PUBLIC ${SDL2_INCLUDE_DIRS})
	foreach(example IN LISTS TINYGL_EXAMPLES)
		add_executable(${example}_sdl2 ${PROJECT_SOURCE_DIR}/examples/${example}.c)
		target_link_libraries(${example}_sdl2 PUBLIC tinygl_ui_sdl2)
		if(CMAKE_C_COMPILER_ID STREQUAL "TinyCC")
			target_compile_definitions(${example}_sdl2 PUBLIC SDL_DISABLE_IMMINTRIN_H)
		endif()
		if(MSVC)
			target_compile_definitions(${example}_sdl2 PRIVATE _CRT_SECURE_NO_WARNINGS)
			target_compile_options(${example}_sdl2 PRIVATE /wd4244) # disable int truncation warnings
			target_compile_options(${example}_sdl2 PRIVATE /wd4305) # disable float truncation warnings
		endif()
	endforeach()
endif()

find_package(SDL3)
if(TINYGL_BUILD_EXAMPLES AND SDL3_FOUND)
	add_library(tinygl_ui_sdl3 STATIC ${PROJECT_SOURCE_DIR}/examples/ui_sdl3.c)
	target_link_libraries(tinygl_ui_sdl3 PUBLIC tinygl)
	target_link_libraries(tinygl_ui_sdl3 PUBLIC ${SDL3_LIBRARIES})
	target_include_directories(tinygl_ui_sdl3 PUBLIC ${SDL3_INCLUDE_DIRS})
	foreach(example IN LISTS TINYGL_EXAMPLES)
		add_executable(${example}_sdl3 ${PROJECT_SOURCE_DIR}/examples/${example}.c)
		target_link_libraries(${example}_sdl3 PUBLIC tinygl_ui_sdl3)
		if(CMAKE_C_COMPILER_ID STREQUAL "TinyCC")
			target_compile_definitions(${example}_sdl3 PUBLIC SDL_DISABLE_IMMINTRIN_H)
		endif()
		if(MSVC)
			target_compile_definitions(${example}_sdl3 PRIVATE _CRT_SECURE_NO_WARNINGS)
			target_compile_options(${example}_sdl3 PRIVATE /wd4244) # disable int truncation warnings
			target_compile_options(${example}_sdl3 PRIVATE /wd4305) # disable float truncation warnings
		endif()
	endforeach()
endif()

include(GNUInstallDirs)
configure_file(${PROJECT_SOURCE_DIR}/cmake/tinygl.pc.in ${PROJECT_BINARY_DIR}/tinygl.pc @ONLY)
install(TARGETS tinygl DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${TINYGL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tinygl/GL)
install(FILES ${PROJECT_BINARY_DIR}/tinygl.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
