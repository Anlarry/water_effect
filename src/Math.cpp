// float RK4(float x, float y, float h, float (*fun)(float, float)){
//     float K1 = fun(x, y);
//     float K2 = fun(x+h/2, y+h*K1/2);
//     float K3 = fun(x+h/2, y+h*K2 / 2);
//     float K4 = fun(x+h, y+h*K3);
//     return y+(K1+K2+K3+K4)*h/6;
// }

#include<tuple>
#include<math.h>
#include<iostream>
using namespace std;

#define tuple_3f tuple<float, float, float>

float Pow(float x, int n){
    float res = 1;
    for(int i = 0; i < n; i++)
        res = res * x;
    return res;
}

float distance(float x1, float y1, float z1, 
    float x2, float y2, float z2)
{
    float res = Pow(x1-x2, 2) + Pow(y1-y2, 2) + Pow(z1-z2, 2);
    return sqrt(res);
}

float distance(float x1, float y1, float x2, float y2){
    float res = Pow(x1-x2, 2) + Pow(y1-y2, 2);
    return res;
}

float distance(tuple_3f A, tuple_3f B)
{
    // cout << get<0>(A) << " " << get<1>(A) << " " << get<2>(A) << " \n";
    // cout << get<0>(B) << " " << get<1>(B) << " " << get<2>(B) << " \n";
    float res =  distance(get<0>(A), get<1>(A), get<2>(A),
        get<0>(B), get<1>(B), get<2>(B));
    return res;
}
