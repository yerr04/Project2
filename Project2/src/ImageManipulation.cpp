#include "ImageManipulation.h"
#include "Image.h"
#include <cmath>
#include <fstream>

using namespace std;

// normalize the channel value to a float between 0 and 1
float normalize(unsigned char channel)
{
    return channel / 255.0f;
} 

//clamp
float clamp(float value)
{
    if (value < 0)
    {
        return 0;
    }
    else if (value > 255)
    {
        return 255;
    }
    else
    {
        return value;
    }
}

float scale(float toScale)
{
    toScale += 0.5f;
    return toScale;
}

// Multiply
Image Multiply(Image &image1, Image &image2)
{
    Image image3;
    Image::Header header = image1.getHeader();

    image3.setHeader(header);

    image1.setUnsignedints();
    image2.setUnsignedints();

    vector<Image::Pixel> pixels1 = image1.getPixels();
    vector<Image::Pixel> pixels2 = image2.getPixels();
    vector<Image::Pixel> pixels3;

    for (unsigned int i = 0; i < pixels1.size(); i++)
    {
        Image::Pixel pixel3;

        unsigned int blueInt = (unsigned int)(scale(pixels1[i].blue * pixels2[i].blue / 255.0f));
        unsigned char blue = image1.itoc(blueInt);
        pixel3.blueChar = blue;

        unsigned int greenInt = (unsigned int)(scale(pixels1[i].green * pixels2[i].green / 255.0f));
        unsigned char green = image1.itoc(greenInt);
        pixel3.greenChar = green;

        unsigned int redInt = (unsigned int)(scale(pixels1[i].red * pixels2[i].red / 255.0f));
        unsigned char red = image1.itoc(redInt);
        pixel3.redChar = red;

        pixels3.push_back(pixel3);
    }
    image3.setPixels(pixels3);

    return image3;
}

Image Subtract(Image &image1, Image &image2)
{
    Image image3;
    Image::Header header = image1.getHeader();

    image3.setHeader(header);

    image1.setUnsignedints();
    image2.setUnsignedints();

    vector<Image::Pixel> pixels1 = image1.getPixels();
    vector<Image::Pixel> pixels2 = image2.getPixels();
    vector<Image::Pixel> pixels3;

    int final;

    for (int i = 0; i < pixels1.size(); i++)
    {
        Image::Pixel pixel3;

        final = pixels1[i].red - pixels2[i].red;
        unsigned char red = image1.itoc(clamp(final));
        pixel3.redChar = red;

        final = pixels1[i].green - pixels2[i].green;
        unsigned char green = image1.itoc(clamp(final));
        pixel3.greenChar = green;

        final = pixels1[i].blue - pixels2[i].blue;
        unsigned char blue = image1.itoc(clamp(final));
        pixel3.blueChar = blue;

        pixels3.push_back(pixel3);
    }
    image3.setPixels(pixels3);
    return image3;
}



Image Screen(Image &image1, Image &image2)
{
    Image image3;
    Image::Header header = image1.getHeader();

    image3.setHeader(header);

    vector<Image::Pixel> pixels1 = image1.getPixels();
    vector<Image::Pixel> pixels2 = image2.getPixels();
    vector<Image::Pixel> pixels3;

    for (int i = 0; i < pixels1.size(); i++)
    {
        Image::Pixel pixel1 = pixels1[i];
        Image::Pixel pixel2 = pixels2[i];
        Image::Pixel pixel3;

        pixel3.redChar = image1.itoc(static_cast<uint8_t>((1 - (1 - normalize(pixel1.redChar)) * (1 - normalize(pixel2.redChar))) * 255) + 0.5f);
        pixel3.greenChar = image1.itoc(static_cast<uint8_t>((1 - (1 - normalize(pixel1.greenChar)) * (1 - normalize(pixel2.greenChar))) * 255) + 0.5f);
        pixel3.blueChar = image1.itoc(static_cast<uint8_t>((1 - (1 - normalize(pixel1.blueChar)) * (1 - normalize(pixel2.blueChar))) * 255) + 0.5f);

        pixels3.push_back(pixel3);
    }
    image3.setPixels(pixels3);
    return image3;
}

