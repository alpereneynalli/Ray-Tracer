#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <cmath>
#include "Utils.h"
//shading
inline float dotProduct(const Vec3f&a ,const Vec3f&b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3f crossProduct(const Vec3f&a ,const Vec3f&b)
{
    return {a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - b.y * a.x};
}

inline float determinant(float a_00, float a_01, float a_02,
                  float a_10, float a_11, float a_12,
                  float a_20, float a_21, float a_22)
{
    return  ((a_00 * (a_11 * a_22 - a_21 * a_12)) -
            (a_10 * (a_22 * a_01 - a_02 * a_21)) +
            (a_20 * (a_01 * a_12 - a_02 * a_11)));                 
}

inline float vectorLength(const Vec3f& a){
    float length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return length;
}

inline Vec3f normalize(Vec3f a){
    float length = vectorLength(a);
    if(length == 0.0f){
        return a; // a is a zero vector
    }
    a /= length;
    return a;
}
#endif