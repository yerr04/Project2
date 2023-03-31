#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Image.h"

using namespace std;

float normalize(unsigned char channel);

float clamp(float value);

float scale (float toScale);

Image Multiply(Image &image1, Image &image2);

Image Subtract(Image &image1, Image &image2);

Image Addition(Image &image1, Image &image2);

Image Screen(Image &image1, Image &image2);

Image Overlay(Image &image1, Image &image2);

Image addGreen(Image &image);

Image scaleRed(Image &image);

Image Rotate(Image &image);

Image splitChannels(string split, Image &image);

Image combineChannels(Image &image1, Image &image2, Image &image3);






