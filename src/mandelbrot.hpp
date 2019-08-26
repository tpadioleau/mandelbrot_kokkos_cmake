#ifndef MANDELBROT_HPP_
#define MANDELBROT_HPP_

#include "constants.hpp"
#include "kokkos_shared.hpp"

/**
 * Kokkos kernel functor to compute mandelbrot set.
 *
 * This functor is designed to work with a multi-dimensionnal
 * range policy.
 */
class MandelbrotFunctor
{
public:
    MandelbrotFunctor(DataArray image, Constants constants)
        : m_image(image)
        , m_xmin(constants.xmin)
        , m_ymin(constants.ymin)
        , m_dx(constants.dx)
        , m_dy(constants.dy)
        , m_WIDTH(constants.WIDTH)
        , m_HEIGHT(constants.HEIGHT)
        , m_MAX_COLOR(constants.MAX_COLOR)
        , m_MAX_ITERS(constants.MAX_ITERS)
    {
    }

    KOKKOS_INLINE_FUNCTION
    unsigned char mandelbrot(int Px, int Py) const noexcept
    {
        float x0=m_xmin+Px*m_dx;
        float y0=m_ymin+Py*m_dy;
        float x=0.0;
        float y=0.0;
        int i;
        for(i=0;x*x+y*y<4.0 && i<m_MAX_ITERS;i++)
        {
            float xtemp=x*x-y*y+x0;
            y=2*x*y+y0;
            x=xtemp;
        }
        return (float) m_MAX_COLOR*i/m_MAX_ITERS;
    }

    KOKKOS_INLINE_FUNCTION
    void operator()(const int i, const int j) const noexcept
    {
        m_image(i,j) = mandelbrot(i,j);
    }

    DataArray m_image;
    float m_xmin, m_ymin, m_dx, m_dy, m_WIDTH, m_HEIGHT, m_MAX_COLOR, m_MAX_ITERS;
}; // end class MandelBrotFunctor

#endif
