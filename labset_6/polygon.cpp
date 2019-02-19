#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>

#define MAX_POLY 8
#define MAX_VER 10

#define TRUE 1
#define FALSE 0

typedef struct polygon
{
	int color;
	int used;
	int xmin, xmax,ymin,ymax;
	int xc, yc;
	int nvtcs;
	int x[MAX_VER],y[MAX_VER];
}polygon;

int picking = FALSE;
int moving =FALSE;
int in_poly = -1;
int present_color = 0;

GLsizei wh = 1000, ww = 1000;


GLfloat colors[8][3]= {
	//Array that holds a set of colors.
	{0.0,0.0,0.0},
	{1.0,0.0,0.0},
	{0.0,1.0,0.0},
	{0.0,0.0,1.0},
	{1.0,1.0,0.0},
	{1.0,0.0,1.0},
	{0.0,1.0,1.0},
	{0.5,0.5,1.0}
};

polygon polys[MAX_POLY];
int pick_poly(int x,int y);

void myReshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w, 0.0,(GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,w,h);
	ww = w;
	wh= h;
}

void myinit()
{
	int i;
	glClearColor(1.0,1.0,1.0,0.0);
    /* mark all polygons unused */
	for(i=0;i<MAX_POLY;i++)
		polys[i].used = FALSE;
}

void Mymouse(int btn, int st,int x, int y)
{
	// Function to handle mouse clicks/events.


	int i,j;
	// Since the real window's coordinate system starts from the top left corner
	// 'y' had to be inverted to accommodate it in our coordinate system.
	y=wh-y;


	if(btn==GLUT_LEFT_BUTTON && st==GLUT_DOWN && !picking && !moving)
	{
		// This event is for creating the polygon.
		moving = FALSE;
		if(in_poly>=0)
		{
			if(polys[in_poly].nvtcs == MAX_VER)
			{
				printf("Exceeds maximum number of vertices\n");
				exit(0);
			}
			i= polys[in_poly].nvtcs;
			polys[in_poly].x[i]=x;
			polys[in_poly].y[i]=y;
			polys[in_poly].nvtcs++;
		}
	}


	if(btn==GLUT_LEFT_BUTTON && st==GLUT_DOWN && picking && !moving)
	{
		// This event is for selecting the polygon.
		picking= FALSE;
		moving = FALSE;
		j= pick_poly(x,y);
		if(j>=0)
		{
			polys[j].used = FALSE;
			in_poly = -1;
			glutPostRedisplay();
		}

	}
}

int pick_poly(int x, int y)
{
    /* find first polygon in which we are in bounding box */
	int i;
	for(i=0; i<MAX_POLY; i++)
	{
		if(polys[i].used)
			if((x>=polys[i].xmin) && (x<=polys[i].xmax) &&
				(y>=polys[i].ymin) && (y<=polys[i].ymax))
			{
				in_poly =i;
				moving =TRUE;
				return i;
			}

		}

		printf("not in a polygon\n");
		return -1;

	}
	void mymotion(int x, int y)
	{
		// Find if we are inside a polygon
		float dx,dy;
		int i,j;
		if(moving)
		{
			y=wh-y;
			j= pick_poly(x,y);
			if(j<0)
			{
				printf("not in a polygon\n");
				return;
			}

			dx= x-polys[j].xc;
			dy = y-polys[j].yc;
			for(i=0;i<polys[j].nvtcs;i++)
			{
				polys[j].x[i]+=dx;
				polys[j].y[i]+=dy;
			}
        /* update the bounding box */
			polys[j].xc+=dx;
			polys[j].yc+=dy;
			if(dx>0) polys[j].xmax+=dx;
			else polys[j].xmin+=dx;
			if(dy>0) polys[j].ymax+=dy;
			else polys[j].ymin+=dy;
			glutPostRedisplay();
		}
	}

	void colormenu(int id )
	{
		present_color = id;
		if(in_poly>=0) polys[in_poly].color = id;
	}

	void mainmenu(int id)
	{
		int i;
		switch(id)
		{
        case 1: /*create a new polygon */
			moving = FALSE;
            /*find a polygon which is not in use now */
			for(i=0; i< MAX_POLY;i++)
				if(polys[i].used == FALSE) break;

			if(i == MAX_POLY)
			{
				printf("Exceeded maximum number of polygons\n");
				exit(0);
			}
            /*Give the details of the polygon*/
			polys[i].color =present_color;
			polys[i].used = TRUE;
			polys[i].nvtcs =0;
			in_poly= i;
			picking = FALSE;
			break;
        case 2: /*  end polygon and find bounding box and center*/
			moving =FALSE;
			if(in_poly>=0)
			{
                /*initialize the bouning box and center to frist vertex */
				polys[in_poly].xmax = polys[in_poly].xmin = polys[in_poly].x[0];
				polys[in_poly].ymax = polys[in_poly].ymin = polys[in_poly].y[0];

				polys[in_poly].xc = polys[in_poly].x[0];
				polys[in_poly].yc = polys[in_poly].y[0];

                /* now find the actual center and limits of bounding box*/
				for(i=1;i<polys[in_poly].nvtcs;i++)
				{
					if(polys[in_poly].x[i] < polys[in_poly].xmin)
						polys[in_poly].xmin = polys[in_poly].x[i];
					else if(polys[in_poly].x[i] > polys[in_poly].xmax)
						polys[in_poly].xmax = polys[in_poly].x[i];
					if(polys[in_poly].y[i] < polys[in_poly].ymin)
						polys[in_poly].ymin = polys[in_poly].y[i];
					else if(polys[in_poly].y[i] > polys[in_poly].ymax)
						polys[in_poly].ymax = polys[in_poly].y[i];

					polys[in_poly].xc += polys[in_poly].x[i];
					polys[in_poly].yc += polys[in_poly].y[i];
				}

				polys[in_poly].xc = polys[in_poly].xc/ polys[in_poly].nvtcs;
				polys[in_poly].yc = polys[in_poly].yc/ polys[in_poly].nvtcs;
			}
			in_poly = -1;
			glutPostRedisplay();
			break;
        case 3: /* set picking mode */
			picking = TRUE;
			moving = FALSE;
			break;
        case 4: /* set moving mode */
			moving = TRUE;
			break;
			case 5: exit(0);
		}
	}

void display()
{
/* display all active polygons */
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT);
	for(i=0;i<MAX_POLY;i++)
	{
		if(polys[i].used)
		{
			glColor3fv(colors[polys[i].color]);
			glBegin(GL_POLYGON);
			for(j=0;j<polys[i].nvtcs;j++)
				glVertex2i(polys[i].x[j], polys[i].y[j]);
			glEnd();
		}
	}
	glFlush();
}

int main(int argc,char **argv)
{
	int cm;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("Polygon Modeler");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	myinit();
	cm= glutCreateMenu(colormenu);
	glutAddMenuEntry("Black", 0);
	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Green",2);
	glutAddMenuEntry("Blue",3);
	glutAddMenuEntry("Yellow",4);
	glutAddMenuEntry("Magenta",5);
	glutAddMenuEntry("Cyan",6);
	glutAddMenuEntry("unknown",7);

	glutCreateMenu(mainmenu);
	glutAddMenuEntry("new polygon", 1);
	glutAddMenuEntry("end polygon",2);
	glutAddMenuEntry("delete polygon", 3);
	glutAddMenuEntry("move polygon",4);
	glutAddMenuEntry("quit", 5);
	glutAddSubMenu("Colors", cm);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMouseFunc(Mymouse);
	glutMotionFunc(mymotion);
	glutMainLoop();
	return 0;
}
