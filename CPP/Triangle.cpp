#include "Triangle.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Triangle::intersect(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    
    //Moller Trumbore Algorithm
    Eigen::Vector3d E1, E2, S, S1, S2;
    double t, b1, b2;
    
    E1 = v1 - v0;
    E2 = v2 - v0;
    S = ray.origin - v0;
    S1 = ray.direction.cross(E2);
    S2 = S.cross(E1);
    
    t = (S2.dot(E2))/(S1.dot(E1));
    b1 = (S1.dot(S))/(S1.dot(E1));
    b2 = (S2.dot(ray.direction))/(S1.dot(E1));
    
    //The hit point is on the triangle only when hit time t, and the barycentric coordinate are non-negative
    if (t>=0 && b1 >= 0 && b2 >= 0 && (b1+b2)<=1 ){
        result.t = t;
        result.position = ray.origin + t * ray.direction;
        result.normal = (-(v2-v0).cross(v1-v0)).normalized();
        result.shape = this;
    }
    
    return result;
}
