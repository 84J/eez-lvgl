FROM debian:bullseye-slim

RUN dpkg --add-architecture armhf                               \
    && dpkg --add-architecture arm64                            \
    && apt update                                               \
    && apt install -y --no-install-recommends                   \
       bash-completion grc less vim-tiny git                    \
       build-essential gcc cmake bison flex m4                  \
       crossbuild-essential-armhf crossbuild-essential-arm64    \
       pkg-config meson ninja-build python3-venv                \
       libgpiod-dev libgpiod2                                   \
       libgpiod-dev:armhf libgpiod2:armhf libevdev-dev:armhf    \
       libdrm-dev:armhf libsdl2-dev:armhf libsdl2-image-dev:armhf \
       libglfw3-dev:armhf libglew-dev:armhf \
    && apt clean                                                \
    && rm -rf /var/lib/apt/lists/*

ENV CROSS_COMPILE=arm-linux-gnueabihf-
ENV PKG_CONFIG_LIBDIR=/usr/lib/arm-linux-gnueabihf/pkgconfig
ENV PKG_CONFIG_SYSROOT_DIR=/

USER root
WORKDIR /ez-lvgl
CMD ["/bin/bash"]
