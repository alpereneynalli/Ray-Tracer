#ifndef _RAY_H_
#define _RAY_H_

#include "parser.h"

using namespace parser;


class Ray
{
public:

    Vec3f origin;
    Vec3f direction;

    Ray();
    Ray(const Vec3f&origin, const Vec3f&direction);
    static Ray generateRay0(const Camera & camera, int i, int j);
    static Ray generateRay(const Camera & camera, int i, int j);

    Vec3f getRayPoint(float t);
    // Vec3f getT(const Vec3f&point)const;
};

#endif