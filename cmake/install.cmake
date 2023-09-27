
# necessary includes
include(GNUInstallDirs)

# configure pkg-config script
configure_file(${PROJECT_SOURCE_DIR}/cmake/TinyGL.pc.in ${PROJECT_BINARY_DIR}/TinyGL.pc @ONLY) 

# install everything
install(TARGETS TinyGL DESTINATION ${CMAKE_INSTALL_LIBDIR}/TinyGL)
install(FILES ${TINYGL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/TinyGL/GL)
install(FILES ${PROJECT_BINARY_DIR}/TinyGL.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
