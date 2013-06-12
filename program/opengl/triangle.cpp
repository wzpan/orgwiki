// Triangle.cpp
// OpenGL SuperBible
// Demonstrates OpenGL Triangle Fans, backface culling, and depth testing
// Program by Richard S. Wright Jr.
#include <GL/glut.h>
#include <math.h>


// Define a constant for the value of PI
#define GL_PI 3.1415f

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

// Flags for effects
// Flags for effects
int iCull = 0;
int iOutline = 0;
int iDepth = 0;

///////////////////////////////////////////////////////////////////////////////
// Reset flags as appropriate in response to menu selections
void ProcessMenu(int value)
	{
	switch(value)
		{
		case 1:
			iDepth = !iDepth;
			break;

		case 2:
			iCull = !iCull;
			break;

		case 3:
			iOutline = !iOutline;
		default:
			break;
		}

	glutPostRedisplay();
	}


// Called to draw scene
void RenderScene(void)
	{
	GLfloat x,y,angle;  // 存储坐标和角度
	int iPivot = 1;		// 用于标识替代颜色

	// 清除窗口和缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 如果标志已被设置，打开选择
	if(iCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// 如果标志已被设置，打开深度测试
	if(iDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	// 如果标志已被设置，只作为线框绘制背面
	if(iOutline)
		glPolygonMode(GL_BACK,GL_LINE);
	else
		glPolygonMode(GL_BACK,GL_FILL);
		

	// 保存矩阵状态并进行旋转
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);


	// 开始绘制三角形扇
	glBegin(GL_TRIANGLE_FAN);

	// 圆锥的锥尖是三角形扇的共享顶点
    // 沿z轴移动，产生一个圆锥而不是圆
	glVertex3f(0.0f, 0.0f, 75.0f);
	
	// 绕一个圆循环，把沿这个圆的偶数点指定为三角形扇的顶点
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
		{
		// 计算下一个顶点的x和y位置
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
	
		// 交替使用红色和绿色
		if((iPivot %2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
			
		// 增加基准值，下次改变颜色
		iPivot++;

		// 为三角形扇指定下一个顶点
		glVertex2f(x, y);
		}

	// 完成为圆锥绘制三角形扇
	glEnd();


	// 开始绘制一个新的三角形扇，用于覆盖圆锥的底
	glBegin(GL_TRIANGLE_FAN);

	// 三角形扇的中心位于原点
	glVertex2f(0.0f, 0.0f);
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
		{
		// 计算下一个顶点的x和y位置
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
	
		// 交替使用红色和绿色
		if((iPivot %2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
			
		// 增加基准值，下次改变颜色
		iPivot++;

		// 指定三角形的下一个顶点
		glVertex2f(x, y);
		}

	// 完成绘制覆盖底面的三角形扇
	glEnd();

	// 恢复变换
	glPopMatrix();


    glutSwapBuffers();
	}

// This function does any needed initialization on the rendering
// context. 
void SetupRC()
	{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

	// Set drawing color to green
	glColor3f(0.0f, 1.0f, 0.0f);

	// 把着色模式设置为单调着色
	glShadeModel(GL_FLAT);

	// 顺时针环绕的多边形是正面
    // 这是翻转的，因为我们使用的是三角形扇
	glFrontFace(GL_CW);
	}

void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key > 356.0f)
		xRot = 0.0f;

	if(key < -1.0f)
		xRot = 355.0f;

	if(key > 356.0f)
		yRot = 0.0f;

	if(key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
	}


void ChangeSize(int w, int h)
	{
	GLfloat nRange = 100.0f;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset projection matrix stack
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}

int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Triangle Culling Example");
	
	// Create the Menu
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Toggle depth test",1);
	glutAddMenuEntry("Toggle cull backface",2);
	glutAddMenuEntry("Toggle outline back",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
	}
