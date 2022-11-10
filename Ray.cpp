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

Ray Ray::generateRay0(const Camera & camera, int i, int j){

    float top = camera.near_plane.w;
    float bottom = camera.near_plane.z;
    float left = camera.near_plane.x;
    float right = camera.near_plane.y;
    float su = (i+0.5)*(right - left) / camera.image_width;
    float sv = (j+0.5)*(top-bottom) / camera.image_height;
    
    // try without normalizing//
    Vec3f gaze = normalize(camera.gaze); // gaze
    Vec3f camPos = camera.position;
    Vec3f v = camera.up;
    //Vec3f m = add(camPos,multFloat(gaze, camera.near_distance)); // center of plane
    Vec3f m = camPos + (gaze * camera.near_distance); // center of plane
    Vec3f u = normalize(crossProduct(gaze, v)); // right direction vector
    //Vec3f q = add(multFloat(v, top),add(m,multFloat(u, left)));
    Vec3f q = (v * top) + (m + (u * left));
    //Vec3f s = substract(add(q, multFloat(u, su)), multFloat(v,sv)); // s is pixel coordinate
    Vec3f s = (q+ (u * su)) - (v * sv);

    Ray ray;
    ray.direction = normalize(s - camPos);
    ray.origin = camPos;    

    return ray;

}
Ray Ray::generateRay(const Camera &camera, int i, int j)
{
    float left = camera.near_plane.x;
    float right = camera.near_plane.y;
    float bottom = camera.near_plane.z;
    float top = camera.near_plane.w;

    Vec3f gaze = normalize(camera.gaze);

    float su = (right - left)*(j + 0.5)/camera.image_width;
    float sv = (top - bottom)*(i + 0.5)/camera.image_height;

    Vec3f m, q, u, v;
    m.x = camera.position.x + (gaze.x * camera.near_distance);
    m.y = camera.position.y + (gaze.y * camera.near_distance);
    m.z = camera.position.z + (gaze.z * camera.near_distance);

    u = crossProduct(gaze, camera.up);
    u = normalize(u);

    v = crossProduct(u, gaze);

    q.x = m.x + (u.x*left) + (v.x*top);
    q.y = m.y + (u.y*left) + (v.y*top);
    q.z = m.z + (u.z*left) + (v.z*top);

    Vec3f s;
    s.x = q.x + (u.x*su) - (v.x * sv);
    s.y = q.y + (u.y*su) - (v.y * sv);
    s.z = q.z + (u.z*su) - (v.z * sv);

    Ray ray;
    ray.origin = camera.position;
    ray.direction = s - camera.position;
    ray.direction = normalize(ray.direction);

    return ray;
}


//Vec3f Ray::getT(const Vec3f&p)const{
    // p = o + td; p - o = td
//}
