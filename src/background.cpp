#include<background.h>

BackGround::BackGround(const string &texture_path, const string &vertexFile, const string &fragmentFile)
{
    shader =  new Shader(vertexFile, fragmentFile);
    texture = new Texture(texture_path, 0) ;
    vertex = vector<float>({
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

void BackGround::draw(){
    this->shader->use();
    glActiveTexture(GL_TEXTURE0);
    texture->Bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}