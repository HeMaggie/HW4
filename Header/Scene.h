#ifndef SCENE_H
#define SCENE_H

#include "Shape.h"
#include "Image.h"
#include <vector>
#include <limits>

namespace Raytracer148 {
    class Scene {
    private:
        std::vector<Shape*> shapes;
        Eigen::Vector3d lightPos;
        Eigen::Vector3d viewPos;
    public:
        Scene(){lightPos = Eigen::Vector3d(3.5,5,-1); viewPos = Eigen::Vector3d(0,0,0);}
        void addShape(Shape *s) { shapes.push_back(s);}
        HitRecord closestHit(const Ray &ray);
        Eigen::Vector3d trace(const Ray &ray, int reflectionTimes);
        Eigen::Vector3d Trace(const Ray &ray);
        void render(Image &image);
        bool litByLight(HitRecord r);
        
        virtual ~Scene()
        {
            for (unsigned int i = 0; i < shapes.size(); i++)
            delete shapes[i];
            shapes.resize(0);
        }
    };
}

#endif
