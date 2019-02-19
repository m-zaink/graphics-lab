#include <bits/stdc++.h>
#include <GL/glut.h>
#define MAX 10
using namespace std;

class Figure {
private:
	bool used;
	int top;
	int xmin, xmax, ymin, ymax;
	int xver[MAX], yver[MAX];
public:
	Figure() {
		used = false;
		top = -1;
		xmin = xmax = ymin = ymax = INT_MIN;
	}

	void addVertex(int x, int y) {
		++top;
		xver[top] = x, yver[top] = y;
	}

	// void endVextex() {
	// 	++top;
	// 	xver[top] = xver[0];
	// 	yver[top] = yver[0];
	// }

	int getTop() {
		return top;
	}

	void drawPolygon() {
		glClear(GL_COLOR_BUFFER_BIT);
		if(top <= 1) 
			cout << "Error. No points present.";
			exit(0);
		}
		// glClearColor(1, 1, 1, 0);

		glColor3f(1, 0, 0);

		glBegin(GL_POLYGON);
		
		for(int i = 0; i < top; ++i)
			glVertex2d(xver[i], yver[i]);

		glEnd();
		glFlush();
		// glutPostRedisplay();
	}
}figure;

int width = 500, height = 500;

void myReshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w, 0.0,(GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,w,h);
	width = w;
	height = h;
}

void mouseFunc(int btn, int st, int x, int y) {
	if(btn == GLUT_LEFT_BUTTON && st == GLUT_DOWN) {
		glutPostRedisplay();
		figure.addVertex(x, width - y);
		return;
	} 
	if(btn == GLUT_RIGHT_BUTTON && st == GLUT_DOWN) {
		figure.drawPolygon();
		return;
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutCreateWindow("Polygon Modules");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);

	glutMainLoop();

	return 0;
}