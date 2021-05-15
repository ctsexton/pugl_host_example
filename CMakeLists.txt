cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(PuglTute)

add_library(pugl 
  "${CMAKE_SOURCE_DIR}/lib/pugl/src/implementation.c"
  "${CMAKE_SOURCE_DIR}/lib/pugl/src/x11.c"
  "${CMAKE_SOURCE_DIR}/lib/pugl/src/x11_stub.c"
  "${CMAKE_SOURCE_DIR}/lib/pugl/src/x11_cairo.c"
)

find_package(PkgConfig)
pkg_search_module(Cairo REQUIRED cairo>=1.12.16)
pkg_search_module(CairoMM REQUIRED cairomm-1.16)
pkg_search_module(X11 REQUIRED x11)
pkg_search_module(Xrandr REQUIRED xrandr)
pkg_search_module(Xext REQUIRED xext)
pkg_check_modules(SUIL REQUIRED suil-0)
pkg_check_modules(LV2 REQUIRED lv2)
pkg_check_modules(LILV REQUIRED lilv-0)

target_include_directories(pugl PUBLIC 
  "${CMAKE_SOURCE_DIR}/lib/pugl/include"
  "${CMAKE_SOURCE_DIR}/lib/pugl/bindings/cxx/include"
  ${Cairo_INCLUDE_DIRS}
  ${X11_INCLUDE_DIRS}
  ${Xrandr_INCLUDE_DIRS}
  ${Xext_INCLUDE_DIRS}
)
target_link_libraries(pugl
  ${Cairo_LIBRARIES}
  ${X11_LIBRARIES}
  ${Xrandr_LIBRARIES}
  ${Xext_LIBRARIES}
)

add_executable(PuglHost src/main.cpp)

target_include_directories(PuglHost PUBLIC 
  "${CMAKE_SOURCE_DIR}/lib/pugl/include/"
  "${CMAKE_SOURCE_DIR}/lib/pugl/bindings/cxx/include/"
  ${CairoMM_INCLUDE_DIRS}
  ${SUIL_INCLUDE_DIRS}
  ${LV2_INCLUDE_DIRS}
  ${LILV_INCLUDE_DIRS}
)
target_link_libraries(PuglHost 
  pugl 
  ${CairoMM_LIBRARIES}
  ${SUIL_LINK_LIBRARIES}
  ${LV2_LINK_LIBRARIES}
  ${LILV_LINK_LIBRARIES}
)
