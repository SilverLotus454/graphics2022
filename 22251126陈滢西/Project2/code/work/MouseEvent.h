#pragma once
const float INF = 1000000.0;
#include <gl/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  //��Ҫʲô�任���͵���ʲô�ļ����������ȥ������
#include <glm/gtc/type_ptr.hpp>
extern float	Scale;					// scaling factor
extern float	Xrot, Yrot;				// rotation angles in degrees
extern float	Xscreen, Yscreen;

//using namespace glm;
typedef struct _FPoint3 {
	int x;
	int y;
	int z;
	int r;
}FPoint3;
void CastRay(int x, int y);
float IntersectSphere(glm::vec3 O, glm::vec3 D, glm::vec3 S, float R);
void MouseMotion(int x, int y);
void MouseButton(int button, int state, int x, int y);
void Reset();