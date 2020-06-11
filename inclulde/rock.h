#ifndef ROCK_H
#define ROCK_H

#include<texture.h>
#include<GLFW/glfw3.h>
#include<shader.h>
#include<iostream>
#include<water.h>
#include<metaball.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

using namespace std;

class Rock
{
private:
    Texture *texture;
    unsigned int VAO, VBO;
    Shader *shader;
    pair<float, float> size_;
    pair<float, float> postion;
    float velocity;
public:
    static float acceleration;
    static float acceleration_water;
    static float impact_force;
    Rock(float size_x, float size_y, 
        const string &texture_path, 
        const string &vertexFile,
        const string &fragmentFile);
    void draw(float x, float y);
    void draw();
    void update(Water *water, MetaBallArray* metaballArray);
    void setPostion(float x, float y);
    bool dead();
};



#endif