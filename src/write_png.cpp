#include "write_png.hpp"

#include "constants.hpp"
#include "kokkos_shared.hpp"
#include "pngwriter.h"

void save_png(DataArrayHost imageHost,
              const std::string& filename,
              const Constants& constants)
{
    std::string filename_png (filename + ".png");
    pngwriter png(constants.WIDTH, constants.HEIGHT, 0, filename_png.c_str());

    double max_colors = static_cast<double>(constants.MAX_COLOR);
    for(unsigned int i=0; i<constants.WIDTH; ++i)
    {
        for(unsigned int j=0; j<constants.HEIGHT; ++j)
        {
            double r = 1.0-(imageHost(i, j) % 4 * 64)/max_colors;
            double g = 1.0-(imageHost(i, j) % 8 * 32)/max_colors;
            double b = 1.0-(imageHost(i, j) %16 * 16)/max_colors;
            png.plot(i, j, r, g, b);
        }
    }

    png.close();
} // save_png
