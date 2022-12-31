#pragma once
#include <iostream>
#include <glad/glad.h>
#include "StringUtil.h"

//��ɫ��
class Shader
{
public:
	Shader(std::istream* source, GLuint type);
	~Shader();
	//��ȡ������
	std::istream* getSource() const;
	//��ȡ����
	GLuint getType() const;
	//��ȡ��ɫ��id
	GLuint getId() const;
	//������ɫ��
	bool compile();

private:
	//������
	std::istream* source;
	//����
	const GLuint type;
	//id����OpenGL���ɣ��ڱ���ǰ�����ã�
	GLuint id;
};
