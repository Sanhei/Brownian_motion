#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include <vector>
#include <array>

namespace integrators{

/**
 * Base class for integrators that provides the mechanism
 * to register potentials
 */
class integrators_base
{
public:
        /** constructor */
        integrators_base()
        {}

        /** register potential for the force update
         *
         * Simply delegate the call to add_potential().
         *
         *
}
}
