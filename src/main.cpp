#include <iostream>
#include <fstream>
#include <cmath>
#include <random>

#include "particle.hpp"
#include "options.hpp"


#include "integrators/omlyan_BA5B.hpp"
#include "integrators/euler.hpp"
#include "force.hpp"
#include "potentials/free_diffusion.hpp"
#include "potentials/double_well.hpp"


#include <string>

#define PROGRAM_NAME "main"

int main(int argc, char** argv)
{
        // parse command line arguments
        program_options options;
        options.parse(argc, argv);

        double timestep = 0.0001;
        particle p;
        double mass = options.get("mass");
        p.mass = mass;
        long int steps = 1000000000;
        p.r = 0.25;
        p.v = 0.1;
        p.f = 0;
        p.rp= 0.25;
        std::cout<<"Mass is "<<p.mass<<std::endl;
        std::cout<<"Gamma is "<<p.gamma<<std::endl;
        integrators::omelyan_BA5B integrate(timestep);
        std::cout<<"Integrate doesn't work"<< timestep <<std::endl;
        integrate.add_potential(potentials::DoubleWell(p));
        std::cout<<"Potential doesn't work"<<std::endl;
        integrate.update_force(p);
        std::cout<<"Time step size is "<< timestep <<std::endl;
        std::cout<<"Simulation start"<<std::endl;
        std::ofstream file;
        std::string fileformat(".txt");
        // file.open(std::to_string(timestep)+fileformat);
        file.open(std::to_string(p.mass)+fileformat);
        for (long int i = 0; i < steps; ++i){
        	if(i>100000){
                	integrate(p);
                	file <<p.r<<std::endl;
                }
        }
        file.close();
}


void program_options::parse(int argc, char** argv)
{
    namespace po = boost::program_options;

    po::options_description desc("Program options");
    desc.add_options()
        ("mass", po::value<double>()->required(), "Mass of particle")

        ("help", "display this help and exit")
        ;

    try {
        po::command_line_parser parser(argc, argv);
        po::parsed_options parsed(parser.options(desc).run());
        po::store(parsed, vm_);

        if (vm_.count("help")) {
            std::cout << "Usage: " PROGRAM_NAME " [OPTION]...\n\n" << desc << std::endl;
            exit(EXIT_SUCCESS);
        }

        po::notify(vm_);
    }
    catch (std::exception const& e) {
        std::cerr << PROGRAM_NAME ": " << e.what() << "\n\n";
        std::cerr << "Try `" PROGRAM_NAME " --help' for more information." << std::endl;
        exit(EXIT_FAILURE);
    }
}
