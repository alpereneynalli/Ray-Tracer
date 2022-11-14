#include "Intersection.h"
#include "parser.h"
#include "Helpers.h"
#include "Utils.h"
#include <iostream>
#include <float.h>

Intersection Intersection::calculateIntersection(Scene const &scene, Ray ray){

    int sizeOfSpheres = scene.spheres.size();
    int sizeOfTriangles = scene.triangles.size();
    int sizeOfMeshes = scene.meshes.size();

    int id = 0;

    Intersection theOne;
    theOne.flag = false;
    float minT = FLT_MAX;

    for (int s = 0; s < sizeOfSpheres; s++)
    {
        Intersection data;
        data.sphereIntersect(scene, ray, s);
        data.obj_id = id++;
        if (data.flag && data.t >= 0) // data.t < __FLT_MAX__) // try >
        {   
            if(data.t < minT){
                minT = data.t;
                theOne = data;
            }
            
        }
    }

    for (int t = 0; t < sizeOfTriangles; t++)
    {
        Intersection data;
        
        data.triangleIntersect(scene, ray, t, 0, 7);
        data.obj_id = id++;
        if (data.flag && data.t >= 0)
        {
            if(data.t < minT){
                minT = data.t;
                theOne = data;
            }
        }
    }

    for (int m = 0; m < sizeOfMeshes; m++)
    {
        Intersection data;
        data.meshIntersect(scene, ray, m);
        data.obj_id = id++;

        if (data.flag && data.t >= 0)
        {
            if(data.t < minT){
                minT = data.t;
                theOne = data;
            }
        }
    }

    
    return theOne;
}


void Intersection::sphereIntersect(Scene const &scene, Ray ray, int index)
{
    Sphere sphere = scene.spheres[index];
    Vec3f center = scene.vertex_data[sphere.center_vertex_id - 1];
    Vec3f direction = ray.direction;
    Vec3f origin = ray.origin;

    float radius = sphere.radius;
    float A = dotProduct(direction, direction);
    float B = 2 * dotProduct(direction, origin - center);
    float C = dotProduct(origin - center, origin - center) - powf(radius, 2);
    float disc = powf(B, 2) - 4 * A * C;

    if (disc < 0)
    {
        flag = false;
    }

    else
    {
        t = fminf((-1 * B + sqrtf(disc)) / 2 * A, (-1 * B - sqrtf(disc)) / 2 * A);
        intersectionPoint = ray.getRayPoint(t);
        flag = true;
        material_id = sphere.material_id;
        normal = (intersectionPoint - center) / radius;
    }
}


void Intersection::triangleIntersect(Scene const &scene, Ray ray, int index, bool isMesh, int meshIndex)
{
    Vec3f direction = ray.direction;
    Vec3f origin = ray.origin;
    Vec3f v0;
    Vec3f v1;
    Vec3f v2;

    if (isMesh)
    {   
        Face face = scene.meshes[meshIndex].faces[index];
        v0 = scene.vertex_data[face.v0_id - 1];
        v1 = scene.vertex_data[face.v1_id - 1];
        v2 = scene.vertex_data[face.v2_id - 1];
        this->material_id = scene.meshes[meshIndex].material_id;
        
    }

    else
    {
        Triangle triangle = scene.triangles[index];
        v0 = scene.vertex_data[triangle.indices.v0_id - 1];
        v1 = scene.vertex_data[triangle.indices.v1_id - 1];
        v2 = scene.vertex_data[triangle.indices.v2_id - 1];
        this->material_id = triangle.material_id;
    }

    Vec3f edge0 = v0 - v1;
    Vec3f edge1 = v0 - v2;
    Vec3f to_origin = v0 - origin;

    flag = false;

    float det0 = determinant(edge0.x, edge1.x, direction.x,
                             edge0.y, edge1.y, direction.y,
                             edge0.z, edge1.z, direction.z);

    if (det0 == 0.0f)
    {
        return;
    }
    
    float G = determinant(edge0.x, to_origin.x, direction.x,
                          edge0.y, to_origin.y, direction.y,
                          edge0.z, to_origin.z, direction.z) / det0;
    if (G < 0 || G > 1)
    {
        return;
    }

    float B = determinant(to_origin.x, edge1.x, direction.x,
                          to_origin.y, edge1.y, direction.y,
                          to_origin.z, edge1.z, direction.z) / det0;
    if (B < 0 || B > 1 - G)
    {
        return;
    }


    t = determinant(edge0.x, edge1.x, to_origin.x,
                    edge0.y, edge1.y, to_origin.y,
                    edge0.z, edge1.z, to_origin.z) / det0;
    if (t <= 0)
    { // CHECK IF NEC FOR T
        return;
    }

    this->flag = true;
    this->intersectionPoint = ray.getRayPoint(t);
    this->normal = normalize(crossProduct(v1 - v0, v2 - v0));
    
}
void Intersection::meshIntersect(Scene const &scene, Ray ray, int index)
{
    Mesh mesh = scene.meshes[index];
    Intersection element;
    Intersection theOne;
    theOne.flag = false;
    float minT = __FLT_MAX__;
    int faceSize = mesh.faces.size();


    for (int faceIndex = 0; faceIndex < faceSize; faceIndex++)
    {
        element.triangleIntersect(scene, ray, faceIndex, 1, index);
        if (element.flag && element.t >= 0)
        { // check t
            if(element.t < minT){
                minT = element.t;
                theOne = element;
            }
        }
    }
    
    *this = theOne;
}
