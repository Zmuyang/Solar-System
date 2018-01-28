#ifndef solarsystem_hpp
#define solarsystem_hpp


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "stars.hpp"

#define STARS_NUM 10

class SolarSystem {

public:

	SolarSystem();
	~SolarSystem();

	void onDisplay();
	void onUpdate();
	void onKeyboard(unsigned char key, int x, int y);

private:
	Star * stars[STARS_NUM];

	//以下三行定义观察视角的参数
	GLdouble viewX, viewY, viewZ;
	GLdouble centerX, centerY, centerZ;
	GLdouble upX, upY, upZ;
};

#endif /* solarsystem_hpp */