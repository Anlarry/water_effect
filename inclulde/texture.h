#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<stb_image.h>
#include<GLFW/glfw3.h>
#include<iostream>
using namespace std;


class Texture{
public:
    Texture(const string &src, bool alpha);
    unsigned int textureId();
    void Bind();
protected:
    int nrChannel, width,  height;
    unsigned char *data;
    unsigned int Id;
    bool alpha;
};

#endif