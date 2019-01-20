#
# mandelbrot_kokkos executable
#
add_executable(mandelbrot_kokkos
  main.cpp
  write_ppm.cpp
  write_screen.cpp)

# pass Kokkos include directories to our target application
target_include_directories(mandelbrot_kokkos PUBLIC ${Kokkos_INCLUDE_DIRS_RET})

target_link_libraries(mandelbrot_kokkos kokkos)
