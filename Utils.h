#ifndef __UTILS_H__
#define __UTILS_H__

#include "parser.h"
using namespace parser;



Vec3f operator+(const Vec3f& a,const Vec3f& b);

Vec3f operator-(const Vec3f& a,const Vec3f& b);

Vec3f operator* (const Vec3f&a, float b);

Vec3f elementMultiply(const Vec3f&a, const Vec3f &b);

Vec3f operator/(const Vec3f&a, float b);

bool operator==(const Vec3f&a, const Vec3f&b);

bool operator!=(const Vec3f&a, const Vec3f&b);

void operator+=(Vec3f& a, const Vec3f& b);

void operator-=(Vec3f& a, const Vec3f& b);

void operator*= (Vec3f& a, float b);
void operator/=(Vec3f& a, float b);

#endif
