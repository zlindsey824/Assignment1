//
//		          Programming Assignment #1
//
//			        Victor Zordan
//
//
//
/***************************************************************************/

                                                   /* Include needed files */
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "line.h"
#include "curve.h"

#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header

#define WIDTH 500
#define HEIGHT 500

typedef struct{
	double r;
	double g;
	double b;
} Color;

Color *colorA, *colorB;
Line line;
Curve curve;
bool linesActive = false;
bool curvesActive =  false;
bool erase = false;
int x_last,y_last;

/***************************************************************************/

void init_window()
                 /* Clear the image area, and set up the coordinate system */
{

        					       /* Clear the window */
        glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
        glOrtho(0,WIDTH,0,HEIGHT,-1.0,1.0);
}

/***************************************************************************/

void write_pixel(int x, int y, double redInc, double greenInc, double blueInc)
                                         /* Turn on the pixel found at x,y */
{
//printf("%f %f %f\n", redInc, greenInc, blueInc);
        glColor3f (colorA->r + redInc, colorA->g + greenInc, colorA->b + blueInc);
        glBegin(GL_POINTS);
           glVertex3i( x, y, 0);
        glEnd();
}

//***************************************************************************/

void dda(){
  float x = line.getPoint(0).x;
  float y = line.getPoint(0).y;
  float slope = line.getSlope();
  
  
  double rDiff = colorB->r - colorA->r;
  double gDiff = colorB->g - colorA->g;
  double bDiff = colorB->b - colorA->b;
  
  if (fabs(slope) < 1){
  	int xDiff = line.getPoint(1).x-line.getPoint(0).x;
  	int xInc = 0;
    while (line.haveAllPoints() && x != line.getPoint(1).x){
      write_pixel((int)x, (int)round(y),(rDiff/xDiff)*xInc,(gDiff/xDiff)*xInc,(bDiff/xDiff)*xInc);
      (line.getXdiff() < 0) ? x-- : x++;
      (line.getYdiff() < 0) ? y-=fabs(slope) : y+=fabs(slope);
      xInc++;
    }
  }
  if (fabs(slope) >= 1){
    slope = line.getInvSlope();
    int yDiff = line.getPoint(1).y-line.getPoint(0).y;
    int yInc = 0;
    while (line.haveAllPoints() && y != line.getPoint(1).y){
      write_pixel((int)round(x), (int)y,(rDiff/yDiff)*yInc,(gDiff/yDiff)*yInc,(bDiff/yDiff)*yInc);
      (line.getXdiff() < 0) ? x-=fabs(slope) : x+=fabs(slope);
      (line.getYdiff() < 0) ? y-- : y++;
      yInc++;
    }
  }
}

//***************************************************************************/

void display ( void )   // Create The Display Function
{

  if (erase){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      // Clear Screen
    x_last = -1;
    y_last = -1;
    erase = false;
  }
  colorA = new Color{0,0,0};

  write_pixel(x_last,y_last,1.0,1.0,1.0);//<-you can get rid of this call if you like
  delete colorA;
  // CALL YOUR CODE HERE
  double r,g,b;
  int colorDivisions = 100;
  r = (rand() % colorDivisions +1)/(double)colorDivisions;
  g = (rand() % colorDivisions +1)/(double)colorDivisions;
  b = (rand() % colorDivisions +1)/(double)colorDivisions;
  colorA = new Color{r,g,b};
  
  r = (rand() % colorDivisions +1)/(double)colorDivisions;
  g = (rand() % colorDivisions +1)/(double)colorDivisions;
  b = (rand() % colorDivisions +1)/(double)colorDivisions;
  colorB = new Color{r,g,b};
  
  if (linesActive && line.haveAllPoints()) {
    dda();
    line.clearPoints();
    printf("\n");
	}
  if (curvesActive && curve.haveAllPoints()){
    float divisions = 25;
		  
		double rDiff = colorB->r - colorA->r;
		double gDiff = colorB->g - colorA->g;
		double bDiff = colorB->b - colorA->b;
		Color startColor = {colorA->r,colorA->g,colorA->b};
    for(int n = 1; n <= divisions; n++){
			float u = (n-1)/divisions;
      Point firstPoint = curve.getPoint(u);
      line.addPoint(firstPoint.x, firstPoint.y);
      colorA = new Color{startColor.r + (rDiff * u), startColor.g + (gDiff * u), startColor.b + (bDiff * u)};
      u = (n)/divisions;
      Point secondPoint = curve.getPoint(u);
      line.addPoint(secondPoint.x, secondPoint.y);
      colorB = new Color{startColor.r + (rDiff * u), startColor.g + (gDiff * u), startColor.b + (bDiff * u)};
      dda();
      line.clearPoints();
    	delete colorA;
    	delete colorB;
    }
    curve.clearPoints();
    printf("\n");
  }
  glutSwapBuffers();                                      // Draw Frame Buffer
}

/***************************************************************************/
void mouse(int button, int state, int x, int y)
{
/* This function I finessed a bit, the value of the printed x,y should
   match the screen, also it remembers where the old value was to avoid multiple
   readings from the same mouse click.  This can cause problems when trying to
   start a line or curve where the last one ended */
        static int oldx = 0;
        static int oldy = 0;
	int mag;

	y *= -1;  //align y with mouse
	y += 500; //ignore
	mag = (oldx - x)*(oldx - x) + (oldy - y)*(oldy - y);
	if (mag > 20) {
		printf(" x,y is (%d,%d)\n", x,y);
    if (linesActive)
		  line.addPoint(x,y);
    if (curvesActive)
      curve.addPoint(x,y);
	}
	oldx = x;
	oldy = y;
	x_last = x;
	y_last = y;
}

/***************************************************************************/
void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{

	switch ( key ) {
		case 27:              // When Escape Is Pressed...
			exit ( 0 );   // Exit The Program
			break;
    case '1':             // stub for new screen
      printf("New screen\n");
			break;
		case 'l':
      linesActive = true;
      curvesActive =  false;
			printf("Drawing lines\n");
			break;
		case 'c':
      linesActive = false;
      curvesActive =  true;
      printf("Drawing curves\n");
			break;
		case 'e':
      erase = true;
      linesActive = false;
      curvesActive =  false;
      printf("Clearing screen\n");
			break;
		default:
			break;
	}
}
/***************************************************************************/

int main (int argc, char *argv[])
{
/* This main function sets up the main loop of the program and continues the
   loop until the end of the data is reached.  Then the window can be closed
   using the escape key.						  */

	srand(time(NULL));
	glutInit            ( &argc, argv );
       	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize  ( 500,500 );
	glutCreateWindow    ( "Computer Graphics" );
	glutDisplayFunc     ( display );
	glutIdleFunc	    ( display );
	glutMouseFunc       ( mouse );
	glutKeyboardFunc    ( keyboard );

        init_window();				             //create_window

	glutMainLoop        ( );                 // Initialize The Main Loop
}
