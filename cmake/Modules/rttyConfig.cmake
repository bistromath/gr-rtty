INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_RTTY rtty)

FIND_PATH(
    RTTY_INCLUDE_DIRS
    NAMES rtty/api.h
    HINTS $ENV{RTTY_DIR}/include
        ${PC_RTTY_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    RTTY_LIBRARIES
    NAMES gnuradio-rtty
    HINTS $ENV{RTTY_DIR}/lib
        ${PC_RTTY_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(RTTY DEFAULT_MSG RTTY_LIBRARIES RTTY_INCLUDE_DIRS)
MARK_AS_ADVANCED(RTTY_LIBRARIES RTTY_INCLUDE_DIRS)

