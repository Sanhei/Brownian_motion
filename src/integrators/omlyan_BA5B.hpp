#ifndef INTEGRATORS_OMELYAN_BA5B_HPP
#define INTEGRATORS_OMELYAN_BA5B_HPP

#include <array>

#include <math.h>
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
      : timestep_(timestep),
        normal_(0, 1)
    {}

    /**
     *      * perform one integration step for the particle given
     *           */
    void operator() (particle& p);
    template <typename rng_type>
    double randomForce(rng_type& rng);
    double randomforce;

    double grad_Potential(double r);
    
    double RG_velocity(double v);
    double RG_acceleration(double potential_force, double v, double m, double gamma, double random_force);
    double temp_force;
private:
    /** integration time step */
    double timestep_;
    double RG_01;
    double RG_02;
    
    /** parameters: the first four subinterval lengths */
    static constexpr double theta_  = 0.08398315262876693;
    static constexpr double rho_    = 0.2539785108410595;
    static constexpr double lambda_ = 0.6822365335719091;
    static constexpr double mu_     = -0.03230286765269967;
    static constexpr double U_depth = 3;
    

    std::normal_distribution<double> normal_;
};

template <typename rng_type>
double omelyan_BA5B::randomForce(rng_type& rng)
{
        double f = normal_(rng);
        return f;
}

double omelyan_BA5B::grad_Potential(double r)
{
        double f = -U_depth*4*(pow(r, 3.0)-r);
        return f;
}

double omelyan_BA5B::RG_velocity(double v)
{
	return v;
}
double omelyan_BA5B::RG_acceleration(double potential_force, double v, double m, double gamma, double random_force)
{
	return (potential_force - gamma*v +random_force)/m;
} 






void omelyan_BA5B::operator() (particle& p)
{

        std::random_device get_seed;
        std::mt19937 rng(get_seed());


        randomforce = sqrt(2*p.gamma/timestep_)*randomForce(rng);
        //randomforce = 0.0;
        p.f =  grad_Potential(p.r);
        // p.r +=p.f*timestep_/p.gamma + sqrt(2*timestep_/p.gamma)*randomforce;
	RG_01 = p.v;
	RG_02 = 0.5*timestep_*RG_acceleration(p.f, p.v, p.mass, p.gamma, randomforce);
	p.f = grad_Potential(p.r+0.5*timestep_*RG_01);
	p.r = p.r + timestep_*RG_01;
	p.v = p.v + timestep_*RG_acceleration(p.f, RG_01, p.mass, p.gamma, randomforce);
}

} // namespace integrators

#endif /* ! INTEGRATORS_OMELYAN_BA5B_HPP*/



