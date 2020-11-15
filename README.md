# HW3

## Mengmei He
## PSID: 1850021

### 1. Operaing System:
MacOS 10.15

### 2. IDE:
Xcode

### 3. Details:

1. Problem 1: Add files for New Shapes

(1) I added two new cpp files. One for triangle, and another one is for plain.<br>

-a. Triangle.cpp <br>

Triangle constructor takes in three vertices to define the position of the triangles, and one object color to define its original color.<br>
It has one funtion "intersect(const Ray &ray)" inherited from the Shape() class. Function intersect(const Ray &ray) returns the record of the point where ray hits the triangle. To get a hit on triangle, the hit time t must satisfy the equation: o + t * d = (1 - b1 - b2) * v0 + b1 * v1 + b2 * v2;<br>
I used Moller Trumbore Algorithm to determine the values of t, b1, and b2. <br>

t = (S2.dot(E2))/(S1.dot(E1));<br>
b1 = (S1.dot(S))/(S1.dot(E1));<br>
b2 = (S2.dot(ray.direction))/(S1.dot(E1));<br>
where, <br>
E1 = v1 - v0;<br>
E2 = v2 - v0;<br>
S = ray.origin - v0;<br>
S1 = ray.direction.cross(E2);<br>
S2 = S.cross(E1);<br>

When t>=0 && b1 >= 0 && b2 >= 0 && (b1+b2)<=1, the ray will hit on the triangle. <br>
I record the hit point as:<br>
        result.t = t;<br>
        result.position = ray.origin + t * ray.direction;<br>
        result.normal = (-(v2-v0).cross(v1-v0)).normalized();<br>

-b. Plain.cpp<br>

Plain constructor takes in a 3D point, a normal of the plain, and the object color to define its original color. It has one funtion "intersect(const Ray &ray)" inherited from the Shape() class.<br>
Combine the plain equation(P'- P).dot(Normal) = 0 and ray equation P'= ray.origin + t * ray.direction, I will get t = (P - ray.origin).dot(Normal)/(ray.direction.dot(Normal));<br>

When t >= 0, there will be a hit on the plain.<br>
I record the hit point as:<br>
    result.t = t;<br>
    result.position = ray.origin + t * ray.direction;<br>
    result.normal = Normal.normalized();<br>
    
(2) main.cpp: Add new shapes into list of shapes <br>

I add one big sphere, two small spheres, a triangle and one plain to the list of shapes. <br>

--------
2. Problem 2: Do Phong Shading---Scene::tracer() <br>
Set lightColor to (1,1,1)<br>

(1) Diffuse: <br>
diffuse = max(lightDir.dot(r.normal),0.0) * lightColor, <br>
where,<br>
r is the record of the closest hit point,<br>
lightDir = (lightPos - r.position).normalized();<br>

(2) Ambient: <br>
ambient = ambientStrength * lightColor, <br>
where ambientStrength = 0.5;<br>

(3) Specular: <br>
specular = specularStrength * spec * lightColor, <br>
where specularStrength = 5, <br>
spec = pow(max(reflectedDir.dot(viewDir),0.0),128). //reflectedDir is the reflected ray of input ray about the normal.<br>

(4) Object color <br>
Apply object color to the result of (diffuse + ambient + specular). <br>
Each value in the result of (diffuse + ambient + specular) is multiplied by the corresponding value in "objectColor".<br>

----------
3. Problem 3: Do Shadow---Scene::tracer() <br>
The logic is: <br>
If the ray from camera has the closest hit on the same shape as the light has the closest hit, then that pixel will not be in shadow.<br>
Otherwise, The pixel will be in shadow.<br>

(1) Get a ray from lightPosition to the position where the ray from camera first hit on a shape.<br>
rayToLight.direction = r.position - lightPos;<br>
rayToLight.origin = lightPos;<br>

(2)Get the closest hit of "rayToLight".<br>
hit = closestHit(rayToLight);<br>
if(hit.shape != r.shape), where r.shape is the shape ray from camera has the closest hit on,<br>
then the result color of this pixel will be black (0,0,0).<br>
else, the result color will be rendered as what it should be (by phong shading).<br>

----------
4. Problem 4: Glossy Reflection---Scene::tracer() <br>
The way to solve this is: Add the color of the object that is hit by the reflected ray of the ray from camrea.<br>

(1) Get the reflected ray of the ray from camrea around r.normal.<br><br>
(a) reflectedRay.direction = ray.direction - 2*(ray.direction.dot(r.normal))*r.normal.<br>
Note: The glm::reflected() function is somehow not working here, so I use this reflection equation.<br>
(b)reflectedRay.origin = r.position - ray.direction/10000;  
Note: ray.direction/10000 is added because r.position is not exactly where the surface is.<br>

(2)Add the reflected color to the result using recursion<br>
result += 0.25 * trace(reflectedRay,reflectionTimes-1),<br>
where, reflectionTimes is the depth of the reflection.<br>

### 4. IMAGES

1. Shapes

![Image of Ambient](Image/P1.png)

2. Shading

![Image of Ambient](Image/P2.png)

3. Shadow

![Image of Ambient](Image/P3.png)

4. Reflection

![Image of Ambient](Image/P4.png)

### 5. Reference
https://learnopengl.com/Lighting/Basic-Lighting <br>
https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
