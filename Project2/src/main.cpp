#include "Image.h"
#include "ImageManipulation.h"
#include <iostream>
#include <string>

using namespace std;

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

int testing()
{
    int passed = 0;
    int failed = 0;

    // Load Images
    Image layer1;
    Image layer2;
    Image pattern1;
    Image pattern2;
    Image text;
    Image text2;
    Image car;
    Image circles;
    Image layer_blue;
    Image layer_green;
    Image layer_red;

    layer1.loadImage("./input/layer1.tga");
    layer2.loadImage("./input/layer2.tga");
    pattern1.loadImage("./input/pattern1.tga");
    pattern2.loadImage("./input/pattern2.tga");
    text.loadImage("./input/text.tga");
    text2.loadImage("./input/text2.tga");
    car.loadImage("./input/car.tga");
    circles.loadImage("./input/circles.tga");
    layer_blue.loadImage("./input/layer_blue.tga");
    layer_green.loadImage("./input/layer_green.tga");
    layer_red.loadImage("./input/layer_red.tga");

    // example files for comparison
    Image example1;
    Image example2;
    Image example3;
    Image example4;
    Image example5;
    Image example6;
    Image example7;
    Image example8_1;
    Image example8_2;
    Image example8_3;
    Image example9;
    Image example10;

    example1.loadImage("./examples/EXAMPLE_part1.tga");
    example2.loadImage("./examples/EXAMPLE_part2.tga");
    example3.loadImage("./examples/EXAMPLE_part3.tga");
    example4.loadImage("./examples/EXAMPLE_part4.tga");
    example5.loadImage("./examples/EXAMPLE_part5.tga");
    example6.loadImage("./examples/EXAMPLE_part6.tga");
    example7.loadImage("./examples/EXAMPLE_part7.tga");
    example8_1.loadImage("./examples/EXAMPLE_part8_r.tga");
    example8_2.loadImage("./examples/EXAMPLE_part8_g.tga");
    example8_3.loadImage("./examples/EXAMPLE_part8_b.tga");
    example9.loadImage("./examples/EXAMPLE_part9.tga");
    example10.loadImage("./examples/EXAMPLE_part10.tga");

    // Part 1: Multiply
    std:: cout << "Part 1: Multiply" << std::endl;
    Image multiply = Multiply(layer1, pattern1);
    multiply.writeImage("./output/part1.tga");
    passed += runTests(example1, multiply);

    //Part 2: Subtract
    std:: cout << "Part 2: Subtract" << std::endl;
    Image subtract = Subtract(car, layer2);
    subtract.writeImage("./output/part2.tga");
    passed += runTests(example2, subtract);

    //Part 3: Multiply laayer1 and pattern 2, then Screen that with text
    std::cout << "Part 3: Multipy and Screen" << std::endl;
    Image multiply2 = Multiply(layer1, pattern2);
    Image screen = Screen(multiply2, text);
    screen.writeImage("./output/part3.tga");
    passed += runTests(example3, screen);

    //Part 4: Multiply layer2 and circles, then subtract with pattern2
    std::cout << "Part 4: Multiply and Subtract" << std::endl;
    Image multiply3 = Multiply(layer2, circles);
    Image subtract2 = Subtract(multiply3, pattern2);
    subtract2.writeImage("./output/part4.tga");
    passed += runTests(example4, subtract2);

    //Part 5: Overlay layer1 and pattern1
    std::cout << "Part 5: Overlay" << std::endl;
    Image overlay = Overlay(pattern1, layer1);
    overlay.writeImage("./output/part5.tga");
    passed += runTests(example5, overlay);

    //Part 6: Add green to car
    std::cout << "Part 6: Add Green" << std::endl;
    Image addGreenCar = addGreen(car);
    addGreenCar.writeImage("./output/part6.tga");
    passed += runTests(example6, addGreenCar);

    //Part 7: Multiply the red channel in car.tga by 4, and scale the  blue channel to 0, then write the result to part7.tga
    std::cout << "Part 7: Multiply Red and Scale Blue" << std::endl;
    Image scaleRedCar = scaleRed(car);
    scaleRedCar.writeImage("./output/part7.tga");
    passed += runTests(example7, scaleRedCar);

    //Part 8: Load car.tga and split the color channels into three separate images. Write the three images to part8_blue.tga, part8_green.tga, and part8_red.tga
    std::cout << "Part 8: Split Channels" << std::endl;
    Image splitRed = splitChannels("red", car);
    Image splitGreen = splitChannels("green", car);
    Image splitBlue = splitChannels("blue", car);

    splitRed.writeImage("./output/part8_red.tga");
    splitGreen.writeImage("./output/part8_green.tga");
    splitBlue.writeImage("./output/part8_blue.tga");
    passed += runTests(example8_1, splitRed);
    passed += runTests(example8_2, splitGreen);
    passed += runTests(example8_3, splitBlue);

    //Part 9: Load layer_blue.tga, layer_green.tga, and layer_red.tga and combine them into a single image. Write the result to part9.tga
    std::cout << "Part 9: Combine Channels" << std::endl;
    Image combine = combineChannels(layer_red, layer_green, layer_blue);
    combine.writeImage("./output/part9.tga");
    passed += runTests(example9, combine);

    // Part 10: Rotate text2.tga 180 degrees and write the result to part10.tga
    std::cout << "Part 10: Rotate" << std::endl;
    Image rotate = Rotate(text2);
    rotate.writeImage("./output/part10.tga");
    passed += runTests(example10, rotate);

    std::cout << "Done" << std::endl;
    std::cout << "Passed " << passed << " out of 12 tests" << std::endl;
    return 0;
}

int main(int argc, char* argv)
{
    // creating a command line interface

    // if no arguments are provided, or if the first and only argument is --help, print the help message
    for (int i = 0; i < argc; i++)
    {
        if (argv[i] == "--help")
        {
            std::cout << "Usage: ./main [OPTION]... [FILE]..." << std::endl;
            std::cout << "Perform image processing operations on a set of images." << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  --help\t\t\tPrint this help message" << std::endl;
            std::cout << "  --multiply [FILE] [FILE]\tMultiply two images" << std::endl;
            std::cout << "  --subtract [FILE] [FILE]\tSubtract two images" << std::endl;
            std::cout << "  --screen [FILE] [FILE]\tScreen two images" << std::endl;
            std::cout << "  --overlay [FILE] [FILE]\tOverlay two images" << std::endl;
            std::cout << "  --addGreen [FILE]\t\tAdd green to an image" << std::endl;
            std::cout << "  --scaleRed [FILE]\t\tScale red in an image" << std::endl;
            std::cout << "  --splitChannels [FILE]\tSplit channels in an image" << std::endl;
            std::cout << "  --combineChannels [FILE] [FILE] [FILE]\tCombine channels in an image" << std::endl;
            std::cout << "  --rotate [FILE]\t\tRotate an image" << std::endl;
            return 0;
        }
    }
    

}