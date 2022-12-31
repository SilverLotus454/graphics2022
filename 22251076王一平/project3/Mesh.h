/*###################################################
##  �ļ�: Mesh.h
##  �ļ�˵���� Mesh.cpp��ͷ�ļ������ڵ���fbx��obj������
��ģ���ļ�
#####################################################*/
#pragma once
#ifndef MYMESH_H
#define MYMESH_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;	// OpenGL����ID������ʱ�󶨸�����ID�Ϳ���ʹ�ø�������л���
	string type;		// ���������
	string path;		// ����ͼƬ�ļ���·�������Ǵ��������·������������������бȽ�
};

class Mesh {
public:
	vector<Vertex> vertices;			// ����Ķ��㣨ָ����������Щ�㣩
	vector<unsigned int> indices;		// ���񶥵��������ָ��������Щ��������һ�����һ�����棩
	vector<Texture> textures;			// ���������õ�����ͼ�������ж��֡����������������ͼ�����淴����ͼ
	unsigned int VAO;					// �������VAO������������󣩵�ID����������ʱ�󶨸�VAO���Ϳ��Ե���glDrawArray��DrawElement���л���
	vector<glm::vec3> positions;
	// Ϊ��ǰMesh��vertices��indices��textures��ֵ���������Ͱ�VAO��VBO��EBO�ȣ�����ΪVAO��ֵ��
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, vector<glm::vec3> positions);
	

	// ��Fragment Shader��uniform sampler��ֵ
	void Draw(Shader shader);

private:
	unsigned int VBO, EBO, pVBO;	// pVBO���洢ģ��λ�õ�VBO
	void setupMesh();
	
};
#endif