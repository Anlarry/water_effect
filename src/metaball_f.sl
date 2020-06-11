#version 330 core

// out vec4 FragColor;
uniform vec4 metaballs[100];

void main(){
    float x = gl_FragCoord.x;
    float y = gl_FragCoord.y;
    for(int i = 0; i < 100; i++)
    {
        vec4 mb = metaballs[i];
        if(mb.a < 0.1) continue;
        else {
            float dx = mb.x - x;
            float dy = mb.y - y;
            float r = mb.z;
            if(dx * dx + dy*dy < r*r) {
                gl_FragColor = vec4(0, 0, 0.7, 0.6);
                return ;
            }
            //else 
                //discard;
                //FragColor = vec4(0, 0, 0, 1.0);
        }
    }
    discard;
    //gl_FragColor = vec4(0, 0, 0, 1.0);
}