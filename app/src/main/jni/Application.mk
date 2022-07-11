APP_ABI := armeabi-v7a
APP_OPTIM := debug
APP_PLATFORM := android-28
APP_CFLAGS := -O2 -std=gnu99 -Wall
APP_CPPFLAGS += -std=c++17 -Wno-invalid-offsetof -Wno-pmf-conversions

APP_STL := c++_static

NDK_TOOLCHAIN_VERSION=clang

