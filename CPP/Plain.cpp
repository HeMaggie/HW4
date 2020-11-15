#include "Plain.h"
#include <limits>

using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Plain::intersect(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    
    double t;
    
    //Combine the plain equation(P'- P).dot(Normal) = 0 and ray equation P'= ray.origin + t*ray.direction
    //will get t.
    t = (P - ray.origin).dot(Normal)/(ray.direction.dot(Normal));
   
    //Only when t is non negative will the ray hit the plain
    if (t >= 0)
    {
        result.t = t;
        result.position = ray.origin + t * ray.direction;
        result.normal = Normal.normalized();
        result.shape = this;
    }
    
    return result;
}
