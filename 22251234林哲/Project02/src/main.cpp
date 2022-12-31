#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <time.h>
#include "camera.h"
#include "shader.h"
#include "mesh.h"
#include "generate_vertices.h"
#include "texture.h"
using namespace std;

// ���ڴ�С
unsigned int SCR_WIDTH = 1440;
unsigned int SCR_HEIGHT = 900;

// ���������
Camera camera(glm::vec3(0.0f, 130.0f, 110.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float NEAR = 0.1f;
float FAR = 400.0f;
bool firstMouse = true;

// ʱ�����
float deltaTime = 0.1f;
float lastFrame = 0.0f;

// �ص�����
void mouse_callback(GLFWwindow* window, double xpos, double ypos);          // ����ƶ�
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);   // �������
void processInput(GLFWwindow* window);                                      // ����

// ����״̬ 
bool MOUSEPRESS = false;                                                    // ������״̬
bool MOUSEABLE = false;                                                     // ���״̬

// ���ݵ��Դ����ɫ��
void set_point_light(Shader& blinnphongshader);

int main()
{
    // �������������
    srand(unsigned int(time(NULL)));

    // ��ʼ��glfw����
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // �����豸��Ϣ������Ļ���
    GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(pMonitor);
    SCR_WIDTH = mode->width / 1.2;
    SCR_HEIGHT = mode->height / 1.2;

    // ��������
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FIREWORK", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // �������
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // ����OpenGL����ָ��
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ģ��
    string typeName = "texture_diffuse";
    Sphere sun(50, LoadTextures(typeName, "textures/sun.jpg")), earth(25, LoadTextures(typeName, "textures/earth.bmp")), moon(20, LoadTextures(typeName, "textures/moon.bmp"));

    // ��ɫ��
    Shader DiffuseShader("shader/Diff.vs", "shader/Diff.fs");
    Shader ColorShader("shader/Color.vs", "shader/Color.fs");
    //Shader ColorShader("shader/Diff.vs", "shader/Diff.fs");
    ColorShader.use();
    set_point_light(ColorShader);

    // ������Ȳ���
    glEnable(GL_DEPTH_TEST);
    
    // ��Ⱦѭ��
    while (!glfwWindowShouldClose(window))
    {
        // ������һ֡��Ⱦʱ����Ⱦ
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // ��������
        processInput(window);

        // ������ɫ
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // �ӽǱ任��ͶӰ�任
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, NEAR, FAR);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 45.0f, -110.0f));
        model = glm::scale(model, glm::vec3(50));
        ColorShader.use();
        ColorShader.setMat4("view", view);
        ColorShader.setVec3("viewPos", camera.Position);
        ColorShader.setMat4("projection", projection);
        ColorShader.setMat4("model", model);
        earth.Draw(ColorShader);

        glm::mat4 model1 = glm::translate(glm::mat4(1.0f), glm::vec3(-80.0f, 45.0f, -30.0f));
        model1 = glm::scale(model1, glm::vec3(20));
        ColorShader.setMat4("model", model1);
        moon.Draw(ColorShader);

        DiffuseShader.use();
        DiffuseShader.setMat4("view", view);
        DiffuseShader.setMat4("projection", projection);
        glm::mat4 model2 = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 45.0f, -110.0f));
        model2 = glm::scale(model2, glm::vec3(100));
        DiffuseShader.setMat4("model", model2);
        sun.Draw(DiffuseShader);


        // ��ʾ��Ⱦ���
        glfwSwapBuffers(window);

        // ���ʱ�䣬����״̬
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


// ����ƶ��ص�����
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// �Ŵ���С�ص�����
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

// �жϰ�����ִ����Ӧ����
void processInput(GLFWwindow* window)
{
    // �����ƶ�
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    // ESC �˳�
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // �����
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && MOUSEPRESS == false)
    {
        if (MOUSEABLE)
        {
            glfwSetCursorPosCallback(window, mouse_callback);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            MOUSEABLE = false;
        }
        else
        {
            firstMouse = true;
            glfwSetCursorPosCallback(window, NULL);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            MOUSEABLE = true;
        }
        MOUSEPRESS = true;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        MOUSEPRESS = false;
}

glm::vec3 get_random_position()
{
    //return glm::vec3(-10.0f + 20.0f, 
    //                 45.0f + 60.0f,
    //                 -150.0f + 60.0f);
    return glm::vec3(300.0f, 45.0f, -110.0f);
}

// ���ݵ��Դ����ɫ��
void set_point_light(Shader& blinnphongshader)
{
    string struct_string = "light_list[";
    string color_string = "].Color";
    string pos_string = "].Position";
    string intensity_string = "].intensity";

    const int num_lights = 2;
        
    for (int i = 0; i < num_lights; i++)
    {
        blinnphongshader.setVec3(struct_string + to_string(i) + color_string, glm::vec3(1.0f, 0.8f, 0.1f));
        blinnphongshader.setVec3(struct_string + to_string(i) + pos_string, get_random_position());
        blinnphongshader.setFloat(struct_string + to_string(i) + intensity_string, 20000.0f);
    }
    blinnphongshader.setInt("num_lights", num_lights);
}