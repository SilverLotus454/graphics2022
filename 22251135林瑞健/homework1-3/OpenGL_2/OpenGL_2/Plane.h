#ifndef PLANE_H
#define PLANE_H

#include <glad/glad.h>
#include <vector>
#include <climits>
#include "Object.h"

class Object;

// ƽ��
class Plane
{
public:
	Plane();
	~Plane();
	// ƽ�������
	class Data
	{
	public:
		Data(const Plane& plane);
		Data(const Plane& plane, const GLint vertexIndex, const GLint vertexTextureIndex, const GLint normalVectorIndex);
		~Data();
		// ���ö�������
		int setVertexIndex(const GLint index);
		// ���ö�����������
		int setVertexTextureIndex(const GLint index);
		// ���ö��㷨��������
		int setNormalVectorIndex(const GLint index);
		// ��ȡ��������
		GLint getVertexIndex() const;
		// ���ö�����������
		GLint getVertexTextureIndex() const;
		// ���ö��㷨��������
		GLint getNormalVectorIndex() const;
		const static GLint UNDEFINED = INT_MAX;
	private:
		GLint vertexIndex;
		GLint vertexTextureIndex;
		GLint normalVectorIndex;
		const Plane* plane;
	};
	// ��ȡƽ�������
	const Data getData(const int index) const;
	// �������
	int addData(Data data);
	// �������
	void clearData();
	// ��Object
	void setObject(const Object& object);
	// ��ȡ�󶨵�Object
	const Object* getObject() const;
	// ��ȡ������Ӧ�Ķ���
	const Vertex& getVertex(const GLint index) const;
	Plane& operator=(const Plane& plane);
	bool operator==(const Plane& plane) const;
	bool operator!=(const Plane& plane) const;
	const static int OPERATION_SUSSESS = 1;
	const static int OPERATION_FAILURE = 0;
private:
	std::vector<Data> datas;
	const Object* object;
};



#endif // !PLANE_H