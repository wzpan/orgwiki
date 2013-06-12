// Lstipple.cpp
// OpenGL SuperBible, Chapter 3
// Demonstrates line stippling
// Program by Richard S. Wright Jr.
// 点画模式
// 显示了位模式乘法因子的效果

#include <GL/glut.h>
#include <math.h>


// Define a constant for the value of PI
#define GL_PI 3.1415f

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


// 绘制场景
void RenderScene(void)
{
  GLfloat y;					// 存储变化的y坐标
  GLint factor = 3;			// 点画乘法因子
  GLushort pattern = 0x5555;	// 点画模式
	

  // Clear the window with current clearing color
  glClear(GL_COLOR_BUFFER_BIT);

  // Save matrix state and do the rotation
  glPushMatrix();
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);



  // Step up Y axis 20 units at a time	
  for(y = -90.0f; y < 90.0f; y += 20.0f)
  {
    // Reset the repeat factor and pattern
    glLineStipple(factor,pattern);

    // 画线
    glBegin(GL_LINES);
    glVertex2f(-80.0f, y);
    glVertex2f(80.0f, y);	
    glEnd();

    factor++;
  }


  // Restore transformations
  glPopMatrix();

  // Flush drawing commands
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
        
  // 启用点画功能
  glEnable(GL_LINE_STIPPLE);
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

  // Reset coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Establish clipping volume (left, right, bottom, top, near, far)
  if (w <= h) 
    glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
  else 
    glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Stippled Line Example");
  glutReshapeFunc(ChangeSize);
  glutSpecialFunc(SpecialKeys);
  glutDisplayFunc(RenderScene);
  SetupRC();
  glutMainLoop();

  return 0;
}
