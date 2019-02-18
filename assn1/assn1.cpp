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
#include <math.h>
#include "line.h"

#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header

#define WIDTH 500
#define HEIGHT 500

Line line;

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

void write_pixel(int x, int y, double intensity)
                                         /* Turn on the pixel found at x,y */
{

        glColor3f (intensity, intensity, intensity);                 
        glBegin(GL_POINTS);
           glVertex3i( x, y, 0);
        glEnd();	
}

//***************************************************************************/

void display ( void )   // Create The Display Function
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      // Clear Screen 

	if (!line.haveAllPoints())
  	write_pixel(x_last,y_last,1.0);//<-you can get rid of this call if you like
  // CALL YOUR CODE HERE
  //dda();
  if (line.haveAllPoints()) {
		int x = line.getPoint(0).x;
		float y = line.getPoint(0).y;
		float slope = line.getSlope();
		while (line.haveAllPoints() && x != line.getPoint(1).x){
			printf("%f\n", slope);
			write_pixel(x, (int)round(y),1.0);
			(line.getXdiff() < 0) ? x-- : x++;
			(line.getYdiff() < 0) ? y-=abs(slope) : y+=abs(slope);
		}
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
		line.addPoint(x,y);
	}
	oldx = x;
	oldy = y;
	x_last = x;
	y_last = y;
	printf("%d\n",line.getNumPoints());
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
			//line();
			printf("drawing line\n");
			break;
		case 'c':
			break;
		case 'e':
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


