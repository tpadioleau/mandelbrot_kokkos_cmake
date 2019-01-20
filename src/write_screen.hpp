#ifndef WRITE_SCREEN_HPP_
#define WRITE_SCREEN_HPP_

#include "constants.hpp"
#include "kokkos_shared.hpp"

void write_screen(DataArrayHost imageHost,
		  const Constants& constants);

#endif // WRITE_SCREEN_H_
