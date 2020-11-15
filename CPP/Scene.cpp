//Stores the objects in a scene and performs basic ray tracing
#include "Scene.h"
#include <cmath>

// GLM Mathematics
#define GLM_FORCE_RADIANS // force everything in radian
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            result = r;
            foundSomething = true;
        }
    }
    return result;
}



//======================*Check if a pixel is lit by the light*=====================//
bool Scene::litByLight(HitRecord r)
{
    //1.---Get the ray from lightPos to the r.position
    Ray rayToLight;
    rayToLight.direction = r.position - lightPos;
    rayToLight.origin = lightPos;
    
    //2.---If the closestHit is not on the same shape as ray does, then that pixel will be shaded, and return false.
    HitRecord hit = closestHit(rayToLight);
    if(hit.shape != r.shape)
        return false;
    
    return true;
}



//============*Returns an RGB color, where R/G/B are each in the range [0,1]*=========//
Vector3d Scene::trace(const Ray &ray, int reflectionTimes) {
    //Recursion termination
    if(reflectionTimes < 0) {
        return Vector3d(0,0,0);
    }
    //Closest hit
    HitRecord r = closestHit(ray);
    
    //Initialize the result color
    Vector3d result;
    result = Vector3d(0,0,0);
    
    //=======Case 1. No intersection=======//
    if (r.t < numeric_limits<double>::epsilon()) return result;

    //=======Case 2. With intersection=======//
    Vector3d lightColor = Vector3d(1,1,1);
    
    /*-Problem 3: Shadow-*/
    //Check if this spot lit by the light, if not return color (0,0,0);
    if(!litByLight(r))  //function litByLight() is defined above
        return result;
    
    /*-Problem 2: Phong Shading-*/
    //2.1 Diffuse -- /Problem 1: Diffuse Only/
    Vector3d lightDir = (lightPos - r.position).normalized();
    double diff = max(lightDir.dot(r.normal),0.0);
    Vector3d diffuse = diff * lightColor;

    //2.2 Ambient
    float ambientStrength = 0.5;
    Vector3d ambient = ambientStrength * lightColor;
    
    //2.3 Specular
    float specularStrength = 5;
    Vector3d viewDir = (viewPos - r.position).normalized();
    Vector3d reflectedDir = -lightDir + 2*(lightDir.dot(r.normal))*r.normal; //glm::reflect(-lightDir, r.normal), is somehow not working here, so I use this reflection equation.
    double spec = pow(max(reflectedDir.dot(viewDir),0.0),128);
    Vector3d specular = specularStrength * spec * lightColor;

    //2.4 Apply object color
    Vector3d r0 = (diffuse + ambient + specular);
    result[0] = r0[0]*(r.shape->objectColor)[0];
    result[1] = r0[1]*(r.shape->objectColor)[1];
    result[2] = r0[2]*(r.shape->objectColor)[2];
    
     /*-Problem 4: Glossy reflection-*/
    //2.5 Glossy reflection
    Ray reflectedRay;
    reflectedRay.direction = ray.direction - 2*(ray.direction.dot(r.normal))*r.normal; //glm::reflect(ray.direction, r.normal) is somehow not working here, so I use this reflection equation.
    reflectedRay.origin = r.position - ray.direction/10000;  //ray.direction/10000 is added because r.position is not exactly where the surface is
    result += 0.25 * trace(reflectedRay,reflectionTimes-1); //add the reflected color to the result
    
    return result;
}



//=============================*Trace calls trace*=============================//
Vector3d Scene::Trace(const Ray &ray){
    return trace(ray,5);    //the depth of reflection is set to 5.
}




//==============================Render Image================================//
void Scene::render(Image &image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    size_t size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;
            
            Vector3d color = Trace(curRay);
            image.setColor(x, y, color[0], color[1], color[2]);
        }
}
