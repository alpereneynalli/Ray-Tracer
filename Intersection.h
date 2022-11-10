#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "Utils.h"
#include "Ray.h"
class Intersection
{

public:
    float t;
    Vec3f intersectionPoint;
    Vec3f normal;
    int material_id;
    int obj_id;
    bool flag;

    void sphereIntersect(Scene const &scene, Ray ray, int index);
    void triangleIntersect(Scene const &scene, Ray ray, int index, bool isMesh, int meshIndex);
    void meshIntersect(Scene const &scene, Ray ray, int index);
    static Intersection calculateIntersection(Scene const &scene, Ray ray);
    static Intersection findFirst(std::vector<Intersection> &data);
};

#endif