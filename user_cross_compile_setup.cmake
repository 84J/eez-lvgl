set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER   arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(ENV{PKG_CONFIG_SYSROOT_DIR} "${CMAKE_SYSROOT}")
set(ENV{PKG_CONFIG_DIR}         "")
set(ENV{PKG_CONFIG_LIBDIR}      "${CMAKE_SYSROOT}/lib/arm-linux-gnueabihf/pkgconfig:${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf/pkgconfig:${CMAKE_SYSROOT}/usr/share/pkgconfig")

add_compile_options(
    -Os -flto=auto -fno-fat-lto-objects
    -ffunction-sections -fdata-sections -fno-pie
    -fomit-frame-pointer -fno-unwind-tables -fno-asynchronous-unwind-tables
)
add_link_options(-Wl,--gc-sections -Wl,-s)
