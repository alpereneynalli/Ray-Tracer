#include <iostream>
#include "parser.h"
#include "ppm.h"
#include "Ray.h"
#include "Intersection.h"
#include <vector>
#include "float.h"
#include <cmath>

typedef unsigned char RGB[3];
using namespace parser;

Vec3f findPixelColor(Scene const &scene, const Camera &camera, const Intersection &intersection, const Ray &ray)
{
    float pixel1 = 0;
    float pixel2 = 0;
    float pixel3 = 0;

    Vec3f pixelColor;

    if (intersection.flag)
    {
        int material_id = intersection.material_id;

        pixel1 = scene.materials[material_id - 1].ambient.x * scene.ambient_light.x;
        pixel2 = scene.materials[material_id - 1].ambient.y * scene.ambient_light.y;
        pixel3 = scene.materials[material_id - 1].ambient.z * scene.ambient_light.z;
        
    }
    else // if hitHappened == 0
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
    int sizeOfSpheres = scene.spheres.size();
    int sizeOfTriangles = scene.triangles.size();
    int sizeOfMeshes = scene.meshes.size();
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

                std::vector<Intersection> intersectionData;
                int id = 0;

                for (int s = 0; s < sizeOfSpheres; s++)
                {
                    Intersection data;
                    data.sphereIntersect(scene, ray, s);
                    if (data.flag && data.t >= 0) // data.t < __FLT_MAX__) // try >
                    {
                        data.obj_id = id++;
                        intersectionData.push_back(data);
                    }
                }

                for (int t = 0; t < sizeOfTriangles; t++)
                {
                    Intersection data;
                    data.triangleIntersect(scene, ray, t, 0, 7);
                    if (data.flag && data.t >= 0)
                    {
                        data.obj_id = id++;
                        intersectionData.push_back(data);
                        // std::cout << "triangle found " << "\n";
                    }
                }

                for (int m = 0; m < sizeOfMeshes; m++)
                {
                    Intersection data;
                    data.meshIntersect(scene, ray, m);
                    if (data.flag && data.t >= 0)
                    {
                        data.obj_id = id++;
                        intersectionData.push_back(data);
                    }
                }

                Intersection theOne = Intersection::findFirst(intersectionData);

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
