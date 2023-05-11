#ifndef FORCE_HPP
#define FORCE_HPP

#include <functional>
#include <vector>

#include "particle.hpp"
#include "friction_kernel.cpp"
#include <random>
/**
 * The force class is a container that holds functions to update the forces on
 * the particles.
 */

class force
{
        /**
         * Force is only depend on the Potential and friction and random force
         * LE equation is
         *
         * m ̈q(t) = −U′(q) − γ(q)  ̇q(t) + √kBTγ(q) * η(t)
         * */
public:
        typedef std::function<void (particle&)> compute_type;

        double timestep_;
        static constexpr double k_BT = 1.;

        void update(particle& particle_) const
        {
                potential_(particle_);
        }// update()

        force& add_potential(compute_type const& potential)
        {
                potential_ = potential;
                return *this;
        }
private:
        compute_type potential_;

};// force
#endif /* ! FORCE_HPP */
