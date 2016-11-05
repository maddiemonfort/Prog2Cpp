#ifndef Painter_h
#define Painter_h

#include <GLUT/glut.h> //mac

/*#include <GL/gl.h> //linux
#include <GL/glu.h>
#include <GL/glut.h>*/


class Painter {
public:

	static void drawSquare(float s, float x, float y, int c){
    	//sets the color for snake
        if(c == 0) { //snake
			glColor3f(0.0,0.0,0.9);
    	}
        //sets the color for food
    	else if(c == 1) { //food
    		glColor3f(0.0, 0.7, 0.0);
    	}

        
    	glBegin(GL_POLYGON);
    
    	glVertex3f(x+(s/2),y+(s/2),-3.0);
    	glVertex3f(x-(s/2),y+(s/2),-3.0);
    	glVertex3f(x-(s/2),y-(s/2),-3.0);
        glVertex3f(x+(s/2),y-(s/2),-3.0);
        
    	glEnd();
	}
	
    //could've been printing game over to the window rather than terminal
	/*static void endGame() {
		char text[32];
		sprintf(text, "Game over");
		glColor3f(0.0,0.0,0.0);
		glRasterPos2i(0, 0);
		for (int i = 0; i < 32; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
		}
		
	}*/

};

#endif
