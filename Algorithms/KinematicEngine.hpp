#ifndef KINEMATICENGINE_HPP_INCLUDED
#define KINEMATICENGINE_HPP_INCLUDED

#include <math.h>

/// TD
/*
    sphere collision detection
    post-collision (?"velocity models"?)
    trajectory intersection and collision (imagine "round lines with thickness")

*/
/*
    replace all the uses of the math library
*/

struct Velocity_2Dim {
    double x {0.0};
    double y {0.0};
    double speed {0.0};   double& s = speed;

    Velocity_2Dim() {}
    Velocity_2Dim(double x, double y) : x(x), y(y) {
        speed = sqrt(x * x + y * y);
    }

    void UpdateSpeed() {
        speed = sqrt(x * x + y * y);
    }
};
struct Particle_2Dim {
    double mass {1.0};  double& m = mass;   // aliasing
    Velocity_2Dim velocity {}; Velocity_2Dim& v = velocity;

    Particle_2Dim() {}
    Particle_2Dim(double velocity_x, double velocity_y, double mass) : velocity(Velocity_2Dim(velocity_x, velocity_y)), mass(mass) {}
};

struct Particle_3Dim {};

void Collide_2Body_v1(Particle_2Dim& a, Particle_2Dim& b) {    // (*?) will "change the originals"
    // implement momentum conservation
    double total_momentum = a.m * a.v.s + b.m * b.v.s;
    std::cout << "[Debugging]\ntotal momentum: " << total_momentum << "\nv1: " << a.v.s << "\nv2: " << b.v.s
                << "\nm1: " << a.m << "\nm2: " << b.m;
    double s_a = (a.m / (a.m + b.m)) * total_momentum;
    double s_b = (b.m / (a.m + b.m)) * total_momentum;


    double error_margin = (total_momentum - s_a * a.m) - s_b * b.m;
    std::cout << "\nv1': " << s_a << "\nv2': " << s_b << "\nerror in momentum conservation: " << error_margin << "\n";
}
bool WillCollide(Particle_2Dim a, Particle_2Dim b) {    // (*?) don't need to change the originals; could use a pointer / reference const though as well
                                                        // but having the data already copied is better than indirectly addressing the memory (?); well,
                                                        // what's the difference when it's already in cache actually (?), just data locality matters, right (?)
}
#endif // KINEMATICENGINE_HPP_INCLUDED
