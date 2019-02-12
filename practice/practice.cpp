#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	glColor3d(1, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
		glVertex3d(-0.8, 0, 0);
		glVertex3d(0.8, 0, 0);
		glVertex3d(0, 0.5, 0);
	glEnd();

	// glColor3d(0, 0, 0);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	for(float i = -0.8; i < 0.8; i+=0.01) {
		glVertex3d(0, 0.5, 0);
		glVertex3d(i, 0, 0);
	}
	glEnd();


	// glColor3d(0.8, 0.2, 0.3);
	glColor3d(0, 1, 1);
	glBegin(GL_POLYGON);
		glVertex3d(-0.8, 0, 0);
		glVertex3d(-0.8, -0.8, 0);
		glVertex3d(0.8, -0.8, 0);
		glVertex3d(0.8, 0, 0);
	glEnd();

	glColor3d(0, 0, 0);
	glBegin(GL_POLYGON);
		glVertex3d(-0.3, -0.4, 0);
		glVertex3d(-0.3, -0.8, 0);
		glVertex3d(0.3, -0.8, 0);
		glVertex3d(0.3, -0.4, 0);
	glEnd();

	glColor3d(0, 1, 0);
	glBegin(GL_POLYGON);
		glVertex3d(-0.8, -0.8, 0);
		glVertex3d(-1, -1, 0);
		glVertex3d(1, -1, 0);
		glVertex3d(0.8, -0.8, 0);
	glEnd();


	glFlush();
}

void initDefaults(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("My Lovely House");
	glutDisplayFunc(display);
}

int main(int argc, char** argv) {
	initDefaults(argc, argv);
	glutMainLoop();
}