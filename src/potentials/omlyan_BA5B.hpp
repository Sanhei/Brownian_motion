#ifndef INTEGRATORS_OMELYAN_BA5B_HPP
#define INTEGRATORS_OMELYAN_BA5B_HPP

#include <array>

#include "integrator_base.hpp"

#include <random>
namespace integrators {

/**
 *  * A 2nd order symplectic and time-reversible integrator with 5 stages
 *   * and subinterval length \lambda optimised for best accuracy.
 *    *
 *     * See BABAB scheme in Omelyan, Mryglod & Folk, Comput. Phys. Commun. 151, 272 (2003).
 *      */
class omelyan_BA5B
  : public integrator_base
{
public:
    omelyan_BA5B(double timestep)
      : timestep_(timestep)
    {}

    /**
     *      * perform one integration step for the particle given
     *           */
    void operator() (particle& p);
    template <typename rng_type>
    double randomForce(rng_type& rng);
private:
    /** integration time step */
    double timestep_;
    /** parameters: the first four subinterval lengths */
    static constexpr double theta_  = 0.08398315262876693;
    static constexpr double rho_    = 0.2539785108410595;
    static constexpr double lambda_ = 0.6822365335719091;
    static constexpr double mu_     = -0.03230286765269967;

    std::normal_distribution<double> normal_;
};

template <typename rng_type>
double omelyan_BA5B::randomForce(rng_type& rng)
{
        double f = normal_(rng);
        return f;
}

void omelyan_BA5B::operator() (particle& p)
{
        std::array<double, 11> subintervals = {{
                theta_ * timestep_
              , rho_ * timestep_
              , lambda_ * timestep_
              , mu_ * timestep_
              , (1 - 2 * (lambda_ + theta_)) * timestep_ / 2
              , (1 - 2 * (mu_ + rho_)) * timestep_
              , (1 - 2 * (lambda_ + theta_)) * timestep_ / 2
              , mu_ * timestep_
              , lambda_ * timestep_
              , rho_ * timestep_
              , theta_ * timestep_
            }};

        std::random_device get_seed;
        std::mt19937 rng(get_seed());

        auto sub = subintervals.begin();         // iterate forward over subintervals

            for (unsigned int k = 0; k < 5; ++k) {
                double dt0 = *sub++;
                double dt1 = *sub++;
                // stage 1: shift velocities
                p.v += p.f * dt0 / p.mass + randomForce(rng)*sqrt(dt0*p.gamma);// k_BT = 1
                // stage 2: shift positions
                p.r += p.v * dt1;
                update_force(p);            // update force after every position update
            }
}

} // namespace integrators

#endif /* ! INTEGRATORS_OMELYAN_BA5B_HPP*/






















}
