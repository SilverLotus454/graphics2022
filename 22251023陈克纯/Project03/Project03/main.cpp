/* code by indere  2017/06/04
** skyboxes.h/.cpp  ������պС���ľ�����εȡ���������ȡ��ľ�������������������ľ
** dynamic.h/.cpp	�������涯̬����
** model.h/.cpp		��ȡOBJģ��
*/

//��Ҫ������ͷ�ļ�
#include"skyboxes.h"
#include "model.h"
#include "dynamic.h"
#include <stdio.h>
#include <GL/glut.h>



#define WINDOW_HEIGHT 300
#define WINDOW_WIDTH 500
#define BUFSIZE	     1000

//�����������ľ���
float G_fDistance = 1.5f;
//�������ת�Ƕ� 
float G_fAngle_horizon = 0.0;
float G_fAngle_vertical = 0.0f;

//�������X Y
GLfloat observe_x = -6.0f;
GLfloat observe_y = 0.0;
GLfloat observe_angle = 90.0f;
GLfloat observe_angle1 = 0.0f;
GLfloat observe_r = 3.0f;
GLfloat observe_z = -0.7f;
const GLfloat PI = 3.24159265357f;
const GLfloat angToarc = 3.141592 / 180.0;	//�ǶȻ�����
const GLfloat arcToang = 180.0 / 3.141592;	//���Ȼ��Ƕ�



GLfloat xx = 0.0f;
GLfloat yy = 0.0f;
GLfloat zz = 0.0f;

//�趨�����ģ���Լ���ʾ�ķ�ʽ
bool redraw = true;
Objmodel *obj1 = new Objmodel();
string path1 = "obj/rubby.obj";
vector<GLfloat > center1(3);
Objmodel *obj2 = new Objmodel();
string path2 = "obj/bird.obj";
vector<GLfloat > center2(3);
Objmodel *obj3 = new Objmodel();
string path3 = "obj/torus.obj";
vector<GLfloat > center3(3);
GLint mode1 = GL_FILL;
GLint mode2 = GL_TRIANGLES;

//light0����
GLfloat Vp0[] = { 0.0,200.0,0.0,0 };	//��Դ������λ��
GLfloat Va0[] = { 0.8,0.8,0.8,1 };       //��Դ������ǿ������  
GLfloat Vd0[] = { 0.6,0.6,0.6,1 };       //��Դɢ���ǿ������  
GLfloat Vs0[] = { 0.5,0.5,0.5,1 };       //��Դ���淴���ǿ������  


										 //�������ӵ�
int prex = 0;
int prey = 0;
//�ӵ��ƶ��ľ��� == ��պн�Ҫ�ƶ��ľ���
GLfloat movedis_x = 0.0f;
GLfloat movedis_z = 0.0f;
GLfloat view_dis_skybox_x = 0.0f;
GLfloat view_dis_skybox_z = 0.0f;
GLfloat terrain_height = 0.0f;
const int TREE_NUM = 100;
GLfloat treex[TREE_NUM];
GLfloat treez[TREE_NUM];
GLint   treetexturenum[TREE_NUM];
GLfloat tree_angle = 0.0f;
Skybox *skybox;
DynamicTexture *fire = new DynamicTexture();

int mode_s = GL_RENDER;
int window_w = 0;
int window_h = 0;

vector<vector<float > >obj_pos;
int obj_nums = 0;


///����
void myinit(void);
void myReshape(GLsizei w, GLsizei h);
void display(void);
void moveMouse(int x, int y);
void processSpecialKeys(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);
void pickObjection(int button, int state, int x, int y);
void drawObjection(int mode);
void motion(int x, int y);

int compare(const void *value1, const void *value2)
{
	return *(int*)value1 - *(int*)value2;
}

void drawGround(GLfloat begin, GLfloat end, GLfloat interval, GLfloat y) {

	for (GLfloat i = begin; i <= end; i += interval) {
		glBegin(GL_LINES);
		glVertex3f(begin, y, i);
		glVertex3f(end, y, i);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(i, y, begin);
		glVertex3f(i, y, end);
		glEnd();
	}

}

