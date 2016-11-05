/*

This is where the main is located.

The junk() function exists to work around a driver issue on Linux for NVIDIA graphics cards

When compiled using a Mac, there are warnings for depreciated functions. This means that they will soon become obselete in future versions of OpenGL. These warnings do not appear on the Lab Machines because they are running an older verison of OpenGL.

*/

#include <GLUT/glut.h> //Use this line for mac
#include <iostream>
#include "GameState.h"
#include "Painter.h"
#include "SnakeSquare.h"
#include <pthread.h>
#include "math.h"

/*#include <GL/gl.h>  //Use these three lines for Linux
#include <GL/glu.h>
#include <GL/glut.h>*/

GameState g;

static void clearScreen() {
        glutSwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT);
}

void junk() {
  int i;
  i=pthread_getconcurrency();
}; 

static void display(void){
    static float distanceX = 0.0;
    static float distanceY = 0.0;
    Painter* p = new Painter();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    //draws white square so player knows where the snake can go.
    glBegin(GL_POLYGON);
		
        glColor3f(1.0,1.0,1.0);
    	glVertex3f(-0.78, 0.78,-3.0);
    	glVertex3f(-0.78, -0.78,-3.0);
    	glVertex3f(0.78, -0.78,-3.0);
   		glVertex3f(0.78, 0.78,-3.0);
    	glEnd();
    
    g.GameDraw(*p);
    glutSwapBuffers();
    //Finish rendering
}

static void timerCallbackFunction(int value) {
    g.GameTime();
    display();
    glutTimerFunc(100, timerCallbackFunction, 0);
}

void keyPress(unsigned char key, int x, int y) {
    //WASD controls for direction
    switch (key) {
        case 'a' : g.GameKeyEvent('a'); break;
        case 'd' : g.GameKeyEvent('d'); break;
        case 'w' : g.GameKeyEvent('w'); break;
        case 's' : g.GameKeyEvent('s'); break;
    }
}


int main (int argc, char **argv){
    srand(time(NULL));
    Square* s = new Square();
    glutInit(&argc, argv);
    s->createWindow();
    
	//Assign the used Msg-routines
	glutDisplayFunc(display);
	glutReshapeFunc(s->reshape);
    glutKeyboardFunc(keyPress);
    timerCallbackFunction(0);

	//Let GLUT get the msgs
	glutMainLoop();
	return 0;
}
