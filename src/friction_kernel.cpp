#include <cmath>
double friction_kernel(double x){
        double gamma_0 = 1;
        double A = 0.2;
        return gamma_0 - A*pow(cos(x*M_PI), 2);
}
