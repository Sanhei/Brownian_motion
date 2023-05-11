#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <functional>
#include <vector>
#include <tuple>

/**
 * The particle class is a data structure that holds the state of the particle
 * (position and velocity vectors) as well as the force acting on it.
 */
class particle
{

public:
        particle(): r(0), v(0), f(0){}
        double r;
        double rp;
        double v;
        double f;
        double mass;
        static constexpr double gamma=3;
        
        
};

#endif
