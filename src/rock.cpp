#include<rock.h>
#include<vector>
#include<iostream>
using namespace std;

float Rock::acceleration = -0.000004;
float Rock::acceleration_water = -0.0000002;
float Rock::impact_force = 0.2;

Rock::Rock(float size_x, float size_y, 
        const string &texture_path, 
        const string &vertexFile,
        const string &fragmentFile)
{
    // this->size_ = {sie_x, size_y};
    this->size_ = {size_x, size_y};
    this->velocity = 0;
    shader = new Shader(vertexFile,fragmentFile);
    texture = new Texture(texture_path, 1);
    vector<float> vertex = vector<float>({
        -1, -1, 0,   0, 0,
        -1,  1, 0,   0, 1,
         1, -1, 0,   1, 0,
        -1,  1, 0,   0, 1,
         1, -1, 0,   1, 0,
         1,  1, 0,   1, 1
    });
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex.size(),  &vertex[0],GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    shader->use();
    glUniform1i(shader->Location("texture1"), 0);
}

void Rock::draw(float x, float y)
{
    this->shader->use();
    glActiveTexture(GL_TEXTURE0);
    texture->Bind();
    glBindVertexArray(VAO);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, 0));
    model = glm::scale(model, glm::vec3(size_.first, size_.second, 1));
    glUniformMatrix4fv(shader->Location("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Rock::draw(){
    // cout << postion.first << " " << postion.second << "\n";
    draw(postion.first, postion.second);
}

void Rock::update(Water *water, MetaBallArray* metaballArray)
{
    int idx;
    float water_height = water->getHightAndIndex(postion.first, &idx);
    if(postion.second > water_height) {
        postion.second += velocity;
        velocity += acceleration;
        if(postion.second < water_height) {
            velocity -= Rock::impact_force*velocity;
            water->addWave(idx, -Rock::impact_force*velocity*5);
            metaballArray->addMetaball(postion.first, postion.second, 0.5*abs(velocity), abs(velocity*5000));
            // cout << velocity*5000 << "\n";
        }
    }
    else{
        postion.second += velocity;
        velocity += acceleration_water;
    }
    // cout << water_height << " " << postion.first << " " << postion.second << " " << velocity << "\n";
    // if(postion.second > 1) postion.second =0;
}

void Rock::setPostion(float x, float y)
{
    this->postion = {x, y};
}

bool Rock::dead(){
    return this->postion.second < -1;
}