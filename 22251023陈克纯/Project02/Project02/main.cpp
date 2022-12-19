#include "loadBMP.h"
#include "MouseEvent.h"

extern texture * sun, *earth, *moon;			//����ָ��

void init(void)
{
	Reset();

	//�����ɫ
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//�����ƹ�Ч��
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//���ö�ά����
	glEnable(GL_TEXTURE_2D);

	//��Դ����
	GLfloat mat_shininess[] = { 10.0 };
	GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

	//������Ӱƽ��
	glShadeModel(GL_SMOOTH);
	//���ò��Ϸ�������
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//0�Ź�Դ��λ��
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	//ʹ��lmodel_ambien
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	//��������
	LoadAllTextures();
}

void idle()
{
	day += angle;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void display(void)
{
	//���ù�Դ
	GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 2.0f };

	year = day / 365;
	month = day / 30;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat mat_ambient1[] = { 1,0,0,1 };
	GLfloat mat_emission[] = { 1,1,1,0 };

	GLfloat mat_ambient2[] = { 0.4,0.4,0.8,1 };
	GLfloat no_emission[] = { 0,0,0,1 };

	//����̫��
	glPushMatrix();
	glRotatef((GLfloat)Yrot, 0., 1., 0.);
	glRotatef((GLfloat)Xrot, 1., 0., 0.);
	glScalef((GLfloat)Scale, (GLfloat)Scale, (GLfloat)Scale);
	glBindTexture(GL_TEXTURE_2D, sun->texID);
	glRotatef(month, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glRotatef(90, -1, 0, 0);

	glDisable(GL_LIGHTING);
	gltDrawSphere(1.0, 60, 40);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glPopMatrix();

	//���Ƶ���
	glPushMatrix();
	glRotatef((GLfloat)Yrot, 0., 1., 0.);
	glRotatef((GLfloat)Xrot, 1., 0., 0.);
	glScalef((GLfloat)Scale, (GLfloat)Scale, (GLfloat)Scale);
	//���������һ����̫��ת������ת��
	glRotatef(year, 0.0, 1.0, 0.0);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, earth->texID);
	glTranslatef(3.0, 0.0, 0.0);
	//������ת 
	glRotatef(month, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
	glRotatef(90, -1, 0, 0);
	gltDrawSphere(0.4, 40, 40);
	glPopMatrix();

	//��������
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, moon->texID);
	glTranslatef(3.0, 0.0, 0.0);
	glRotatef(60, -1, 1, 0);
	//�����Ƶ���ת
	glRotatef(month, 0, 1.0, 0);
	glTranslatef(0.6, 0.0, 0.0);
	glRotatef(90, -1, 0, 0);
	gltDrawSphere(0.07, 20, 20);
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);				//ָ���ӿڴ�С
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1, 20);		//͸��ͶӰ

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	//ָ���������λ��	
}

int main(int argc, char** argv)
{
	//��ʼ��
	glutInit(&argc, argv);
	//��ʼ����ʾģʽ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//��ʼ����ʾ���ڴ�С
	glutInitWindowSize(1000, 600);
	//��ʼ����ʾ����λ��
	glutInitWindowPosition(100, 100);
	//��������
	glutCreateWindow(argv[0]);

	//��ʼ���û�����
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);

	glutMainLoop();
	return 0;
}

