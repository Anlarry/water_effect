#version 330 core

in vec2 TexCoord ;

out vec4 FragColor;

uniform sampler2D texture1;
// uniform sampler2D texture1;
// uniform sampler2D texture2;
// uniform float lifespan;


void main(){
    vec4 textureColor = texture(texture1, TexCoord);
    if(textureColor.a < 0.1)
        discard;
    FragColor = textureColor;
    // FragColor = texture(texture1, TexCoord);
      // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2); 
      // FragColor = vec4(0, 0, 0.65, 1);
}