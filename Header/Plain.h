#ifndef Plain_hpp
#define Plain_hpp

#include "Shape.h"

namespace Raytracer148 {
    class Plain : public Shape {
    public:
        Plain(Eigen::Vector3d &p, Eigen::Vector3d &n, Eigen::Vector3d &objColor)
        {
            P = p;
            Normal = n;
            objectColor = objColor;
        }
        
        virtual HitRecord intersect(const Ray &ray);
        
    private:
        Eigen::Vector3d P;
        Eigen::Vector3d Normal;
    };
}
#endif /* Plain_hpp */
