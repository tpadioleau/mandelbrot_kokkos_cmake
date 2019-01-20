#include <cstdlib> // for atoi
#include <iostream>

#include "constants.hpp"
#include "kokkos_shared.hpp"
#include "mandelbrot.hpp"
#include "write_screen.hpp"
#include "write_ppm.hpp"

void compute_mandelbrot_set(int argc, char* argv[])
{
    int default_size = 8192;
    if (argc>1)
    {
        default_size = std::atoi(argv[1]);
    }

    std::cout << "Compute Mandelbrot set of size "
              << default_size << "x"
              << default_size << "\n";

    Constants constants(default_size);

    // prepare data array for Mandelbrot set computation
    DataArray     image     = DataArray("image", constants.WIDTH, constants.HEIGHT);
    DataArrayHost imageHost = Kokkos::create_mirror_view(image);

    /*
     * Actual computation
     */
    {
        MandelbrotFunctor functor(image, constants);
        using range2d_t = Kokkos::MDRangePolicy<Kokkos::Rank<2>,
                                                Kokkos::IndexType<int>>;
        range2d_t range({0, 0}, {constants.WIDTH, constants.HEIGHT});
        Kokkos::parallel_for(range, functor);
        Kokkos::fence();
    }

    std::cout << "end of mandelbrot loop reached ...\n";

    // copy back results from device to host
    Kokkos::deep_copy(imageHost, image);

    write_screen(imageHost, constants);

    // save color ppm file
    if (1)
    {
        std::string filename("mandelbrot.ppm");
        save_ppm(imageHost, filename, constants);
    }
} // compute_mandelbrot_set

//============================================================
//============================================================
int main(int argc, char* argv[])
{
    /*
     * Initialize kokkos (host + device)
     *
     * If CUDA is enabled, Kokkos will try to use the default GPU, i.e. GPU #0 if you
     * have multiple GPUs.
     */
    Kokkos::initialize(argc, argv);

    std::cout << "##########################\n";
    std::cout << "KOKKOS CONFIG             \n";
    std::cout << "##########################\n";
    Kokkos::print_configuration(std::cout);
    if (Kokkos::hwloc::available())
    {
        std::cout << "hwloc (NUMA[" << Kokkos::hwloc::get_available_numa_count()
                  << "] x CORE["    << Kokkos::hwloc::get_available_cores_per_numa()
                  << "] x HT["      << Kokkos::hwloc::get_available_threads_per_core()
                  << "])\n";
    }
    std::cout << "##########################" << std::endl;

    compute_mandelbrot_set(argc, argv);

    Kokkos::finalize();

    return EXIT_SUCCESS;
}
