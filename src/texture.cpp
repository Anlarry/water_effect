#include<texture.h>
#include<stdio.h>
Texture::Texture(const string &src, bool alpha):
    alpha(alpha)
{
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(src.c_str(), &width, &height, &nrChannel, 0);
    printf("%d\n", nrChannel);
    glGenTextures(1, &Id);
    glBindTexture(GL_TEXTURE_2D, Id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if(data){
        // ???? Bug here
        glTexImage2D(GL_TEXTURE_2D, 0, alpha ?  GL_RGBA : GL_RGB, width, height, 0, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE ,data);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,data);
        
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("fail to load texture\n");
    }
    stbi_image_free(data);

}

void Texture::Bind(){
    glBindTexture(GL_TEXTURE_2D, Id);
}

unsigned int Texture::textureId(){
    return this->Id;
}