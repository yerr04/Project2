#include "Image.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void Image::loadImage(string filename)
{
    ifstream file(filename, ios::binary);
    if (file.is_open())
    {
        file.read(&header.idLength, sizeof(header.idLength));
        file.read(&header.colorMapType, sizeof(header.colorMapType));
        file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.read((char*)&header.xOrigin, sizeof(header.xOrigin));
        file.read((char*)&header.yOrigin, sizeof(header.yOrigin));
        file.read((char*)&header.width, sizeof(header.width));
        file.read((char*)&header.height, sizeof(header.height));
        file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

        int size = header.width * header.height;
        for (int i = 0; i < size; i++)
        {
            file.read((char*)&pixel.blueChar, sizeof(pixel.blueChar));
            file.read((char*)&pixel.greenChar, sizeof(pixel.greenChar));
            file.read((char*)&pixel.redChar, sizeof(pixel.redChar));

            pixel.blue = ctoi(pixel.blueChar);
            pixel.green = ctoi(pixel.greenChar);
            pixel.red = ctoi(pixel.redChar);

            pixels.push_back(pixel);
        }
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
    file.close();
}

void Image::writeImage(string filename) 
{
    ofstream file(filename, ios::binary);
    if (file.is_open())
    {
        file.write(&header.idLength, sizeof(header.idLength));
        file.write(&header.colorMapType, sizeof(header.colorMapType));
        file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        file.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        file.write((char*)&header.width, sizeof(header.width));
        file.write((char*)&header.height, sizeof(header.height));
        file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

        for (int i = 0; i < pixels.size(); i++)
        {
            file.write((char*)&pixels[i].blueChar, 1);
            file.write((char*)&pixels[i].greenChar, 1);
            file.write((char*)&pixels[i].redChar, 1);
        }
    }
    else
    {
        cout << "Unable to open file";
    }
    file.close();
}

unsigned int Image::ctoi(unsigned char c)
{
    return (unsigned int)(c - '\0');
}

unsigned char Image::itoc(unsigned int i)
{
    return (unsigned char)(i + '\0');
}

void Image::setUnsignedints()
{
    for (int i = 0; i < pixels.size(); i++)
    {
        pixels[i].blue = ctoi(pixels[i].blueChar);
        pixels[i].green = ctoi(pixels[i].greenChar);
        pixels[i].red = ctoi(pixels[i].redChar);
    }
}

Image::Header Image::getHeader()
{
    return header;
}

void Image::setHeader(Header &h)
{
    header.idLength = h.idLength;
    header.colorMapType = h.colorMapType;
    header.dataTypeCode = h.dataTypeCode;
    header.colorMapOrigin = h.colorMapOrigin;
    header.colorMapLength = h.colorMapLength;
    header.colorMapDepth = h.colorMapDepth;
    header.xOrigin = h.xOrigin;
    header.yOrigin = h.yOrigin;
    header.width = h.width;
    header.height = h.height;
    header.bitsPerPixel = h.bitsPerPixel;
    header.imageDescriptor = h.imageDescriptor;
}

void Image::setPixels(vector<Pixel> &p)
{
    for (unsigned int i = 0; i < p.size(); i++)
    {
        pixels.push_back(p[i]);
    }
}

vector<Image::Pixel> Image::getPixels()
{
    return pixels;
}

bool Image::operator==(Image &rhs){
    for (unsigned int i = 0; i < pixels.size(); i++){
		if ((pixels[i].blueChar == rhs.pixels[i].blueChar) && (pixels[i].greenChar == rhs.pixels[i].greenChar) && (pixels[i].redChar == rhs.pixels[i].redChar)) {
			return true;
		}
    }
    return false;
}

