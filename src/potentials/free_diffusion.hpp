#ifndef POTENTIAL_FREE_DIFFUTION_HPP
#define POTENTIAL_FREE_DIFFUTION_HPP

#include "../particle.hpp"


namespace potentials {

class FreeDiffusion
{
public:
        FreeDiffusion(particle& p) {}
        // k_BT is Boltzmann temperature
        template <typename container_type>
        double operator() (container_type& p)
        // r is the position
        {
                
                 double f = 0.;
                return f;
        }
}; //class

} // namespace potential
#endif /* ! POTENTIAL_FREE_DIFFUTION_HPP */
