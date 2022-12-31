#pragma once

#include<iostream>
#include<vector>
#include<gl/freeglut.h>
#include<gl/glext.h>
#include<gl/glut.h>
#include <stdlib.h> 
#include <time.h>  

using namespace std;



const int SKYBOX_NUM = 7;

#define MAP_W 32
#define MAP_SCANL 16

class Skybox {
private:
	GLuint skytextureNum[SKYBOX_NUM];
	vector<string> skypath;
	GLuint treetextureNum[SKYBOX_NUM];
	vector<string> treepath;
	//�趨������ͼ�Ĵ�С
	GLint width;	//��ͼƬ��С���
	GLint height;	//��ͼƬ��С���

	GLbyte*		g_imageData;		//���θ߶���Ϣ
	float		g_terrain[MAP_W*MAP_W][3];
	GLuint		g_index[MAP_W*MAP_W * 2];
	float		g_texcoord[MAP_W*MAP_W][2];
	

	
public:
	Skybox();
	~Skybox();

	//������
	void loadTexImages();

	//����պ�
	void drawSkyBox();

	//������
	void InitTerrain();
	void drawLand();

	//�õ��ض���ĵ��θ߶�
	float getHeight(float x,float z);

	//����ľ
	void drawTrees(float treex[],float treez[],int num,float n[],int treenum[]);

	//�ƶ���պ�
	void moveSkyBox(GLint x,GLint y,GLint z);

	//��bmp
	GLbyte *gltReadBMPBits(const char *szFileName, int *nWidth, int *nHeight);

	//��tga
	GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

	int getTreepathSize();


};

