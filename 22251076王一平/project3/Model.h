/*###################################################
##  �ļ�: Model.h
##  �ļ�˵���� Model.cpp��ͷ�ļ������ڵ���fbx��obj������
��ģ���ļ�
#####################################################*/
#pragma once
#ifndef MYMODEL_H
#define MYMODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

extern unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model
{
public:
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;				// ģ�Ͱ���������Mesh
	string directory;
	bool gammaCorrection;				
	vector<glm::vec3> positions;		// ģ�͵�λ��

	Model(string const &path, vector<glm::vec3> positions, bool gamma = false);

	Model();
	// ����ģ�������е�Mesh  ����Meshʹ�õĶ���ͬһ��Shaderģ��
	void Draw(Shader shader);

private:
	void loadModel(string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	
	// ��Assimp�����ݽ�����Mesh����
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	
};



#endif