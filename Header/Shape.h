#ifndef SHAPE_H
#define SHAPE_H

#include <Eigen/Dense>


namespace Raytracer148 {
    struct Ray
    {
        Eigen::Vector3d origin, direction;
    };
    class Shape;
    
    struct HitRecord
    {
        Eigen::Vector3d position, normal;
        double t;
        Shape * shape = nullptr;
    };
    
    class Shape
    {
        public:
            Eigen::Vector3d objectColor;
            virtual ~Shape(){}
            virtual HitRecord intersect(const Ray &ray) = 0;
    };

}

#endif
