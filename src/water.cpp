#include<water.h>
#include<glad/glad.h>
#include<iostream>
#include<_Math.h>
#include<tuple>
using namespace std;

#define tuple_3f tuple<float, float, float>
#define DELTA 0.01
#define N 100

#define EPS 1e-6

float Water::dampen = 0.0003;
float Water::acceleration = 0.00002;
float Water::spread = 0.015;
float Spring::init_height = 0.3;

Spring::Spring(){
    this->height = Spring::init_height;
    this->velocity = 0;
}

void Spring::update(){
    float x = -init_height + height;
    height += velocity;
    velocity += - Water::acceleration * x - velocity * Water::dampen;
}

Water::Water(int spring_number)
{
    triangle = Triangle();
    springs.resize(spring_number);
    for(int i = 0; i < springs.size(); i++){
        springs[i] = Spring();
    }
}

void Water::addWave(int idx, float velocity){
    springs[idx].velocity = velocity;
}

void Water::update(){
    for(int i = 0; i < springs.size(); i++){
        springs[i].update();
    }
    for(int j = 0; j < 2; j++){
        for(int i = 0; i < springs.size(); i++){
            if(i > 0){
                float deltaHeight = springs[i].height - springs[i-1].height;
                springs[i-1].velocity += deltaHeight * Water::spread;
            }
            if(i + 1 < springs.size()){
                float deltaHeight = springs[i].height - springs[i+1].height;
                springs[i+1].velocity += deltaHeight * Water::spread;
            }
        }
    }
}

void Water::drawTrapezoid(Shader *shader, int left_idx, float x, float y){
    float width = 2.0f / (springs.size()-1) ;
    triangle.draw(shader, 
        glm::vec3(width * left_idx +x, springs[left_idx].height+y, 0),
        glm::vec3(width * left_idx +x, 0+y, 0),
        glm::vec3(width * (left_idx+1)+x, 0+y, 0)
    );
    triangle.draw(shader, 
        glm::vec3(width * left_idx+x, springs[left_idx].height+y, 0),
        glm::vec3(width*(left_idx+1)+x, springs[left_idx+1].height+y, 0),
        glm::vec3(width * (left_idx+1)+x, 0+y, 0)
    );
}

void Water::draw(Shader *shader, float x,  float y){
    // cout << springs[0].height << " " << springs[0].velocity << "\n";
    for(int i = 0; i+1 < springs.size(); i++){
        drawTrapezoid(shader, i, x, y);
    }
}

float Water::getHightAndIndex(float x, int *index)
{
    x += 1;
    float width = 2.0f / (springs.size()-1);
    int idx = (x + 0.5*width) / width;
    *index = idx;
    return springs[idx].height-1;
}

Water::~Water()
{
}