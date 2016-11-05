/*

This class creates the window for the game

*/

#ifndef snake_square_h
#define snake_square_h

class Square{
    
    
public:
    Square() { //constructor
        
    }
    
    static void reshape(int x, int y){
        if (y == 0 || x == 0) return;  //Nothing is visible then, so return
        //Set a new projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
        glMatrixMode(GL_MODELVIEW);
        glViewport(0,0,x,y);  //Use the whole window for rendering
    }
    
    void createWindow(){
        //Initialize GLUT
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        Wsize = 800;
        glutInitWindowSize(Wsize,Wsize);
        //Create a window with rendering context and everything else we need
        glutCreateWindow("Snake");
        glClearColor(0.0,0.0,0.0,0.0);
    }
    
    
private:
    int Wsize;
    
};

#endif
