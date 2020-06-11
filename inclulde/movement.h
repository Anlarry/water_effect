#ifndef MOVEMENT_H
#define MOVEMENT_H
#endif

#include<shapeObj.h>
#include<Python.h>
#include<pylifecycle.h>

class SimplePendulum: public Shape
{

public:
    SimplePendulum(PF origin, float radius, float theta) :
        ball(0.05, origin.first-radius*sin(theta), origin.second-radius*cos(theta), 100),
        line(origin.first, origin.second, 0, ball.getOrigin().first, ball.getOrigin().second, 0)
    {
        // ball = Circle(0.05, origin.first-radius*sin(theta), origin.second+radius*cos(theta), 100);
        // line = Line(origin.first, origin.second, 0, ball.getOrigin().first, ball.getOrigin().second, 0);
        this->theta = theta;
        this->radius = radius;
        float a = 9.8 * sin(theta);
        // this->alpha = - a / radius;
        this->w = 0;
        this->delta = 0;
        getState();
    }
    float getTheta(){
        return this->theta;
    }
    int getStateSize(){
        return this->stateSize;
    }
    float  getState(int idx){
        return this->state[idx];
    }
    // void update(){
    //     // float h = 0.1;
    //     // float nv = RK4(this->theta, this->w, h, this->alpha);
    //     // this->theta += h;
    //     // this->w += nv;
    //     // this->delta += h;
        
    // }
    void draw(){
        ball.draw();
        line.draw();
    }
    ~SimplePendulum(){
        free(state);
    }
protected:
    Circle ball;
    Line line;
    float theta;
    float w;
    // float alpha; 
    float radius;
    float delta;
    float *state;
    int stateSize;
    void getState(){
        // Py_SetPythonHome((wchar_t*)"C:/Users/29444/AppData/Local/Programs/Python/Python38");
        Py_SetPythonHome(L"C:/Users/29444/AppData/Local/Programs/Python/Python38");
        Py_Initialize();
        if(!Py_IsInitialized()){
            printf("init python error");
        }
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append(\"./src\")");
        PyObject *pyFun = NULL;
        PyObject *pyModule = NULL;
        pyModule = PyImport_ImportModule("Diff");
        if(pyModule == NULL){
            printf("not found file");
        }
        pyFun = PyObject_GetAttrString(pyModule, "Pendulum");
        PyObject *args = Py_BuildValue("(fff)", this->radius, this->theta, this->w);
        PyObject* pValue = PyObject_CallObject(pyFun, args);
        int size = PyList_Size(pValue);
        printf("%d\n",  size);
        this->stateSize = size;
        state = (float*)malloc(size*sizeof(float));
        for(int i = 0; i < size; i++){
            PyObject  *item = PyList_GetItem(pValue, i);
            float cfloat = PyFloat_AsDouble(item);
            state[i] = cfloat;
        }
        Py_Finalize();
    }
};



