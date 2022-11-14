
#include "Utils.h"
using namespace parser;


Vec3f operator+(const Vec3f& a,const Vec3f& b){
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}


Vec3f operator-(const Vec3f& a,const Vec3f& b){
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}


Vec3f operator* (const Vec3f&a, float b){
    return {a.x * b, a.y * b, a.z * b};
}


Vec3f operator/(const Vec3f&a, float b){
    return {a.x / b, a.y / b, a.z / b};
}


Vec3f elementMultiply(const Vec3f&a, const Vec3f &b){
    Vec3f result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    return result;
}

bool operator==(const Vec3f&a, const Vec3f&b){
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool operator!=(const Vec3f&a, const Vec3f&b){
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

void operator+=(Vec3f& a, const Vec3f& b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
}

void operator-=(Vec3f& a, const Vec3f& b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
}

void operator*= (Vec3f& a, float b){
    a.x *= b;
    a.y *= b;
    a.z *= b;
}
void operator/=(Vec3f& a, float b){
    a.x /= b;
    a.y /= b;
    a.z /= b;
}


