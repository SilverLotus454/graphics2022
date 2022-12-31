#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	~Camera();
	//�������λ��
	void setEye(glm::vec3 eye);
	//�����������ĵ�
	void setCenter(glm::vec3 center);
	//���ó��ϵķ���
	void setUp(glm::vec3 up);
	//��ȡ���λ��
	glm::vec3 getEye() const;
	//��ȡ�������ĵ�
	glm::vec3 getCenter() const;
	//��ȡ���ϵķ���
	glm::vec3 getUp() const;
	//��ȡ�ӽǾ���
	glm::mat4 getViewMatrix();

private:
	//���λ��
	glm::vec3 eye;
	//�������ĵ�
	glm::vec3 center;
	//���ϵķ���
	glm::vec3 up;
	//�ӽǾ���
	glm::mat4 viewMatrix;
	//�ӽǾ����Ƿ�Ϊ����
	bool updatedView;
};
