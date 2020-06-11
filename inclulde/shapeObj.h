#ifndef SHAPEOBJ_H
#define SHAPEOBJ_H


#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<math.h>
#include<tuple>
#include<vector>
#include<shader.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

using  namespace std;

#define PF pair<float,float>
// static const float PI = acos(-1.0);
extern const float PI;
#define uint unsigned int
#define tuple_3f tuple<float, float, float>

class Shape{
public:
    virtual void draw()=0;
};


class Circle : public Shape
{
protected:
    /* data */
    float radius;
    PF origin;
    float *pts;
    uint *idx;
    int triangleNumber;

    uint VAO, VBO, EBO;
public:
    
    Circle(float radius, float x, float y, int n){
        this->radius = radius;
        this->origin = {x, y};
        this->triangleNumber = n;
        pts = (float*)malloc((1+n)*3*sizeof(float));
        pts[0] = x;
        pts[1] = y;
        pts[2] = 0;
        for(int i = 3, k = 0; k < n; k++, i+=3 ){
            pts[i] = x + radius * cos(2.0*PI*k/n);
            pts[i+1] = y + radius * sin(2.0*PI*k/n);
            pts[i+2] = 0;
        }
        idx = (uint*)malloc(n*3*sizeof(uint));
        for(int i = 0, k = 0; k < n; k++, i+=3){
            idx[i] = 0;
            idx[i+1] = k+1;
            idx[i+2] = k + 2 > n ? 1 : k+2;
        }

        // debug
        // for(int i = 0, k = 0; k < n+1; i+=3, k++){
        //     printf("%.2lf %.2lf %.2lf\n", pts[i], pts[i+1], pts[i+2]);
        // }
        // puts("");
        // for(int i = 0, k = 0; k < n; i+=3, k++){
        //     printf("%d %d %d\n", idx[i], idx[i+1], idx[i+2]);
        // }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, (1+n)*3*sizeof(float), this->pts, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, n*3*sizeof(uint), idx, GL_STATIC_DRAW);
        glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    uint getVAO(){
        return this->VAO;
    }
    float getRadius(){
        return this->radius;
    }
    PF getOrigin(){
        return this->origin;
    }
    void draw(){
        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, 3*this->triangleNumber, GL_UNSIGNED_INT, 0);
    }
    ~Circle(){
        free(this->pts);
        free(this->idx);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};

class Line : public Shape
{
protected:
    float pts[6];
    uint VAO, VBO;
public:
    uint getVAO(){
        return VAO;
    }
    Line(float x1, float y1, float z1, float x2, float y2, float z2){
        pts[0] = x1;
        pts[1] = y1;
        pts[2] = z1;
        pts[3] = x2;
        pts[4] = y2;
        pts[5] = z2;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), this->pts, GL_STATIC_DRAW);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, n*3*sizeof(uint), idx, GL_STATIC_DRAW);
        glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }    
    void draw(){
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_LINES, 0, 2);
    }
};

class Triangle
{
public:
    uint VAO, VBO;
    vector<float> vertex;
    Triangle(){
        vertex = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex.size(), &vertex[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);
    }
    void draw(Shader *shader, const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &C){
        glm::mat4 model = glm::mat4(1.0f);
        // for(int i = 0; i < 3; i++){
        //     model[i][0] = A[i];
        //     model[i][1] = B[i];
        //     model[i][2] = C[i];
        // }
        // model[0][3] = 0.4;
        // model = glm::translate(model, glm::vec3(0.2,  0, 0));

        // model[0][3] = 0.1;
        // for(int i = 0; i < 4; i++){
        //     for(int j = 0; j < 4; j++)
        //         cout << model[i][j] << " ";
        //     cout << "\n";
        // }
        model[0] = glm::vec4(A, 0);
        model[1] = glm::vec4(B, 0);
        model[2] = glm::vec4(C, 0);
        glUniformMatrix4fv(shader->Location("model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};


class Object
{
public:
    Object();
    ~Object();
};
#endif