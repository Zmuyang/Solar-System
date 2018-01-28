
#include "stars.hpp"
#include <cmath>

#define PI 3.1415926535

Star::Star(GLfloat radius, GLfloat distance,
	GLfloat speed, GLfloat selfSpeed,
	Star* parent) {
	this->radius = radius;
	this->selfSpeed = selfSpeed;
	this->alphaSelf = this->alpha = 0;
	this->distance = distance;

	for (int i = 0; i < 4; i++)
		this->rgbaColor[i] = 1.0f;

	this->parentStar = parent;
	if (speed > 0)
		this->speed = 360.0f / speed;
	else
		this->speed = 0.0f;
}

void Star::drawStar() { // ���ƾ�������� 

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	int n = 1440;

	glPushMatrix();//����OpenGL��ǰ�ľ��󻷾�
	{

		if (parentStar != 0 && parentStar->distance > 0) { // ��������ǣ��Ҿ��벻Ϊ0����ô ����ԭ��ƽ��һ���뾶���ⲿ�����ڴ�������

			glRotatef(parentStar->alpha, 0, 0, 1);//�����Ƶ�ͼ���� z ����ת alpha

			glTranslatef(parentStar->distance, 0.0, 0.0);  // x �᷽����ƽ�� distance , y,z ���򲻱�
		}

		glBegin(GL_LINES); //�������й��

		for (int i = 0; i<n; ++i)
			glVertex2f(distance * cos(2 * PI * i / n),
				distance * sin(2 * PI * i / n));
		glEnd();

		glRotatef(alpha, 0, 0, 1); // x �᷽����ƽ�� distance , y,z ���򲻱�

		glTranslatef(distance, 0.0, 0.0); // x �᷽��ƽ�� distance, y,z ���򲻱�

		glRotatef(alphaSelf, 0, 0, 1);  //��ת

		glColor3f(rgbaColor[0], rgbaColor[1], rgbaColor[2]); //����������ɫ
		glutSolidSphere(radius, 40, 32);   //��Ⱦһ������
	}
	glPopMatrix();  //�ָ���ʼ���󻷾�

}

void Star::update(long timeSpan) {
	alpha += timeSpan * speed;  // ���½Ƕ�
	alphaSelf += selfSpeed;      // ������ת�Ƕ�
}


Planet::Planet(GLfloat radius, GLfloat distance,
	GLfloat speed, GLfloat selfSpeed,
	Star* parent, GLfloat rgbColor[3]) :
	Star(radius, distance, speed, selfSpeed, parent) {
	rgbaColor[0] = rgbColor[0];
	rgbaColor[1] = rgbColor[1];
	rgbaColor[2] = rgbColor[2];
	rgbaColor[3] = 1.0f;
}

void Planet::drawPlanet() {   //�������������Ҫ���ƹ���Ч��
	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
	GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
	GLfloat mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat mat_emission[] = { rgbaColor[0], rgbaColor[1], rgbaColor[2], rgbaColor[3] };
	GLfloat mat_shininess = 90.0f;
	// glMaterialfvָ�����ڹ��ռ���ĵ�ǰ�������ԣ�����face��ȡֵ������GL_FRONT��GL_BACK��GL_FRONT_AND_BACK��ָ���������Խ�Ӧ������������档 
	//����ָ��ֻ��Ҫ����һ����ֵ����ʱֻ��Ҫʹ��glMaterialf���������Ĳ������ö���Ҫ���ö��ֵ��������Ҫʹ������������ã�ʹ�ô�ָ�����������İ汾 glMaterialfv 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); //���ʵĻ�����ɫ
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //���ʵ�ɢ����ɫ
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);//���ʵľ��淴����ɫ
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);//���ʵķ������ɫ
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);//���淴��ָ��
}

LightPlanet::LightPlanet(GLfloat radius, GLfloat distance, GLfloat speed,
	GLfloat selfSpeed, Star* parent, GLfloat rgbColor[3]) :
	Planet(radius, distance, speed, selfSpeed, parent, rgbColor) {
	;
}

void LightPlanet::drawLight() {//������ LightPlanet ����˵�����ڷ���������������ǲ���Ҫ��������ղ��ʣ���Ҫ�������Դλ��

	GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };//������
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };//ɢ���
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };//�����
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);  // ָ��0�Ź�Դ��λ��
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); // ����0�Ź�Դ�Ļ��������� ����ʾ���ֹ������䵽�ò����ϣ������ܶ�η����׷�������ڻ����еĹ���ǿ��
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); // ����0�Ź�Դ��ɢ������� �����䷴Ӧ��Ĺ���ǿ��
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // ����0�Ź�Դ�ľ��淴������ԣ����淴���Ĺ���ǿ��

}