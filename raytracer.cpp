#include <iostream>
#include "parser.h"
#include "ppm.h"
#include "Ray.h"
#include "Intersection.h"
#include <vector>
#include "float.h"
#include <cmath>
#include "Helpers.h"

typedef unsigned char RGB[3];
using namespace parser;

Vec3f findPixelColor(Scene const &scene, const Camera &camera, const Intersection &intersection, const Ray &ray)
{
    float pixel1 = 0;
    float pixel2 = 0;
    float pixel3 = 0;

    Vec3f pixelColor;

    int lightsSize = scene.point_lights.size();
    int spheresSize = scene.spheres.size();
    int trianglesSize = scene.triangles.size();
    int meshesSize = scene.meshes.size();

    if (intersection.flag)
    {
        int material_id = intersection.material_id;

        pixel1 = scene.materials[material_id - 1].ambient.x * scene.ambient_light.x;
        pixel2 = scene.materials[material_id - 1].ambient.y * scene.ambient_light.y;
        pixel3 = scene.materials[material_id - 1].ambient.z * scene.ambient_light.z;

        for (int currentLight = 0; currentLight < lightsSize; currentLight++)
        {
            PointLight light = scene.point_lights[currentLight];
            bool isShadow = false;

            Vec3f wi = normalize(intersection.intersectionPoint - light.position);
            Vec3f epsilon = wi * scene.shadow_ray_epsilon;

            Ray ray(intersection.intersectionPoint + epsilon, wi);
            
            for (int currentSphere = 0; currentSphere < spheresSize; currentSphere++)
            {
                /* code */
            }

            if (!isShadow)
            {
                for (int currentTriangle = 0; currentTriangle < trianglesSize; currentTriangle++)
                {
                    /* code */
                }
                
            }
            
            if (!isShadow)
            {
                for (int currentMesh = 0; currentMesh < meshesSize; currentMesh++)
                {
                    /* code */
                }
            }
            
            
        }
        
    }
    else
    {
        pixel1 = scene.background_color.x;
        pixel2 = scene.background_color.y;
        pixel3 = scene.background_color.z;
    }

    pixelColor.x = pixel1;
    pixelColor.y = pixel2;
    pixelColor.z = pixel3;

    return pixelColor;
}

int main(int argc, char *argv[])
{
    Scene scene;
    scene.loadFromXml("/mnt/c/Users/alpereneynalli/Desktop/477/code_template/simple.xml");
    int cameraNumber = scene.cameras.size();

    for (int c = 0; c < cameraNumber; c++)
    {
        Camera cur = scene.cameras[c];
        int width = cur.image_width;
        int height = cur.image_height;

        unsigned char *image = new unsigned char[width * height * 3];
        int pixelNumber = 0;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Ray ray = Ray::generateRay0(cur, j, i);

                Intersection theOne = Intersection::calculateIntersection(scene, ray);

                Vec3f pixelColor = findPixelColor(scene, cur, theOne, ray);

                if (pixelColor.x > 255)
                    image[pixelNumber] = 255;
                else
                    image[pixelNumber] = round(pixelColor.x);

                if (pixelColor.y > 255)
                    image[pixelNumber + 1] = 255;
                else
                    image[pixelNumber + 1] = round(pixelColor.y);

                if (pixelColor.z > 255)
                    image[pixelNumber + 2] = 255;
                else
                    image[pixelNumber + 2] = round(pixelColor.z);

                pixelNumber += 3;
            }
        }

        write_ppm(cur.image_name.c_str(), image, width, height);
    }
}
