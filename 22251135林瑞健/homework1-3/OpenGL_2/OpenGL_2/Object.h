#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Vertex.h"
#include "Plane.h"
#include "Shader.h"
#include "Texture.h"

class Plane;

// ����
class Object
{
public:
	Object();
	~Object();
	// ��obj�ļ��м���Object
	int loadObject(std::istream& input);
	// ִ�л���ǰ��׼������
	void draw();
	// ��ӵ�
	int addVertex(const Vertex& vertex);
	// ���ƽ��
	int addPlane(const Plane& plane);
	// ɾ����
	int deleteVertex(const Vertex& vertex);
	// ɾ��ƽ��
	int deletePlane(const Plane& plane);
	// ɾ����
	int deleteVertex(const int position);
	// ɾ��ƽ��
	int deletePlane(const int position);
	// ��ӵ㷨����
	int addVertexNormal(const glm::vec3& normal);
	// ɾ���㷨����
	int deleteVertexNormal(const int position);
	// ��յ㷨����
	void clearVertexNormal();
	// �����ɫ��
	void addShader(Shader& shader);
	// �����ɫ��
	void clearShaders();
	// �����
	void clearVertices();
	// ���ƽ��
	void clearPlanes();
	// �����ͼ
	void addTexture(Texture& texture);
	// �����ͼ
	void clearTextures();
	// ��ȡ��ǰ״̬�µı任����
	const glm::mat4& getTransformation() const;
	// ���ñ任����
	void resetTranslation();
	// ��ȡShaderProgram
	GLuint getShaderProgram() const;
	// ��ȡ������ͼ
	const std::vector<Texture>& getTextures();
	// ��ȡVAO
	GLuint getVAO() const;
	// ��ȡ����ԭ������������ϵ�е�����
	glm::vec3 getPosition();
	// ��ȡ���������������ϵ��������ת���ĽǶ�
	glm::vec3 getSelfRotation();
	// ƽ�ƣ��������������ϵ��
	void translate(const glm::vec3& direction);
	// ��ת���������������ϵ��
	void selfRotate(const float degree, const glm::vec3& axis);
	// ��ת���������������ϵ�����ݲ�����
	void rotate(const float degree, const glm::vec3& axis);
	// ��ȡ���е�
	const std::vector<Vertex>& getVertices() const;
	// ��ȡ����ƽ��
	const std::vector<Plane>& getPlanes() const;
	// ��ȡ���е㷨����
	const std::vector<glm::vec3>& getVertexNormals() const;
	const static int OPERATION_SUSSESS = 1;
	const static int OPERATION_FAILURE = 0;
	const static int UNDEFINED = UINT_MAX;

private:
	// ����
	std::vector<Vertex> vertices;
	// ƽ��
	std::vector<Plane> planes;
	// ��ɫ��
	std::vector<Shader> shaders;
	// ��ͼ
	std::vector<Texture> textures;
	// �㷨����
	std::vector<glm::vec3> vertexNormals;
	// �任����
	glm::mat4 transformation;
	// ��ɫ������
	GLuint shaderProgram;
	// Vertex Array Object
	GLuint vao;
	// ģ�͵ĵ�ǰλ��
	glm::vec3 position;
	// ģ�͵���ת��������x��y��z�ᣩ
	glm::vec3 rotation;
	// ��ʼ����ɫ��
	void initShaders();
	// ��ʼ����ɫ������
	void initShaderProgram();
	// ��ʼ��VAO
	void initVAO();
	// ��ʼ����ͼ
	void initTextures();
	// ���ɶ�������
	void prepareVertices(std::vector<GLfloat>& verticesInfo);
	// ���ɶ�����������
	void prepareVertexIndices(std::vector<GLint>& vertexIndices);
	// ���ɶ��㷨��������
	void prepareVertexNormals(std::vector<GLfloat>& vertexNormalInfo);
	// ���ɶ��㷨������������
	void prepareVertexNormalIndices(std::vector<GLint>& vertexNormalIndices);
};
#endif // !OBJECT_H