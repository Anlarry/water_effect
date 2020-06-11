#ifndef _MATH_H
#define _MATH_H

#include<tuple>
#include<math.h>
using namespace std;

#define tuple_3f tuple<float, float, float>

extern float Pow(float x, int n);
extern float distance(float x1, float y1, float z1, 
    float x2, float y2, float z2);
extern float distance(tuple_3f A, tuple_3f B);
extern float distance(float x1, float y1, float x2, float y2);

// float Pow(float x, int n){
//     float res = 1;
//     for(int i = 0; i < n; i++)
//         res = res * x;
//     return res;
// }

// float distance(float x1, float y1, float z1, 
//     float x2, float y2, float z2)
// {
//     float res = Pow(x1-x2, 2) + Pow(y1-y2, 2) + Pow(z1-z2, 2);
//     return sqrt(res);
// }

// float distance(tuple_3f A, tuple_3f B)
// {
//     return distance(get<0>(A), get<1>(A), get<2>(A),
//         get<0>(B), get<1>(B), get<2>(B));
// }

#endif