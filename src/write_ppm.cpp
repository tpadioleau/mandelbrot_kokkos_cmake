#include "write_ppm.hpp"

#include "constants.hpp"
#include "kokkos_shared.hpp"

#include <fstream>

void save_ppm(DataArrayHost imageHost,
	      const std::string& filename,
	      const Constants& constants)
{
    std::string filename_ppm (filename + ".ppm");
    std::fstream myfile (filename_ppm, std::fstream::out | std::fstream::trunc);

    myfile << "P6 " << constants.WIDTH << ' ' << constants.HEIGHT << " 255\n";
    for(unsigned int i=0; i<constants.WIDTH; ++i)
    {
        for(unsigned int j=0; j<constants.HEIGHT; ++j)
        {
            // create an arbitrary RBG code mapping values taken by imageHost
            myfile << static_cast<unsigned char>(imageHost(i, j) % 4 * 64)
                   << static_cast<unsigned char>(imageHost(i, j) % 8 * 32)
                   << static_cast<unsigned char>(imageHost(i, j) % 16 * 16);
        }
    }
} // save_ppm
