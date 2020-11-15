#ifndef Triangle_h
#define Triangle_h

#include "Shape.h"

namespace Raytracer148 {
    class Triangle : public Shape {
    public:
        Triangle(Eigen::Vector3d &vertex0, Eigen::Vector3d &vertex1,Eigen::Vector3d &vertex2, Eigen::Vector3d &objColor)
        {
            v0 = vertex0;
            v1 = vertex1;
            v2 = vertex2;
            objectColor = objColor;
        }
        
        virtual HitRecord intersect(const Ray &ray);
    
    private:
        Eigen::Vector3d v0;
        Eigen::Vector3d v1;
        Eigen::Vector3d v2;
    };
}

#endif /* Triangle_h */
