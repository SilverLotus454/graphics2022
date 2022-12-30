/*################################################################
##  �ļ���Shader.h
##  �ļ�˵���� Shader���ͷ�ļ���Shader��Ĺ��ܰ�����������Vertex Shader
��Fragment Shader��Shader Program��ʹ��Shader Program��ΪShader�е�
uniform��ֵ��
##################################################################*/

#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Shader
{
public:
	// ����ID
	unsigned int programID;
	// ���캯������ȡShaderԴ�벢����Shader Program
	Shader(std::string const vertexPath, std::string const fragmentPath);
	Shader();
	// ʹ��Shader Program
	void use();
	// uniform���ߺ���
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string &name, float value1, float value2, float value3) const;
	void setMat4(const std::string &name, const glm::mat4 &mat);
};

#endif