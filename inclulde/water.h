#ifndef WATER_H
#define WATER_H

#include<vector>
#include<queue>
#include<shapeObj.h>
#include<GLFW/glfw3.h>
#include<list>
using namespace std;

class Water;

class Spring
{
public:
    static float init_height;
    float height, velocity;
    void update();
    Spring();
};

class Water
{
private:
    vector<Spring> springs;
    Triangle triangle;
    void drawTrapezoid(Shader *shader, int left_idx, float x, float y);
public:
    static float dampen;
    static float acceleration;
    static float spread;
    Water(int spring_number);
    float getHightAndIndex(float x, int *index);
    void addWave(int idx, float velocity);
    void update();
    void draw(Shader *shader, float x, float y);
    ~Water();
};




#endif