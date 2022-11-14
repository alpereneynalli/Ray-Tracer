#include "Shading.h"
#include <iostream>
#include <cmath>

Vec3f findColor(Scene const &scene, const Camera &camera, const Intersection &intersection, const Ray &ray, int maxDepth)
{

    Vec3f pixelVal{0.0f, 0.0f, 0.0f};

    int lightsSize = scene.point_lights.size();
    int spheresSize = scene.spheres.size();
    int trianglesSize = scene.triangles.size();
    int meshesSize = scene.meshes.size();

    if (intersection.flag)
    {
        int material_id = intersection.material_id;


        pixelVal = elementMultiply(scene.materials[material_id - 1].ambient, scene.ambient_light);

        for (int currentLight = 0; currentLight < lightsSize; currentLight++)
        {
            PointLight light = scene.point_lights[currentLight];
            bool isShadow = false;

            Vec3f wi = normalize(light.position - intersection.intersectionPoint);
            Vec3f epsilon = wi * scene.shadow_ray_epsilon;

            Ray rayShadow(intersection.intersectionPoint + epsilon, wi);
            Intersection data;

            float tL = rayShadow.getT(light.position);
            
            for (int cur = 0; cur < spheresSize; cur++)
            {
                Sphere sphere = scene.spheres[cur];
          		Vec3f center = scene.vertex_data[sphere.center_vertex_id - 1];
          		float radius = sphere.radius;

                data.sphereIntersect(scene, rayShadow , cur);

                if (data.flag)
                {
                    if (tL > data.t && data.t >= 0)
                    {
                        isShadow = true;
                        break;
                    }
                    
                }
                
            }

            if (!isShadow)
            {
                for (int cur = 0; cur < trianglesSize; cur++)
                {
                    data.triangleIntersect(scene, rayShadow, cur, 0, 0);
                    
                    if(data.flag)
                    {
                        if(tL > data.t && data.t >= 0)
                        {
                            isShadow = true;
                            break;
                        }
                    }
                }
                
            }
            
            if (!isShadow)
            {
                for (int currentMesh = 0; currentMesh < meshesSize; currentMesh++)
                {
                    data.meshIntersect(scene, rayShadow, currentMesh);
                    
                    if(data.flag)
	            	{
	              		if(tL > data.t && data.t >= 0)
	              		{
	                		isShadow = true;
                            break;
	              		}
	            	}
                }
            }
            
            if(!isShadow)
	        {
		        int material_id = intersection.material_id;

		        Vec3f diffuse = calcDiffuse(scene, light, intersection.intersectionPoint, wi, material_id, intersection.normal);

		        Vec3f specular = calcSpecular(scene, light, intersection.intersectionPoint, wi, material_id, intersection.normal, ray);
		                    
              	pixelVal += diffuse + specular;
            
	        }

            

        }
        
        bool isReflective = scene.materials[material_id - 1].mirror.x > 0.0f || scene.materials[material_id - 1].mirror.y > 0.0f || scene.materials[material_id - 1].mirror.z > 0.0f;
        
        Vec3f reflectionColor = {0.0f, 0.0f, 0.0f};

        if (isReflective && maxDepth > 0)
        {
            Vec3f reflectionDirection = normalize(intersection.normal * (-2 * dotProduct(ray.direction, intersection.normal)) + ray.direction);
            Vec3f epsilon = reflectionDirection * scene.shadow_ray_epsilon;
            Ray reflectionRay(intersection.intersectionPoint + epsilon, reflectionDirection);
            
            
            Intersection reflectionIntersection = Intersection::calculateIntersection(scene, reflectionRay);
            
            if(reflectionIntersection.flag && reflectionIntersection.obj_id != intersection.obj_id){
                reflectionColor = findColor(scene, camera, reflectionIntersection, reflectionRay, maxDepth - 1);
                pixelVal += elementMultiply(reflectionColor, scene.materials[material_id - 1].mirror);
            }

        }

    }
    else
    {
        pixelVal.x = scene.background_color.x;
        pixelVal.x = scene.background_color.y;
        pixelVal.x = scene.background_color.z;
    }

    pixelVal.x = std::min(pixelVal.x, 255.0f);
    pixelVal.y = std::min(pixelVal.y, 255.0f);
    pixelVal.z = std::min(pixelVal.z, 255.0f);
    
    return pixelVal;
}

Vec3f calcIrradiance(const PointLight &light, const Vec3f& intersectionPoint ){
    
    float d_2 = dotProduct(light.position - intersectionPoint, light.position - intersectionPoint);
    
    if(d_2 != 0.0f){
        return light.intensity/d_2;
    }
    else return{0.0f, 0.0f, 0.0f};

}

Vec3f calcDiffuse(Scene const &scene, const PointLight &light, const Vec3f& intersectionPoint,const Vec3f &wi, int material_id, const Vec3f &normal){
    
    Vec3f diffuse = scene.materials[material_id - 1].diffuse;
    Vec3f irradiance = calcIrradiance(light, intersectionPoint);
    float dot = std::max(0.0f, dotProduct(wi, normal));
    
    diffuse = elementMultiply(diffuse, irradiance * dot);

    return diffuse;
}


Vec3f calcSpecular(Scene const &scene, const PointLight &light, const Vec3f& intersectionPoint,const Vec3f &wi , int material_id, const Vec3f &normal, const Ray &ray){
    
    Vec3f specular = scene.materials[material_id - 1].specular;
    Vec3f irradiance = calcIrradiance(light, intersectionPoint);
    Vec3f h = normalize(wi - ray.direction);
    float dot = std::max(0.0f, dotProduct(normal, h));
    
    float phongExp = powf(dot, scene.materials[material_id - 1].phong_exponent);
    
    specular = elementMultiply(specular, irradiance * phongExp);

    return specular;
    
}