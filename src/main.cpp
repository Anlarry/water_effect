#include<time.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h> 
#include<stdio.h>
#include<math.h>
// #include<shader.h>
#include<string>
// #include<particle.h>
// #include<texture.h>
#include<myLib.h>
#include<iostream>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define uint unsigned int
using namespace std;

const float PI = acos(-1.0);
float cursor_postion_x;
float cursor_postion_y;
bool mouse_click;
bool mouse_click_right;

const int Width = 600;
const int Height = 600;
string vertexSrc = "src/vertex.sl";
string fragmentSrc = "src/fragment.sl";
list<Rock> rocks;

void buffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window, Water &water){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == 1){
        glfwSetWindowShouldClose(window, 1);
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == 1){
        water.addWave(0, 0.001);
        // auto coord = water.checkPoint(0);
        // water.setPoint(0, get<0>(coord), get<1>(coord)+0.01, get<2>(coord));
        // water.setVelocity(0, 0.01);
    }
    // if(glfwGetKey(window, GLFW_KEY_DOWN) == 1){
        // auto coord = water.checkPoint(0);
        // water.setPoint(0, get<0>(coord), get<1>(coord)-0.01, get<2>(coord));
        // water.setVelocity(0, -10000.0);
    // }
    
}

pair<float, float> cursorPos2coord(float x, float y)
{
    float res_x = 2.0 * x / Width  -1.0;
    y = Height - y;
    float res_y = 2.0 * y / Height - 1.0;
    return {res_x, res_y};
}



void cursor_poscallback(GLFWwindow* window, double x, double y){
    // cout << x << " " << y << "\n";
    cursor_postion_x = x;
    cursor_postion_y = y;
}
void mouse_button_callback(GLFWwindow* window, int button, int action , int mods){
    mouse_click = 0;
    mouse_click_right = 0;
    pair<float, float> coord = cursorPos2coord(cursor_postion_x, cursor_postion_y);
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        mouse_click = 1;
        rocks.push_back(Rock(0.05, 0.05, "src\\rock.png", "src\\rock_v.sl", "src\\rock_f.sl"));
        auto it = rocks.end(); it--;
        it->setPostion(coord.first,coord.second);
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        mouse_click_right = 1;

    }
        // cout << "click" << "\n";
}



int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(Width, Height, "My window", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_poscallback);
    glfwSetFramebufferSizeCallback(window, buffer_size_callback);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("init glad error");
        return -1;
    }
    srand((int)time(0));
    BackGround background = BackGround("src\\sky.png", "src\\background_v.sl", 
        "src\\background_f.sl");

    MetaBallArray metaballArray = MetaBallArray("src\\metaball_v.sl", "src\\metaball_f.sl");
    // metaballArray.addMetaball(0, 0, 0.0005, 10);
    // Rock rock = Rock(0.05, 0.05, "src\\rock.png", "src\\rock_v.sl", "src\\rock_f.sl");
    // rock.setPostion(0, 0);
    Shader shader = Shader(vertexSrc, fragmentSrc);
    // Texture texture = Texture("src\\sky.png", 0);

    shader.use();
    Water water = Water(200);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Triangle triangle = Triangle();
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.5, -0.5, 0));
    glUniformMatrix4fv(shader.Location("model"), 1, GL_FALSE, glm::value_ptr(model));

    while (!glfwWindowShouldClose(window))
    {
        processInput(window, water);
        pair<float, float> coord = cursorPos2coord(cursor_postion_x, cursor_postion_y);
        int idx;
        float height = water.getHightAndIndex(coord.first, &idx);
        if(mouse_click_right) water.addWave(idx, 0.001);

        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        background.draw();

        // rock.draw(coord.first, coord.second);
        // rock.draw();
        for(auto it = rocks.begin(); it != rocks.end(); it++)
            it->draw();

        shader.use();
        water.draw(&shader, -1, -1);
        
        metaballArray.draw();

        // ---------------- UPDADE -------------

        // rock.update(&water);
        for(auto it = rocks.begin(); it != rocks.end(); ){
            it->update(&water, &metaballArray);
            if(it->dead()){
                it = rocks.erase(it);
            }
            else it++;
        }
        water.update();
        metaballArray.update(&water);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        // _sleep(50);   
        // glDisable(GL_BLEND);
    }

    // glDeleteVertexArrays(1 , &VAO);
    // glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0; 

}