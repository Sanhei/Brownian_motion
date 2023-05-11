/*
 * Copyright © 2017 Felix Höfling
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INTEGRATORS_EULER_HPP
#define INTEGRATORS_EULER_HPP

#include <array>

#include "integrator_base.hpp"
#include <random>
namespace integrators {

class euler
  : public integrator_base
{
public:
    euler(double timestep)
      : timestep_(timestep),
        normal_(0, 1)
    {}

    /**
     * perform one integration step for the particle given
     */
    void operator() (particle& particles);
    
    template <typename rng_type>
    double randomForce(rng_type& rng);
    double randomforce;

private:
    /** integration time step */
    double timestep_;
    std::normal_distribution<double> normal_;
};

template <typename rng_type>
double euler::randomForce(rng_type& rng)
{
        double f = normal_(rng);
        return f;
}




void euler::operator() (particle& p)
{
    std::array<double, 1> dt = {{ timestep_ }};
    std::random_device get_seed;
    std::mt19937 rng(get_seed());
    randomforce = randomForce(rng);
    p.r += p.v * dt[0];
    double delta_v = randomforce*dt[0]/p.mass;
                // delta_v = dt0/abs(dt0)*randomForce(rng);
    p.v += p.f * dt[0] / p.mass + delta_v;
    update_force(p);
}

} // namespace integrators

#endif /* ! INTEGRATORS_EULER_HPP */
