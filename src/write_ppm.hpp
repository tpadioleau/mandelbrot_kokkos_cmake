#ifndef WRITE_PPM_HPP_
#define WRITE_PPM_HPP_

#include <string>

#include "constants.hpp"
#include "kokkos_shared.hpp"

void save_ppm(DataArrayHost imageHost,
	      const std::string& filename,
	      const Constants& constants);

#endif // WRITE_PPM_H_