int k = 0;
static int last = clock();
void f() {

	//���ó�ģ�;���ģʽ
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int now = clock();
	if (now - last > 100) {
		k = (k + 1) % 8;
		last = now;
		//cout << last << endl;
		glutPostRedisplay();
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);


	cout << "���������ʽ˵����" << endl;
	cout << "w/s/a/d�����ӵ�ǰ�������ƶ�" << endl;
	cout << "����������ҿ����ӵ㷽��" << endl;
	cout << "���OBJģ�Ͳ��ţ������ƶ��������ƶ�OBJģ�� " << endl;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);


	//�趨OPENGL����λ�úʹ�С
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Indere");


	myinit();
	glutReshapeFunc(myReshape);
	glutSpecialFunc(processSpecialKeys);
	glutPassiveMotionFunc(moveMouse);	//����ƶ���ת�ӽ�
	glutMouseFunc(pickObjection);		//�����ѡ��
	glutMotionFunc(motion);				//��갴���ƶ�OBJ
	glutKeyboardFunc(processNormalKeys);
	glutDisplayFunc(display);
	glutIdleFunc(f);					//��ʱҲ�ܻ�����
	glutMainLoop();
	return 0;
}


void myinit(void)
{
	//your initialization code
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float low = -MAP_SCANL * MAP_W / 2 + 5;
	float length = MAP_SCANL * MAP_W - 5;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < TREE_NUM; i++) {
		treex[i] = rand() % (int)length + low;
		treez[i] = rand() % (int)length + low;
		treetexturenum[i] = rand() % 4;		//�����4������ľ���������   
											//��Ϊ����ľ�������������ʵ�������֪��	�����޷���init����͸���  ����ֻ���ֶ���������ֵ
	}

	fire->loadTexImages();
}

void myReshape(GLsizei w, GLsizei h)
{
	//�趨����
	glViewport(0, 0, w, h);

	//�趨͸�ӷ�ʽ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0, 1.0*(GLfloat)w / (GLfloat)h, 0.1, 3000.0);
	window_w = w;
	window_h = h;
}

void display(void)
{
	//cout << "123123" << endl;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//���ó�ģ�;���ģʽ
	glMatrixMode(GL_MODELVIEW);
	skybox = new Skybox();
	//���뵥λ������
	glLoadIdentity();

	gluLookAt(observe_x, observe_y + terrain_height, observe_z,
		observe_r*cos(observe_angle*angToarc) + observe_x, observe_y + 4 * sin(observe_angle1*angToarc) + terrain_height, observe_z + observe_r*sin(observe_angle*angToarc),
		0.0, 1.0, 0.0);
	tree_angle += observe_angle / 100;


	//����պ� 
	skybox->loadTexImages();
	glPushMatrix();
	terrain_height = skybox->getHeight(observe_x, observe_z) + 5.0f;
	skybox->moveSkyBox(view_dis_skybox_x, terrain_height, view_dis_skybox_z);
	//��������

	if (redraw) {		//ֻ��һ��   ��Ȼÿ�ε��û�ܿ�
		obj1->readFile(path1);
		obj2->readFile(path2);
		obj3->readFile(path3);
		center1 = obj1->getCenter();
		center2 = obj2->getCenter();
		center3 = obj3->getCenter();

		center1[0] = 50.0f - center1[0]; center1[2] = 50.0f - center1[2]; center1[1] *= -1;
		obj_pos.push_back(center1);
		center2[0] = -center2[0] - 50; center2[2] = -center2[2] + 50; center2[1] *= -1;
		obj_pos.push_back(center2);
		center3[0] = -center3[0]; center3[2] = -center3[2] + 200; center3[1] *= -1;
		obj_pos.push_back(center3);
		redraw = false;
	}
	drawObjection(mode_s);
	//�����ӵ�����
	float n1[2];
	float x1 = observe_r*cos(observe_angle*angToarc); float z1 = observe_r*sin(observe_angle*angToarc);
	//��һ��
	n1[0] = x1 / sqrtf(x1 * x1 + z1 * z1);
	n1[1] = z1 / sqrtf(x1 * x1 + z1 * z1);
	//n1Ϊ����ͼ���ӵ㵥λ������n1��n2��  n2[2] = {-z,x};  ����ʹn1��n2 = 0
	float n2[2] = { -n1[1],n1[0] };
	if (time(NULL) - last > 150) {
		k = (k + 1) % 8;
		last = clock();
	}

	skybox->drawTrees(treex, treez, TREE_NUM, n2, treetexturenum);
	glTranslatef(-10.0, 0.0, 10.0);
	fire->drawFire(k, n2);
	glPopMatrix();


	glLightfv(GL_LIGHT0, GL_POSITION, Vp0);		//���ù�Դ��λ��
	glLightfv(GL_LIGHT0, GL_AMBIENT, Va0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Vd0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Vs0);

	glTranslatef(0.0, 0.0, -G_fDistance);


	//���Ƶ�ƽ��
	/*GLfloat begin = -100.0f;
	GLfloat end = 100.0f;
	GLfloat interval = 1.0f;
	GLfloat obeserve_y = -1.0f;
	drawGround(begin, end, interval, obeserve_y);*/

	glutSwapBuffers();//����ǰ�󻺳���
					  //glFlush();
}

