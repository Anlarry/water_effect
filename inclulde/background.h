#ifndef BACKGROUND_H
#define BACKGROUND_H

#include<iostream>
#include<string>
#include<vector>
using namespace std;
// #define uing unsigned int


#include<texture.h>
#include<GLFW/glfw3.h>
#include<shader.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class BackGround
{
private:
    Texture *texture;
    unsigned int VAO, VBO;
    vector<float> vertex;
    Shader *shader;
public:
    BackGround(const string &texture_path,const string &vertexFile, const string &fragmentFile);
    void draw();
};

#endif