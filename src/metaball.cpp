#include<metaball.h>
#include<vector>
#include<time.h>
using namespace std;

#define random(x) rand()%x

#define Width 600
#define Height 600

float MetaBall::acceleration = -0.000004;

MetaBall::MetaBall(int index, float x, float y, float velocity_x, float velocity_y) :
    index(index), postion({x, y}), velocity({velocity_x, velocity_y})
{
}

void MetaBall::update(vector<float> &stateArray)
{
    // this->postion.first += 0.01;
    // if(this->postion.first > 1) this->postion.first -= 1;
    this->postion.first += velocity.first;
    this->postion.second += velocity.second;
    this->velocity.second += acceleration;

    int idx = index * 4;
    stateArray[idx] = (this->postion.first+1)*Width/2;
    stateArray[idx+1] = (this->postion.second+1)*Height/2;
    // cout << idx << " " << postion.first << " " << postion.second << "\n";
}

pair<float, float> MetaBall::getPostion(){
    return postion;
}

pair<float, float> MetaBall::getVelocity(){
    return velocity;
}

MetaBallArray::MetaBallArray(const string &vertexFile, const string &fragmenFile)
{
    vector<float> vertex = vector<float>({
        -1, -1, 0,
        -1,  1, 0,     // 
         1, -1, 0,     // 
         -1, 1, 0,
         1, -1, 0,
         1,  1, 0
    });
    shader = new Shader(vertexFile, fragmenFile);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex.size(), &vertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    stateArray.resize(100*4);
    for(int i = 0; i < 100; i++)
        freeMetaball.push(i);
}

void MetaBallArray::update(Water* water)
{
    // for(int i = 0; i < metaballs.size(); i++)
    //     metaballs[i].update(stateArray); 
    for(auto it = metaballs.begin(); it!=metaballs.end(); )
    {
        it->update(stateArray);
        auto pos = it->getPostion();
        int water_idx;
        float water_height = water->getHightAndIndex(pos.second, &water_idx);
        if(pos.second < water_height && it->getVelocity().second < 0){
            freeMetaball.push(it->index);
            stateArray[it->index*4+3] = 0;
            it = metaballs.erase(it);
        }
        else {
            it++;
        }
    }
    // cout << metaballs.size() << "\n";
}

void MetaBallArray::addMetaball(float x, float y, float velocity_range, int n)
{
    for(int i = 0; !freeMetaball.empty() and i < n; i++)
    {
        float vx = 1.0*velocity_range*(random(50)-25) / 50;
        float vy = max(0.0, 1.0*(random(50)+50) / 50) * abs(velocity_range);
        int idx = freeMetaball.front(); 
        freeMetaball.pop();
        metaballs.push_back(MetaBall(idx, x, y, vx, vy));
        idx *= 4;
        stateArray[idx] = (x+1)*Width/2;
        stateArray[idx+1] = (y+1)*Height/2;
        stateArray[idx+2] = random(5)+3;
        stateArray[idx+3] = 0.6;
    }
    // stateArray[0] = 150;
    // stateArray[1] = 300;
    // stateArray[2] = 2;
    // stateArray[3] = 1;
}

void MetaBallArray::draw(){
    this->shader->use();
    glUniform4fv(shader->Location("metaballs"), 100, &stateArray[0]);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}