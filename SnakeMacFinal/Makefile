all: project

project: SnakeTest.o
		g++ /System/Library/Frameworks/GLUT.framework/GLUT /System/Library/Frameworks/OpenGL.framework/OpenGL SnakeTest.o -o project

SnakeTest.o: SnakeTest.cpp
		g++ -c SnakeTest.cpp
		
clean:
	rm -rf *o *gch *stackdump project