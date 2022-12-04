#include "GL\freeglut.h"
#include "GLFW\glfw3.h"
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// ���ô��ڿ�͸�
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw��ʼ��������
	glfwInit();
	// �������ΰ汾�ż�����ģʽ��ֻʹ��openGl���Ӽ���
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��������
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// �������Ļ���
	glfwMakeContextCurrent(window);
	// �����ڴ�С�仯ʱ�����ûص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// ѭ����Ⱦ�����ڲ��ᱻ�رգ�
	while (!glfwWindowShouldClose(window))
	{
		// ��������
		processInput(window);

		// ʹ���Զ������ɫ�����Ļ
		glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
		// �����ɫ����λ
		glClear(GL_COLOR_BUFFER_BIT);

		// ������ɫ����
		glfwSwapBuffers(window);
		// ����Ƿ��д����¼�
		glfwPollEvents();
	}

	// glfwTerminate�����ͷ�֮ǰ�����GLFW��Դ
	glfwTerminate();
	return 0;
}

// ������������
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


// �����ڴ�С�ı�ʱ�Ļص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// �����ӿڣ�ǰ��������Ϊ������С��λ�ã������������Ǵ��ڵĿ�Ⱥ͸߶�
	glViewport(0, 0, width, height);
}


