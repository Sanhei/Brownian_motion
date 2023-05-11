#ifndef INTEGRATORS_RUNGE_KUTTA_HPP
#define INTEGRATORS_RUNGE_KUTTA_HPP

#include <array>
#include <math.h>
#include <random>

#include "integrator_base.hpp"

namespace integrators {

/**
 * This is used to for consisting with group member.
 * Since everyone is using Runge Kutta.
 */
class runge_kutta
 : public integrator_base
{
public:
        runge_kutta(double timestep)
                : timestep_(timestep),
                  normal_(0, 1) // Define a normal distribution with mean 0, variance 1

        {}

        void operator() (particle& p);
        template <typename rng_tupe>
        double randomForce(rng_type& rng);
        double randomeforce;
private:
        double timestep_;

        std::normal_distribution<double> normal_;
};

template <typename rng_type>
double runge_kutta::randomForce(rng_type& rng)
{
        double f = normal_(rng);
        return f;
}

void 




}
