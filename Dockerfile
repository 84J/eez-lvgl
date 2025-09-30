FROM debian:bullseye-slim

RUN dpkg --add-architecture armhf                                   \
    && dpkg --add-architecture arm64                                \
    && apt update                                                   \
    && apt install -y --no-install-recommends                       \
       bash-completion grc less vim-tiny git                        \
       build-essential gcc cmake bison flex m4                      \
       crossbuild-essential-armhf crossbuild-essential-arm64        \
       pkg-config meson ninja-build python3-venv                    \
       libgpiod-dev       libgpiod2         libevdev-dev            \
       libgpiod-dev:armhf libgpiod2:armhf   libevdev-dev:armhf      \
       libgpiod-dev:arm64 libgpiod2:arm64   libevdev-dev:arm64      \
       libdrm-dev         libsdl2-dev       libsdl2-image-dev       \
       libdrm-dev:armhf   libsdl2-dev:armhf libsdl2-image-dev:armhf \
       libdrm-dev:arm64   libsdl2-dev:arm64 libsdl2-image-dev:arm64 \
       libglfw3-dev       libglew-dev                               \
       libglfw3-dev:armhf libglew-dev:armhf                         \
       libglfw3-dev:arm64 libglew-dev:arm64                         \
    && apt clean                                                    \
    && rm -rf /var/lib/apt/lists/*

ENV CROSS_COMPILE=arm-linux-gnueabihf-
ENV PKG_CONFIG_LIBDIR=/usr/lib/arm-linux-gnueabihf/pkgconfig
ENV PKG_CONFIG_SYSROOT_DIR=/

USER root
WORKDIR /ez-lvgl
CMD ["/bin/bash"]
