// copied

#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <cmath>
#include "Utils.h"

inline float dotProduct(const Vec3f & first, const Vec3f & second)
{
	return ((first.x * second.x) + (first.y * second.y) + (first.z * second.z));
}


inline Vec3f crossProduct(const Vec3f & first, const Vec3f & second)
{
    Vec3f res;
    res.x = (first.y*second.z) - (first.z*second.y);
    res.y = (first.z*second.x) - (first.x*second.z);
    res.z = (first.x*second.y) - (first.y*second.x);

    return res;
}

inline float determinant(
            float x_00,float x_01,float x_02,
            float x_10,float x_11,float x_12,
            float x_20,float x_21,float x_22)
{
    return
        (x_00 * ((x_11 * x_22) - (x_21 * x_12))) -
        (x_10 * ((x_22 * x_01) - (x_02 * x_21))) +
        (x_20 * ((x_01 * x_12) - (x_02 * x_11)));
}

inline float vectorLength(const Vec3f & vector) {
    return std::sqrt(vector.x * vector.x
                     + vector.y * vector.y
                     + vector.z * vector.z );
}

inline Vec3f normalize(Vec3f vector) {
    float vecLength = vectorLength(vector);
    if (vecLength == 0.0f)
        return Vec3f(); // return zero vector

    vector = divFloat(vector, vecLength);
    return vector;
}

#endif