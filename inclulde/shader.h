#ifndef SHADER_H
#define SHADER_H


#include<stdio.h>
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

class Shader
{
private:
    unsigned int Program;
    string vertexShaderSrc, fragmentShaderSrc;
    // int vertexShader, fragmentShader;
    
    void compile_link(){
        int success;
        char vertexInfo[512], fragmentInfo[512];
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexShaderCode = vertexShaderSrc.c_str();
        const char* fragmentShaderCode = fragmentShaderSrc.c_str();
        glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(vertexShader, 512, NULL, vertexInfo);
            printf("compile vertex shader src error\n");
            printf(" ------Src------ \n");
            cout << vertexShaderSrc << "\n" ;
            printf("%s\n", vertexInfo);
        }

        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentInfo);
            printf("compile fragment shader src error\n");
            printf("%s\n", fragmentInfo);
        }
    
        Program = glCreateProgram();
        glAttachShader(Program, vertexShader);
        glAttachShader(Program, fragmentShader);
        glLinkProgram(Program);
        // int success;
        char info[512];
        glGetProgramiv(Program, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(Program, 512, NULL, info);
            printf("link program error\n");
            printf("%s\n", info);
        } 

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
public:

    Shader(const string &vertexShaderFile, const  string &fragmentShaderFile){
        char buffer[256];
        ifstream vertex(vertexShaderFile), fragment(fragmentShaderFile);
        if(!vertex.is_open()){;
            printf("open vertex shader src file error\n");
        }
        while(!vertex.eof()){
            string t;
            // cin >> t;
            vertex.getline(buffer, 256);
            // t = vertex.get();
            // cout << t ;
            t = buffer ;
            // printf("%s\n", buffer);
            vertexShaderSrc += t + "\n";
        } 
        if(!fragment.is_open()){;
            printf("open fragment shader src file error\n");
        }
        while(!fragment.eof()){
            string t;
            // cin >> t;
            fragment.getline(buffer, 256);
            t = buffer;
            // printf("%s\n", buffer);
            fragmentShaderSrc += t + "\n";
        }
        compile_link();
    };

    void use(){
        glUseProgram(this->Program);
    }
    int getProgram(){
        return this->Program;
    }
    int Location(const string &s){
        return glGetUniformLocation(this->Program, s.c_str());
    }
};
#endif 
