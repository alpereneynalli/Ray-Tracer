#include "Ray.h"
#include "Helpers.h"

Ray::Ray()
{
}

Ray::Ray(const Vec3f&origin, const Vec3f&direction){
    this->origin = origin;
    this->direction = direction;
}

Vec3f Ray::getRayPoint(float t){
    return this->origin + (this->direction * t);
}

Ray Ray::generateRay(const Camera & camera, int i, int j){

    float top = camera.near_plane.w;
    float bottom = camera.near_plane.z;
    float left = camera.near_plane.x;
    float right = camera.near_plane.y;
    float su = (i+0.5)*(right - left) / camera.image_width;
    float sv = (j+0.5)*(top - bottom) / camera.image_height;
    
    Vec3f gaze = normalize(camera.gaze); // gaze
    Vec3f camPos = camera.position;
    Vec3f v = camera.up;
    Vec3f m = camPos + (gaze * camera.near_distance); // center of plane
    Vec3f u = normalize(crossProduct(gaze, v)); // right direction vector
    Vec3f q = (v * top) + (m + (u * left));
    Vec3f s = (q+ (u * su)) - (v * sv);

    Ray ray;
    ray.direction = normalize(s - camPos);
    ray.origin = camPos;    

    return ray;

}


float Ray::getT(const Vec3f&p)const{
    Vec3f diff = p - this->origin;
    
    return (diff.x + diff.y + diff.z)  / (this->direction.x + this->direction.y + this->direction.z);
}
