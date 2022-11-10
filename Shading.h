#ifndef __SHADING_H__
#define __SHADING_H__

#include "Utils.h"
#include "Intersection.h"
#include "Helpers.h"

Vec3f findColor(Scene const &scene, const Camera &camera, const Intersection &intersectionPoint, const Ray &ray,int maxDepth);
Vec3f calcIrradiance(const PointLight &light, const Vec3f& intersectionPoint );
Vec3f calcDiffuse(Scene const &scene, const PointLight &light, const Vec3f& intersectionPoint, const Vec3f &wi, int material_id, const Vec3f &normal);
Vec3f calcSpecular(Scene const &scene, const PointLight &light, const Vec3f& intersectionPoint,const Vec3f &wi, int material_id, const Vec3f &normal, const Ray &ray);




#endif