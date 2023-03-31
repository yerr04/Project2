#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;



class Image
{
public:
struct Pixel
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;

    unsigned char redChar;
    unsigned char greenChar;
    unsigned char blueChar;
};
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    void loadImage(string filename);
    void writeImage(string filename);

    unsigned int ctoi(unsigned char c);
    unsigned char itoc(unsigned int i);
    void setUnsignedints();

    Header getHeader();
    vector<Pixel> getPixels();

    void setHeader(Header &h);
    void setPixels(vector<Pixel> &p);

    bool operator==(Image& rhs);


private:
    Header header;
    vector<Pixel> pixels;
    Pixel pixel;

};
