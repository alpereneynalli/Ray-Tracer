#include <iostream>
#include "parser.h"
#include "ppm.h"
#include "Ray.h"
#include "Intersection.h"
#include <vector>
#include "float.h"
#include <cmath>
#include "Helpers.h"
#include "Shading.h"

#include <chrono>
#include <ctime>

typedef unsigned char RGB[3];
using namespace parser;


int main(int argc, char *argv[1])
{
    Scene scene;
    scene.loadFromXml(argv[1]);
    int cameraNumber = scene.cameras.size();

    int progressBar = 0;
    auto start = std::chrono::system_clock::now();

    for (int c = 0; c < cameraNumber; c++)
    {
        Camera curr = scene.cameras[c];
        int width = curr.image_width;
        int height = curr.image_height;

        unsigned char *image = new unsigned char[width * height * 3];
        int pixelIndex = 0;
        std::cout << curr.image_name.c_str() << std::endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Ray ray = Ray::generateRay(curr, j, i);

                Intersection theOne = Intersection::calculateIntersection(scene, ray);

                Vec3f pixelVal = findColor(scene, curr, theOne, ray, scene.max_recursion_depth);

                image[pixelIndex++] = pixelVal.x;

                image[pixelIndex++] = pixelVal.y;

                image[pixelIndex++] = pixelVal.z;

            }

            if(i * 100 / height > progressBar)
            {
                

                progressBar = i * 100 / height;
                std::cout << progressBar << "% ";// Some computation here

                auto end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = end-start;
                std::cout << "elapsed time: " << elapsed_seconds.count() << "s"
                        << std::endl;
            }
        
        }

        write_ppm(curr.image_name.c_str(), image, width, height);
    }
}
