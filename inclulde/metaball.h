#ifndef METABALL_H
#define METABALL_H

#include<texture.h>
#include<GLFW/glfw3.h>
#include<list>
#include<shader.h>
#include<vector>
#include<queue>
#include<iostream>
#include<water.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

using namespace std;

class MetaBall
{
private:
    pair<float, float> postion;
    pair<float, float> velocity;
public:
    int index;
    static float acceleration;
    MetaBall(int index,float x, float y, float velocity_x, float velocity_y);
    void update(vector<float> &stateArray);
    pair<float, float> getPostion();
    pair<float,float> getVelocity();
};

class MetaBallArray
{
private:
    Shader* shader;
    unsigned int VAO, VBO;
public:
    vector<float> stateArray;
    list<MetaBall> metaballs;
    queue<int> freeMetaball;
    MetaBallArray(const string &vertexFile,const string &fragmenFile);
    void update(Water *water);
    void addMetaball(float x, float y, float velocity_range, int n);
    void draw();
};


#endif