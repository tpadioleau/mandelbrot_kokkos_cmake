add_executable(mandelbrot_kokkos
  main.cpp
  write_png.cpp
  write_ppm.cpp
  write_screen.cpp)

target_link_libraries(mandelbrot_kokkos kokkos PNGwriter)
