#ifndef INTEGRATOR_BASE_HPP
#define INTEGRATOR_BASE_HPP

#include "../particle.hpp"
#include "../force.hpp"
namespace integrators {

class integrator_base
{
public:
        /** constructor */
        integrator_base() {}
        /** register potential for the force update
         * Simply delegate the call to add_potential().
         *
         * Returning a reference to ourselves allows chaining of function calls,
         * e.g., integrator().add_potential().add_potential();
         **/
        integrator_base& add_potential(force::compute_type const& potential)
        {
                force_.add_potential(potential);
                return *this;
        }
        /* update fore */
        integrator_base const& update_force(particle& p) const
        {
                force_.update(p);
                return *this;
        }
        /* apply periodic boundaries to all particles */

protected:
        /** force class holding the update functions of the potential */
        force force_;

}; /* class */

} /* namespace */

#endif /* ! INTEGRATOR_BASE_HPP */
