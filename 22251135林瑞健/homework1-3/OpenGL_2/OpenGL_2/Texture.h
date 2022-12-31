#pragma once
#include <glad/glad.h>
#include <string>

//��ͼ
class Texture
{
public:
	Texture(std::string& source, GLuint wrapS, GLuint wrapT, GLuint minFilter, GLuint magFilter);
	~Texture();
	//��ȡ��ͼ·��
	std::string getSource() const;
	//��ȡs���򳬳���ͼ���귶Χ�Ĵ���ʽ
	GLuint getWrapS() const;
	//��ȡt���򳬳���ͼ���귶Χ�Ĵ���ʽ
	GLuint getWrapT() const;
	//��ȡ��С��ͼ�Ĵ���ʽ
	GLuint getMinFilter() const;
	//��ȡ�Ŵ���ͼ�Ĵ���ʽ
	GLuint getMagFilter() const;
	//��ȡid
	GLuint getId() const;
	//������ͼ
	void loadSource();

private:
	//��ͼ·��
	std::string source;
	//s���򳬳���ͼ���귶Χ�Ĵ���ʽ
	GLuint wrapS;
	//t���򳬳���ͼ���귶Χ�Ĵ���ʽ
	GLuint wrapT;
	//��С��ͼ�Ĵ���ʽ
	GLuint minFilter;
	//�Ŵ���ͼ�Ĵ���ʽ
	GLuint magFilter;
	//id����OpenGL���ɣ��ڱ���ǰ�����ã�
	GLuint id;
};
