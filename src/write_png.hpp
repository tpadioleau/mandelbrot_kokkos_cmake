#ifndef WRITE_PNG_HPP_
#define WRITE_PNG_HPP_

#include <string>

#include "constants.hpp"
#include "kokkos_shared.hpp"

void save_png(DataArrayHost imageHost,
              const std::string& filename,
              const Constants& constants);

#endif // WRITE_PNG_HPP_
