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

    for (int c = 0; c < cameraNumber; c++)
    {
        Camera cur = scene.cameras[c];
        int width = cur.image_width;
        int height = cur.image_height;

        unsigned char *image = new unsigned char[width * height * 3];
        int pixelNumber = 0;
        
        //change
        int progressBar = 0;
        auto start = std::chrono::system_clock::now();

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Ray ray = Ray::generateRay0(cur, j, i);

                Intersection theOne = Intersection::calculateIntersection(scene, ray);

                Vec3f pixelColor = findColor(scene, cur, theOne, ray, scene.max_recursion_depth);

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

            //delete
            if(i * 100 / width > progressBar)
            {
                progressBar = i * 100 / width;
                std::cout << progressBar << "% ";// Some computation here
                auto end = std::chrono::system_clock::now();
            
                std::chrono::duration<double> elapsed_seconds = end-start;
            
                std::cout << "elapsed time: " << elapsed_seconds.count() << "s"
                        << std::endl;
            }

        }

        write_ppm(cur.image_name.c_str(), image, width, height);
    }
}
