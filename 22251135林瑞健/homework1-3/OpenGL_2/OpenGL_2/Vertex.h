#ifndef VERTEX_H
#define VERTEX_H


#include <glad/glad.h>
#include <climits>
#include <glm/glm.hpp>

// ����
class Vertex
{
public:
	Vertex();
	Vertex(const GLfloat x, const GLfloat y, const GLfloat z);
	~Vertex();
	// ����x����
	int setX(const GLfloat x);
	// ����y����
	int setY(const GLfloat y);
	// ����z����
	int setZ(const GLfloat z);
	// ���x����
	GLfloat getX() const;
	// ���y����
	GLfloat getY() const;
	// ���z����
	GLfloat getZ() const;
	Vertex& operator=(const Vertex& vertex);
	bool operator==(const Vertex& vertex) const;
	bool operator!=(const Vertex& vertex) const;
	operator glm::vec3() const;
	operator glm::vec4() const;
	const static int OPERATION_SUSSESS = 1;
	const static int OPERATION_FAILURE = 0;
	const static int UNDEFINED = INT_MIN;
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;
};



#endif // !VERTEX_H