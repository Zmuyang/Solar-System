

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "solarsystem.hpp"
//����ͼ�δ��ڵĻ�����
#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 700

SolarSystem solarsystem;
// ����ע�� GLUT �Ļص�
void onDisplay(void) {
	solarsystem.onDisplay();
}
void onUpdate(void) {
	solarsystem.onUpdate();
}
void onKeyboard(unsigned char key, int x, int y) {
	solarsystem.onKeyboard(key, x, y);
}

int main(int argc, char*  argv[]) {
	glutInit(&argc, argv);//��GLUT���г�ʼ�������������е������в���
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//�������ָ����ʹ�� RGBA ģʽ��ʽ��ɫ����ģʽ�����⻹���� ָ����ʹ�õ����廹��˫���崰�ڡ���������ʹ�� RGBA �� ˫���崰��
	glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);//���ô��ڱ�����ʱ���Ͻ�λ����Ļ�ϵ�λ��
	glutCreateWindow("SolarSystem "); //��������
									  /*	glutDisplayFunc �ĺ���ԭ��Ϊ glutDisplayFunc(void (*func)(void))������һ���ص�������ÿ�� GLUT ȷ��һ�����ڵ�������Ҫ������ʾ��ʱ��
									  glutDisplayFunc ע��Ļص������ͻᱻִ��.��
									  */
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onUpdate); //glutIdleFunc(void (*func)(void)) ��ָ��һ�����������ڴ����¼�ѭ�� �����ڿ��е�ʱ�򣬾�ִ���������������ص���������һ������ָ����Ϊ����Ψһ����
	glutKeyboardFunc(onKeyboard);//  glutKeyboardFunc(void (*func)(unsigned char key, int x, int y)) �� �Ὣ�����ϵļ���һ������������������������»����ͷ�ʱ�������ͻ����
	glutMainLoop();//����GLUT�¼�����ѭ���������е���"�¼�"�йصĺ�����������ѭ����
	return 0;
}