Image Overlay(Image &image1, Image &image2)
{
    Image image3;
    Image::Header header = image1.getHeader();

    image3.setHeader(header);

    vector<Image::Pixel> pixels1 = image1.getPixels();
    vector<Image::Pixel> pixels2 = image2.getPixels();
    vector<Image::Pixel> pixels3;

    for (int i = 0; i < pixels1.size(); i++)
    {
        Image::Pixel pixel1 = pixels1[i];
        Image::Pixel pixel2 = pixels2[i];
        Image::Pixel pixel3;

        if (normalize(pixel1.redChar) < 0.5)
        {
            pixel3.redChar = image1.itoc(static_cast<uint8_t>((2 * normalize(pixel1.redChar) * normalize(pixel2.redChar)) * 255) + 0.5f);
        }
        else
        {
            pixel3.redChar = image1.itoc(static_cast<uint8_t>((1 - 2 * (1 - normalize(pixel1.redChar)) * (1 - normalize(pixel2.redChar))) * 255) + 0.5f);
        }

        if (normalize(pixel1.greenChar) < 0.5)
        {
            pixel3.greenChar = image1.itoc(static_cast<uint8_t>((2 * normalize(pixel1.greenChar) * normalize(pixel2.greenChar)) * 255) + 0.5f);
        }
        else
        {
            pixel3.greenChar = image1.itoc(static_cast<uint8_t>((1 - 2 * (1 - normalize(pixel1.greenChar)) * (1 - normalize(pixel2.greenChar))) * 255) + 0.5f);
        }

        if (normalize(pixel1.blueChar) < 0.5)
        {
            pixel3.blueChar = image1.itoc(static_cast<uint8_t>((2 * normalize(pixel1.blueChar) * normalize(pixel2.blueChar)) * 255) + 0.5f);
        }
        else
        {
            pixel3.blueChar = image1.itoc(static_cast<uint8_t>((1 - 2 * (1 - normalize(pixel1.blueChar)) * (1 - normalize(pixel2.blueChar))) * 255) + 0.5f);
        }

        pixels3.push_back(pixel3);
    }
    image3.setPixels(pixels3);
    return image3;
}

// add 200 to the green channel
Image addColor(Image &image, string color, float amount)
{
    Image image3;
    Image::Header header = image.getHeader();

    image3.setHeader(header);

    vector<Image::Pixel> pixels1 = image.getPixels();
    vector<Image::Pixel> pixels3;

    if (color == "red") {
        for (int i = 0; i < pixels1.size(); i++)
        {
            Image::Pixel pixel1 = pixels1[i];
            Image::Pixel pixel3;

            pixel3.redChar = clamp(pixel1.redChar + amount);
            pixel3.greenChar = pixel1.greenChar;
            pixel3.blueChar = pixel1.blueChar;

            pixels3.push_back(pixel3);
        }
    }
    else if (color == "green") {
        for (int i = 0; i < pixels1.size(); i++)
        {
            Image::Pixel pixel1 = pixels1[i];
            Image::Pixel pixel3;

            pixel3.redChar = pixel1.redChar;
            pixel3.greenChar = clamp(pixel1.greenChar + amount);
            pixel3.blueChar = pixel1.blueChar;

            pixels3.push_back(pixel3);
        }
    }
    else if (color == "blue") {
        for (int i = 0; i < pixels1.size(); i++)
        {
            Image::Pixel pixel1 = pixels1[i];
            Image::Pixel pixel3;

            pixel3.redChar = pixel1.redChar;
            pixel3.greenChar = pixel1.greenChar;
            pixel3.blueChar = clamp(pixel1.blueChar + amount);

            pixels3.push_back(pixel3);
        }
    }
    else {
        cout << "Invalid color" << endl;
    }
    image3.setPixels(pixels3);
    return image3;
}


Image Rotate(Image &image) 
{
    Image image3;
    Image::Header header = image.getHeader();

    image3.setHeader(header);

    vector<Image::Pixel> pixels1 = image.getPixels();
    vector<Image::Pixel> pixels3;

    for (int i = pixels1.size() -1; i >= 0; i--)
    {
        Image::Pixel pixel1 = pixels1[i];
        Image::Pixel pixel3;

        pixel3.redChar = pixel1.redChar;
        pixel3.greenChar = pixel1.greenChar;
        pixel3.blueChar = pixel1.blueChar;

        pixels3.push_back(pixel3);
    }
    image3.setPixels(pixels3);
    return image3;
}

