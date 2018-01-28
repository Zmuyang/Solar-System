
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

void Star::drawStar() { // 绘制具体的星球 

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	int n = 1440;

	glPushMatrix();//保存OpenGL当前的矩阵环境
	{

		if (parentStar != 0 && parentStar->distance > 0) { // 如果是行星，且距离不为0，那么 且向原点平移一个半径，这部分用于处理卫星

			glRotatef(parentStar->alpha, 0, 0, 1);//将绘制的图形沿 z 轴旋转 alpha

			glTranslatef(parentStar->distance, 0.0, 0.0);  // x 轴方向上平移 distance , y,z 方向不变
		}

		glBegin(GL_LINES); //绘制运行轨道

		for (int i = 0; i<n; ++i)
			glVertex2f(distance * cos(2 * PI * i / n),
				distance * sin(2 * PI * i / n));
		glEnd();

		glRotatef(alpha, 0, 0, 1); // x 轴方向上平移 distance , y,z 方向不变

		glTranslatef(distance, 0.0, 0.0); // x 轴方向平移 distance, y,z 方向不变

		glRotatef(alphaSelf, 0, 0, 1);  //自转

		glColor3f(rgbaColor[0], rgbaColor[1], rgbaColor[2]); //绘制行星颜色
		glutSolidSphere(radius, 40, 32);   //渲染一个球体
	}
	glPopMatrix();  //恢复初始矩阵环境

}

void Star::update(long timeSpan) {
	alpha += timeSpan * speed;  // 更新角度
	alphaSelf += selfSpeed;      // 更新自转角度
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

void Planet::drawPlanet() {   //不发光的星球，需要绘制光照效果
	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
	GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
	GLfloat mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat mat_emission[] = { rgbaColor[0], rgbaColor[1], rgbaColor[2], rgbaColor[3] };
	GLfloat mat_shininess = 90.0f;
	// glMaterialfv指定用于光照计算的当前材质属性，参数face的取值可以是GL_FRONT、GL_BACK或GL_FRONT_AND_BACK，指出材质属性将应用于物体的哪面。 
	//镜面指数只需要设置一个数值，这时只需要使用glMaterialf；而其他的材质设置都需要设置多个值，这是需要使用数组进行设置，使用带指针向量参数的版本 glMaterialfv 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); //材质的环境颜色
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //材质的散射颜色
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);//材质的镜面反射颜色
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);//材质的发射光颜色
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);//镜面反射指数
}

LightPlanet::LightPlanet(GLfloat radius, GLfloat distance, GLfloat speed,
	GLfloat selfSpeed, Star* parent, GLfloat rgbColor[3]) :
	Planet(radius, distance, speed, selfSpeed, parent, rgbColor) {
	;
}

void LightPlanet::drawLight() {//而对于 LightPlanet 类来说，属于发光的星球，所以我们不但要设置其光照材质，还要设置其光源位置

	GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };//环境光
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };//散射光
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };//镜面光
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);  // 指定0号光源的位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); // 设置0号光源的环境光属性 ，表示各种光线照射到该材质上，经过很多次反射后追踪遗留在环境中的光线强度
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); // 设置0号光源的散射光属性 ，漫射反应后的光照强度
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // 设置0号光源的镜面反射光属性，镜面反射后的光照强度

}