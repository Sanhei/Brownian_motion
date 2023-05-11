#include <random>
#include <iostream>
#include <fstream>
#include <vector>

class try_random
{
public:
        try_random(double x)
                :normal_(0, x)
        {}

        template <typename container_type, typename rng_type>
        void operator() (container_type& particles, rng_type& rng, bool zero_vcm=false);

private:
        std::normal_distribution<double> normal_;
}; //end of class

template <typename container_type, typename rng_type>
void try_random::operator() (container_type& particles, rng_type& rng, bool zero_vcm)
{
        for( auto& p : particles)
                p = normal_(rng);
}


int main(int argc, char** argv)
{
        std::random_device get_seed;
        std::mt19937 rng(get_seed());

        std::vector<double> test_vector;
        for(int i=0; i< 10; i++)
                test_vector.push_back(i);
        try_random output_random(100.);
        output_random(test_vector, rng);
        for(int i=0; i< 10; i++)
                std::cout<<test_vector[i]<<std::endl;
        return 0;
}