Image splitChannels(string split, Image &image)
{
    Image image3;
    Image::Header header = image.getHeader();

    image3.setHeader(header);

    vector<Image::Pixel> pixels1 = image.getPixels();
    vector<Image::Pixel> pixels3;

    for (int i = 0; i < pixels1.size(); i++)
    {
        unsigned char channel;
        Image::Pixel pixel1 = pixels1[i];
        Image::Pixel pixel3;
        
        if (split == "red")
        {
            channel = pixel1.redChar;
        }
        else if (split == "green")
        {
            channel = pixel1.greenChar;
        }
        else if (split == "blue")
        {
            channel = pixel1.blueChar;
        }

        pixel3.redChar = channel;
        pixel3.greenChar = channel;
        pixel3.blueChar = channel;

        pixels3.push_back(pixel3);
    }
    image3.setPixels(pixels3);
    image3.setUnsignedints();
    return image3;
}

Image scaleColor(Image &image, string color, float amount)
{
    Image image3;
    Image::Header header = image.getHeader();

    image3.setHeader(header);

    vector<Image::Pixel> pixels1 = image.getPixels();
    vector<Image::Pixel> pixels3;

    for (int i = 0; i < pixels1.size(); i++)
    {
        if (color == "red") {
            Image::Pixel pixel1 = pixels1[i];
            Image::Pixel pixel3;

            float red = normalize((float)pixel1.red) * amount;
            unsigned int redInt = (unsigned int)(scale(red * 255));
            redInt = clamp(redInt);
            unsigned char redChar = image3.itoc(redInt);

            pixel3.redChar = redChar;

            pixel3.greenChar = pixel1.greenChar;

            pixel3.blueChar = pixel1.blueChar;

            pixels3.push_back(pixel3);
        }
        else if (color == "green") {
            Image::Pixel pixel1 = pixels1[i];
            Image::Pixel pixel3;

            float green = normalize((float)pixel1.green) * amount;
            unsigned int greenInt = (unsigned int)(scale(green * 255));
            greenInt = clamp(greenInt);
            unsigned char greenChar = image3.itoc(greenInt);

            pixel3.redChar = pixel1.redChar;

            pixel3.greenChar = greenChar;

            pixel3.blueChar = pixel1.blueChar;

            pixels3.push_back(pixel3);
        }
        else if (color == "blue") {
            Image::Pixel pixel1 = pixels1[i];
            Image::Pixel pixel3;

            float blue = normalize((float)pixel1.blue) * amount;
            unsigned int blueInt = (unsigned int)(scale(blue * 255));
            blueInt = clamp(blueInt);
            unsigned char blueChar = image3.itoc(blueInt);

            pixel3.redChar = pixel1.redChar;

            pixel3.greenChar = pixel1.greenChar;

            pixel3.blueChar = blueChar;

            pixels3.push_back(pixel3);
        }
        else {
            cout << "Invalid color" << endl;
        }
    }
    image3.setPixels(pixels3);
    return image3;
}

Image combineChannels(Image &image1, Image &image2, Image &image3)
{
    Image image4;
    Image::Header header = image1.getHeader();

    image4.setHeader(header);

    vector<Image::Pixel> pixels1 = image1.getPixels();
    vector<Image::Pixel> pixels2 = image2.getPixels();
    vector<Image::Pixel> pixels3 = image3.getPixels();
    vector<Image::Pixel> pixels4;

    for (int i = 0; i < pixels1.size(); i++)
    {
        Image::Pixel pixel1 = pixels1[i];
        Image::Pixel pixel2 = pixels2[i];
        Image::Pixel pixel3 = pixels3[i];
        Image::Pixel pixel4;

        pixel4.redChar = pixel1.redChar;
        pixel4.greenChar = pixel2.greenChar;
        pixel4.blueChar = pixel3.blueChar;

        pixels4.push_back(pixel4);
    }
    image4.setPixels(pixels4);
    return image4;
}