//The entry point for the program. Sets up a scene, initiates ray tracing, and saves the output.

#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plain.h"
#include "Triangle.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image image(400, 400);
    Scene scene;

    //1.Sphere
    Vector3d center;
    Vector3d objColor;
    
    //1.1
    center = Vector3d(0,0,4);
    objColor = Vector3d(0.6,0.2,0.9);
    scene.addShape(new Sphere(center, 2, objColor));

    //1.2
    center = Vector3d(-0.5,1,2.5);
    objColor = Vector3d(0.1,0.5,0.1);
    scene.addShape(new Sphere(center, .5, objColor));

    //1.3
    center = Vector3d(0.5,1.25,2.75);
    objColor = Vector3d(0.9,0.7,0.6);
    scene.addShape(new Sphere(center, .5, objColor));

    
    //2.Triangle
    Vector3d vertex1 = Vector3d(0.0,0.2,1.7);
    Vector3d vertex2 = Vector3d(1.0,-0.5,1.0);
    Vector3d vertex3 = Vector3d(-1.0,0.0,1.5);
    objColor  = Vector3d(0.3,0.7,0.6);
    scene.addShape(new Triangle(vertex1,vertex2,vertex3,objColor));
    
    //3.Plain
    Vector3d p = Vector3d(0,-2,0);  //A random point in the plain
    Vector3d normal = Vector3d(0,1,0);  //Normal of the plain
    objColor  = Vector3d(1.0,1.0,1.0);
    scene.addShape(new Plain(p,normal,objColor));
    
    //Render scene
    scene.render(image);
    image.writePNG("test.png");

    return 0;
}
