all: project

project: SnakeTest.o
		g++ -o project SnakeTest.o -lGL -lGLU -lglut -lm -pthread

SnakeTest.o: SnakeTest.cpp
		g++ -c SnakeTest.cpp
		
clean:
	rm -rf *o *gch *stackdump project