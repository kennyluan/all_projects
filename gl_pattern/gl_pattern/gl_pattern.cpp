// gl_pattern.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

#define GLEW_STATIC 1
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

GLuint vboId[2];

static GLint vertices[] = {
		1,1,0,
		1,100,0,
		100,1,0,
		100,100,0,
		1,1,-100,
		1,100,-100,
		100,1,-100,
		100,100,-100
		};

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	// Init glew library
	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		cout<<"failed to initalize glew"<<endl;
	}
	cout << "using GLEW version "<< glewGetString(GLEW_VERSION)<<endl;

	// VBO
	glGenBuffers(2, vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)/sizeof(vertices[0])*sizeof(GLint), vertices, GL_STATIC_DRAW);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 0.0);
	gluLookAt (0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glVertexPointer(3, GL_INT, 0, BUFFER_OFFSET(0));
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);

	glBegin(GL_TRIANGLE_STRIP);
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);
	glEnd();

	glFlush();
}

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (0.0, w, 0.0, h, 1.5, 200.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y)
{
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(256, 256);
   glutInitWindowPosition(100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}