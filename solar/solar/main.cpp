

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "solarsystem.hpp"
//创建图形窗口的基本宏
#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 700

SolarSystem solarsystem;
// 用于注册 GLUT 的回调
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
	glutInit(&argc, argv);//对GLUT进行初始化，并处理所有的命令行参数
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//这个函数指定了使用 RGBA 模式韩式颜色索引模式。另外还可以 指定是使用单缓冲还是双缓冲窗口。这里我们使用 RGBA 和 双缓冲窗口
	glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);//设置窗口被创建时左上角位于屏幕上的位置
	glutCreateWindow("SolarSystem "); //创建窗口
									  /*	glutDisplayFunc 的函数原型为 glutDisplayFunc(void (*func)(void))，这是一个回调函数，每当 GLUT 确定一个窗口的内容需要更新显示的时候
									  glutDisplayFunc 注册的回调函数就会被执行.，
									  */
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onUpdate); //glutIdleFunc(void (*func)(void)) 将指定一个函数，用于处理当事件循环 ，处于空闲的时候，就执行这个函数。这个回调函数接受一个函数指针作为它的唯一参数
	glutKeyboardFunc(onKeyboard);//  glutKeyboardFunc(void (*func)(unsigned char key, int x, int y)) ， 会将键盘上的键与一个函数关联，当这个键被按下或者释放时，函数就会调用
	glutMainLoop();//进入GLUT事件处理循环，让所有的与"事件"有关的函数调用无限循环。
	return 0;
}

