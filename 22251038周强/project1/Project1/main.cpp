
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL/SOIL.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"

// ���ڳߴ�
const GLuint WIDTH = 800, HEIGHT = 600;

// ������Ӧ����
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// ���λ��
float lastX = (float)WIDTH / 2.0f;
float lastY = (float)HEIGHT / 2.0f;
bool firstMouse = true;

// ���ڿ���ģ��
GLfloat Angle_X = 0, Angle_Y = 0, Scale = 45; // Angle������ת, Scale����ģ��ǰ��
glm::vec3 Axis_X(1.f, 0.f, 0.f);
glm::vec3 Axis_Y(0.f, 1.f, 0.f);

// ���ڿ����ӽ�
glm::vec3 MyLookAt(0.f, 0.f, -5.f);
GLfloat Yaw, Pitch;
bool isControl = false;

int main()
{
    // ���ڳ�ʼ��
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // ����һ��GLFW���ڶ���
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Project1", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // ���ûص�����
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouseButton_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // ��ʼ��GLEW
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);


    // ������������ɫ��
    Shader ourShader("Shader.vs", "Shader.fs");


    // ������
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ��������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // ��������
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // ���


    // ���ز���������
    GLuint texture;
 
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // ���ò���
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // ���������˲���
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // ���ء�������������mipmaps
    int width, height;
    unsigned char* image = SOIL_load_image("R-C.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    // ѭ����ʾ
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Render
        // �����ɫ����
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ��������
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);


        // ������ɫ��
        ourShader.Use();

        // ����model��view��projection����
        glm::mat4 model(1.f);
        glm::mat4 view(1.f);
        glm::mat4 projection(1.f);
        model = glm::rotate(model, glm::radians((GLfloat)Angle_X), Axis_X);
        model = glm::rotate(model, glm::radians((GLfloat)Angle_Y), Axis_Y);
        view = glm::translate(view, MyLookAt);
        view = glm::rotate(view, glm::radians((GLfloat)Yaw), Axis_Y);
        view = glm::rotate(view, glm::radians((GLfloat)Pitch), Axis_X);
        projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

        // ��ȡ��ɫ���еĲ���������
        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // ����
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    // �ͷ���Դ
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

// ������Ӧ����
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_UP) {
        Angle_X -= 1.f;
    }
    else if (key == GLFW_KEY_DOWN) {
        Angle_X += 1.f;
    }
    else if (key == GLFW_KEY_LEFT) {
        Angle_Y -= 1.f;
    }
    else if (key == GLFW_KEY_RIGHT) {
        Angle_Y += 1.f;
    }

    if (key == GLFW_KEY_W) {
        MyLookAt[1] += 0.1f;
    }
    else if (key == GLFW_KEY_S) {
        MyLookAt[1] -= 0.1f;
    }
    else if (key == GLFW_KEY_A) {
        MyLookAt[0] += 0.1f;
    }
    else if (key == GLFW_KEY_D) {
        MyLookAt[0] -= 0.1f;
    }
}

void mouseButton_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:

            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:

            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            isControl = true;
            break;
        default:
            return;
        }
    else {
        isControl = false;
    }

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    MyLookAt[2] += 0.1f * yoffset;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!isControl) return;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;

    Yaw += xoffset * 0.1;
    Pitch += yoffset * 0.1;
}