#include "write_screen.hpp"

#include "constants.hpp"
#include "kokkos_shared.hpp"

#include <iostream>

void write_screen(DataArrayHost imageHost,
		  const Constants& constants)
{
    // print aesthetically, dont read this part
    int xmax = 80;
    int ymax = 60;

    for(int y=0; y<ymax; ++y)
    {
        std::cout << '\n';
        for(int x=0; x<xmax; ++x)
        {
            int val = imageHost(y*constants.HEIGHT/ymax, x*constants.WIDTH/xmax);

            if (val==200)
            {
                std::cout << '&';
            }
            else if (val==42)
            {
                std::cout << 'X';
            }
            else if (val>64)
            {
                std::cout << '#';
            }
            else if (val>32)
            {
                std::cout << ':';
            }
            else if (val>8)
            {
                std::cout << '.';
            }
            else
            {
                std::cout << ' ';
            }
        }
    }

    std::cout << '\n';
} // write_screen
