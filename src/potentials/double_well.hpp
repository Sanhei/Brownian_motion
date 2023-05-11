#ifndef DOUBLE_WELL_HPP
#define DOUBLE_WELL_HPP

#include "../particle.hpp"

namespace potentials{

class DoubleWell
{
        public:
                DoubleWell(particle& p){}
                template <typename container_type>
                double operator() (container_type& p)
                {
                        p.f = -U_depth*4*(pow(p.r, 3.0)-p.r);
                        return p.f;
                }
        private:
                double U_depth = 3.;
};

}
#endif /* ! DOUBLE_WELL_HPP */
