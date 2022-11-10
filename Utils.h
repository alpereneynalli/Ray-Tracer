#ifndef __UTILS_H__
#define __UTILS_H__

#include "parser.h"
using namespace parser;

Vec3f add(const Vec3f& a,const Vec3f& b);


Vec3f operator+(const Vec3f& a,const Vec3f& b);

Vec3f substract (const Vec3f&a, const Vec3f&b);

Vec3f operator-(const Vec3f& a,const Vec3f& b);

Vec3f multFloat (const Vec3f&a, float b);

Vec3f operator* (const Vec3f&a, float b);

Vec3f divFloat (const Vec3f&a, float b);

Vec3f operator/(const Vec3f&a, float b);

/*
Vec3f operator= (Vec3f &a, const Vec3f &b){
    MUST BE A MEMBER FUNCTION
}*/

/*Vec3f& vec_copy(Vec3f b){
    Vec3f* a = new Vec3f;
    a->x = b.x;
    a->y = b.y;
    a->z = b.z;
    return *a;
}
*/

bool vecIsEqual(Vec3f&a, const Vec3f&b);

bool operator==(const Vec3f&a, const Vec3f&b);

bool operator!=(const Vec3f&a, const Vec3f&b);

void operator+=(Vec3f& a, const Vec3f& b);

void operator-=(Vec3f& a, const Vec3f& b);

void operator*= (Vec3f& a, float b);
void operator/=(Vec3f& a, float b);

#endif
