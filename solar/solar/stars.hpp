
#ifndef star_hpp
#define star_hpp

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Star {
public:
	GLfloat radius;   //公转半径
	GLfloat speed, selfSpeed; //公转速度，自转速度
	GLfloat distance; //距离太阳中心的距离
	GLfloat rgbaColor[4];  //颜色

	Star* parentStar;   //父节点星球

	Star(GLfloat radius, GLfloat distance , GLfloat speed , GLfloat selfSpeed , Star* parent);   //构造函数，旋转半径、旋转速度、自转速度、绕行(父节点)星球
	void drawStar();   //对一般的星球的移动、旋转等活动进行绘制
	virtual void draw() { drawStar(); }  //负责调用drawStar()
	virtual void update(long timeSpan);  //参数为每次刷新画面时的时间跨度
protected:
	GLfloat alphaSelf, alpha;    // 当前的自转角度 ， 当前的公转角度
};

class Planet : public Star {
public:
	Planet(GLfloat radius, GLfloat distance,GLfloat speed, GLfloat selfSpeed,Star* parent, GLfloat rgbColor[3]);
	void drawPlanet();  //对具备自身材质的行星绘制材质
	virtual void draw() { drawPlanet(); drawStar(); } //向其子类开放重写功能
};

class LightPlanet : public Planet {
public:
	LightPlanet(GLfloat Radius, GLfloat Distance,GLfloat Speed, GLfloat SelfSpeed,Star* Parent, GLfloat rgbColor[]);
	void drawLight();   //对自身可发光的恒星绘制光照
	virtual void draw() { drawLight(); drawPlanet(); drawStar(); } 
};

#endif /* star_hpp */