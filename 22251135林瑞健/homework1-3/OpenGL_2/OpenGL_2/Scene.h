#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>
#include <functional>
#include <vector>

#include "Object.h"
#include "Camera.h"

class Object;

// �����ص�����
typedef std::function<void(GLFWwindow*)> OnKeyDown;
// ���ص�����
typedef std::function<void(GLFWwindow*)> OnMouseAction;
// ��Ⱦ�ص�����
typedef std::function<void(GLFWwindow* window)> OnRender;

// ��̨
class Scene
{
public:
	// ͶӰ����Projection��
	glm::mat4 perspective;
	// ��ȡʵ��
	static Scene& getInstance();
	// ��ʼ��
	int init() const;
	// ��������
	int createWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	// ��ʼ��Ⱦ
	void start() const;
	// ��Ӱ����ص�����
	void addOnKeyDown(const OnKeyDown& onKeyDown);
	// �����Ⱦ�ص�����
	void addOnRender(const OnRender& onRender);
	// ������ص�����
	void addOnMouseAction(const OnMouseAction& onMouseAction);
	// ��������ص�����
	void clearOnKeyDown();
	// �����Ⱦ�ص�����
	void clearOnRender();
	// ������ص�����
	void clearOnMouseAction();
	// �������
	void addObject(Object* object);
	// �������
	void clearObject();
	void setCamera(Camera& camera);
	Camera& getCamera();
	const static int OPERATION_SUCCESS = 1;
	const static int OPERATION_FAILURE = -1;
	~Scene();

private:
	static Scene* instance;
	Camera camera;
	GLFWwindow* window;
	std::vector<OnKeyDown> onKeyDowns;
	std::vector<OnRender> onRenders;
	std::vector<Object*> objects;
	std::vector<OnMouseAction> onMouseActions;
	Scene();
};



#endif // !SCENE_H