void moveMouse(int x, int y) {
	observe_angle = (x / 4) % 720;
	observe_angle1 = ((WINDOW_HEIGHT / 2 - y) / 10) % 90 + 10;
	prex = x;
	prey = y;
	if (x <= 0)
		x = WINDOW_WIDTH;
	glutPostRedisplay();
}


void processSpecialKeys(int key, int x, int y)
{
	switch (key) {

	case GLUT_KEY_LEFT:
		observe_angle -= 2.0f; break;
	case GLUT_KEY_RIGHT:
		observe_angle += 2.0f; break;
	case GLUT_KEY_UP:
		if (observe_angle1 <= 90.0f)
			observe_angle1 += 1.0f;
		break;
	case GLUT_KEY_DOWN:
		if (observe_angle1 >= -90.0f)
			observe_angle1 -= 1.0f;
		break;
	}
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'y':	//"a"
		G_fDistance -= 2.0f;
		break;
	case 'Y':		//"A"
		G_fDistance += 2.0f;
		break;
	case 27:	//"esc"
		exit(0);
	case '1':
		path1 = "obj/rubby.obj";
		redraw = true; obj1->~Objmodel(); obj1 = new Objmodel(); break;
	case '2':
		path1 = "obj/bird.obj";
		redraw = true; obj1->~Objmodel(); obj1 = new Objmodel(); break;
	case '3':
		path1 = "obj/torus.obj";
		redraw = true; obj1->~Objmodel(); obj1 = new Objmodel(); break;
	case '4':
		path1 = "obj/wan.obj";
		redraw = true; obj1->~Objmodel(); obj1 = new Objmodel(); break;
	case '5':
		mode2 = GL_POINTS; break;
	case '6':
		mode2 = GL_TRIANGLES; mode1 = GL_LINE; break;
	case '7':
		mode1 = GL_FILL; mode2 = GL_TRIANGLES; break;
	case 'W':
	case 'w':
		movedis_x = 1.0* cos(observe_angle*angToarc) * cos(observe_angle1*angToarc);
		movedis_z = 1.0* sin(observe_angle*angToarc) * cos(observe_angle1*angToarc);
		view_dis_skybox_x += movedis_x;
		view_dis_skybox_z += movedis_z;
		observe_x += /*0.1f*/ movedis_x;
		observe_z += /*0.1f*/ movedis_z;
		break;
	case 'S':
	case 's':
		movedis_x = -1.0* cos(observe_angle*angToarc) * cos(observe_angle1*angToarc);
		movedis_z = -1.0* sin(observe_angle*angToarc) * cos(observe_angle1*angToarc);
		view_dis_skybox_x += movedis_x;
		view_dis_skybox_z += movedis_z;
		observe_x += /*0.1f*/ movedis_x;
		observe_z += /*0.1f*/ movedis_z;
		break;
	case 'A':
	case 'a':
		movedis_x = -1.0* cos((observe_angle + 90.0)*angToarc);
		movedis_z = -1.0* sin((observe_angle + 90.0)*angToarc);
		view_dis_skybox_x += movedis_x;
		view_dis_skybox_z += movedis_z;
		observe_x += /*0.1f*/ movedis_x;
		observe_z += /*0.1f*/ movedis_z;

		break;
	case 'D':
	case 'd':
		movedis_x = 1.0* cos((observe_angle + 90.0)*angToarc);
		movedis_z = 1.0* sin((observe_angle + 90.0)*angToarc);
		view_dis_skybox_x += movedis_x;
		view_dis_skybox_z += movedis_z;
		observe_x += /*0.1f*/ movedis_x;
		observe_z += /*0.1f*/ movedis_z;

		break;
	}
	//printf("�ӵ����꣺X:%f,Y:%f,Z:%f\n", observe_x, observe_y + terrain_height, observe_z);
	glutPostRedisplay();
}

