#include "Image.h"
#include "ImageManipulation.h"
#include <filesystem>
#include <iostream>
#include <string>


int runTests(Image &example, Image &img)
{
	// if the images are equal, return 1
    if (img == example)
    {
        std::cout << "Test Passed" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Test Failed" << std::endl;
        return 0;
    }
}


void helpMessage(){
    std::cout << "Project 2: Image Processing, Spring 2023" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "          ./project2.out [output] [firstImage] [method] [...]" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc == 1 || (argc == 2 && std::string(argv[1]) == "--help")){
        helpMessage();
        return 0;
    }

    Image trackingImage;

    std::string output = argv[1];
    std::string firstImage = argv[2];

    if (firstImage.find(".tga") == std::string::npos) 
    {
        std::cerr << "Invalid file name." << std::endl;
        return 1;
    }

    // iterate through the arguments
    for (int i = 3; i < argc; i++)
    {
        std::string method = argv[i];

        if (method == "multiply" || method == "subtract" || method == "overlay" || method == "screen")
        {
            i++;
            if (i >= argc)
            {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }
            std::string secondImage = argv[i];
            if (secondImage.find(".tga") == std::string::npos)
            {
                std::cerr << "Invalid argument, invalid file name." << std::endl;
                return 1;
            }
            Image image2;
            try {
                image2.loadImage(".\\" + secondImage);
            }
            catch (const std::exception& e) {
                std::cerr << "Invalid argument, could not load image." << std::endl;
                return 1;
            }

            if (method == "multiply")
            {
                trackingImage = Multiply(trackingImage, image2);
                std::cout << "Multiplying " << firstImage << " and " << secondImage << " ..." << std::endl;
            }
            else if (method == "subtract")
            {
                trackingImage = Subtract(trackingImage, image2);
            }
            else if (method == "overlay")
            {
                trackingImage = Overlay(trackingImage, image2);
            }
            else if (method == "screen")
            {
                trackingImage = Screen(trackingImage, image2);
            }
        }
        else if (method == "combine")
        {
            i++;
            if (i >= argc)
            {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }
            std::string greenFile = argv[i];
            Image green;
            try {
                green.loadImage(greenFile);
            }
            catch (const std::exception& e) {
                std::cerr << "Invalid argument, could not load image." << std::endl;
                return 1;
            }

            i++;
            if (i >= argc)
            {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }

            std::string blueFile = argv[i];
            Image blue;
            try {
                blue.loadImage(blueFile);
            }
            catch (const std::exception& e) {
                std::cerr << "Invalid argument, could not load image." << std::endl;
                return 1;
            }

            trackingImage = combineChannels(trackingImage, green, blue);
        }
        else if (method == "flip")
        {
            trackingImage = Rotate(trackingImage);
        }
        else if (method == "onlyred" || method == "onlygreen" || method == "onlyblue")
        {
            trackingImage = splitChannels(method.substr(4), trackingImage);
        }
        else if (method == "addred" || method == "addgreen" || method == "addblue"){
            i++;
            if (i >= argc)
            {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }
            try {
                int addnum = std::stoi(argv[i]);
                trackingImage = addColor(trackingImage, method.substr(3), addnum);
            }
            catch (const std::exception& e) {
                std::cerr << "Invalid argument, expected number." << std::endl;
                return 1;
            }
        }
        else if (method == "scaleblue" || method == "scalegreen" || method == "scalered")
        {
            i++;
            if (i >= argc)
            {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }
            try {
                int scale = std::stoi(argv[i]);
                trackingImage = scaleColor(trackingImage, method.substr(5), scale);
            }
            catch (const std::exception& e) {
                std::cerr << "Invalid argument, expected number." << std::endl;
                return 1;
            }
        }
        else
        {
            std::cerr << "Invalid method name." << std::endl;
            return 1;
        }
    }

    try {
        trackingImage.writeImage(output);
    }
    catch (const std::exception& e) {
        std::cerr << "Invalid argument, could not write image." << std::endl;
        return 1;
        }
    return 0;
}