//��갴���ƶ��¼�
void motion(int x, int y) {
	moveMouse(x, y);	//�ӽǱ仯
	int num = obj_nums - 1;
	if (num < 0 || num >= obj_pos.size())
		return;
	float dis = sqrtf((observe_x - obj_pos[num][0])*(observe_x - obj_pos[num][0]) + (observe_z - obj_pos[num][2])*(observe_z - obj_pos[num][2]));
	obj_pos[num][0] = dis*cos(observe_angle*angToarc) + observe_x;
	obj_pos[num][2] = observe_z + dis*sin(observe_angle*angToarc);
	glutPostRedisplay();
}



void drawObjection(int mode) {

	if (mode == GL_SELECT) {
		glInitNames();
	}
	glPushMatrix();
	float obj_high1 = skybox->getHeight(obj_pos[0][0], obj_pos[0][2]) + 6.0f;
	glTranslatef(obj_pos[0][0], obj_pos[0][1] + obj_high1, obj_pos[0][2]);
	glScalef(3.0f, 3.0f, 3.0f);
	if (mode == GL_SELECT)
		glPushName(1);
	obj1->drawBox();
	obj1->showObj(mode1, mode2);	//����Ϊģ�͵���ʾ��ʽ  GL_POINTS	GL_LINES	GL_TRIANGLES
	if (mode == GL_SELECT)
		glPopName();
	glPopMatrix();

	glPushMatrix();
	float obj_high2 = skybox->getHeight(obj_pos[1][0], obj_pos[1][2]) + 1.5f;
	glTranslatef(obj_pos[1][0], obj_pos[1][1] + obj_high2, obj_pos[1][2]);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(3.0f, 3.0f, 3.0f);
	if (mode == GL_SELECT)
		glPushName(2);
	obj2->drawBox();
	obj2->showObj(mode1, mode2);	//����Ϊģ�͵���ʾ��ʽ  GL_POINTS	GL_LINES	GL_TRIANGLES
	if (mode == GL_SELECT)
		glPopName();
	glPopMatrix();

	glPushMatrix();
	float obj_high3 = skybox->getHeight(obj_pos[2][0], obj_pos[2][2]) + 3.0f;
	glTranslatef(obj_pos[2][0], obj_pos[2][1] + obj_high3, obj_pos[2][2]);
	glScalef(0.01, 0.01, 0.01);
	if (mode == GL_SELECT)
		glPushName(3);
	obj3->drawBox();
	obj3->showObj(mode1, mode2);	//����Ϊģ�͵���ʾ��ʽ  GL_POINTS	GL_LINES	GL_TRIANGLES
	if (mode == GL_SELECT)
		glPopName();
	glPopMatrix();
}

void processHits(GLint hits, GLuint buffer[])
{
	GLuint  names, *ptr;
	vector<int> n;
	ptr = (GLuint *)buffer;
	for (int i = 0; i < hits; i++) {
		names = *ptr;
		if (names == 0) {
			ptr += 3;
			continue;
		}
		if (names != 1) {
			obj_nums = 0;
			continue;
		}
		ptr += 3;
		for (int j = 0; j < names; j++) {
			obj_nums = *ptr;
		}
	}
	//cout << obj_nums<< endl;
}



void pickObjection(int button, int state, int x, int y)
{
	GLuint selectBuf[BUFSIZE];   //�洢�����¼
	GLint hits;                                 //�����¼�ĸ���
	GLint viewport[4];                    //�ӿ�

	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;

	glGetIntegerv(GL_VIEWPORT, viewport);  //����ӿ�

	glSelectBuffer(BUFSIZE, selectBuf);    //ָ���洢�����¼������
	glRenderMode(GL_SELECT);          //����ѡ��ģʽ


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	//������ѡ������ѡ���������������(x,viewport[3]-y)����С��(5,5)
	gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 5, 5, viewport);
	//����ͶӰ����

	gluPerspective(80.0f, float(window_w) / float(window_h), 0.1, 3000.0);
	//gluOrtho2D(0.0, 3.0, 0.0, 3.0);
	//��ѡ��ģʽ�»��Ʒ���

	mode_s = GL_SELECT;
	display();
	mode_s = GL_RENDER;
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();        //���ƽ���

	hits = glRenderMode(GL_RENDER); //��ȡ��¼�µĵ���ĸ���
	processHits(hits, selectBuf);           //��������¼selectBuf

	glutPostRedisplay();
}