#include "Painter.h"
#include <iostream>
#include <fstream>
#include "mSnakeClass.h"
#include "math.h"

void readAndWrite(int newScore) {
    int* highScores = new int[10];
    int score = 0;
    
    std::fstream myReadFile;
    myReadFile.open("highScores.txt");
    if (myReadFile.is_open()) {
        int i = 0;
        while (!myReadFile.eof()) {
            myReadFile >> score;
            highScores[i] = score;
            i++;
        }
    }
    
    for(int i = 0; i < 10; i++) {
        if(highScores[i] <= newScore) {
            //copy highscores up to this point into a temporary array
            int* temp = new int[10];
            for(int j = 0; j < i; j++) {
                temp[j] = highScores[j];
            }
            
            //add the new number to the array
            temp[i] = newScore;
            
            //add rest of array to temp array except last number
            //only want the top 10 high scores
            for(int k = i; k < 9; k++) {
                temp[k + 1] = highScores[k];
            }
            
            //save new highScores list
            delete highScores;
            highScores = temp;
            break; //dont want to continue running
        }
    }
    myReadFile.seekg(0);
    
    
    //write new highScores array to myReadFile
    for(int i = 0; i < 10; i++) {
        if(i < 9) {
            myReadFile << highScores[i] << std::endl;
        }
        else {
            myReadFile << highScores[i];
        }
    }
    
    //test it works
    myReadFile.seekp(0);
    std::cout << "High scores: \n";
     while(!myReadFile.eof()) {
         int s;
         myReadFile >> s;
         std::cout << s << std::endl;
     }
    
    myReadFile.close();
}

//compares two floats to see if they are equal. (And checks if the snake hits the side of the game)
bool floatCompare(float x, float y) {
    if (fabsf(x - y) < 0.00001) {
        return true;
    } else if ((fabsf(x) - 0.76) > 0.01 || (fabsf(y) - 0.76) > 0.01) {
        return true;
    } else {
        return false;
    }
}

//checks if the snake is dead
bool snakeDead(Snake s, bool gameOver) {
    if (gameOver) {
        return true;
    }
    
    float headx = s.getX();
    float heady = s.getY();
    int length = s.getLength();
    for (int i = 1; i < length-1; i++) {
        if (floatCompare(headx, s.getXLoc(i))) {
            if (floatCompare(heady, s.getYLoc(i))) {
                return true;
            }
        }
    }
    return false;
}

//contains most of the logic of the game
class GameState {

    char currentDirection;
    char lastDirection;
    Snake s;
    //changed
    Food* f;
    int score;
    bool gameOver;
    int z;
    int snakeLength;

public:
	GameState() { //constructor
        currentDirection = 'd';
        lastDirection = 'd';
        f = new Food(.04f, .04f, &s);
        gameOver = false;
        score = 0;
        z = 0;
        snakeLength=0;
	}

	void GameDraw(Painter p) {
        
        if (!gameOver) {
        	//snake
        	for(int i = 0; i < s.getLength() - 1; i++) {
            		float fx = s.getXLoc(i);
            		float fy = s.getYLoc(i);
            		p.drawSquare(0.04f, fx, fy, 0);
		}
        	//food
        	p.drawSquare(0.04f, f->getX(), f->getY(), 1);	
        }
        
        else {
        	//p.endGame();
            if (z < 1) {
                std::cout << "Game Over" << std::endl;
                readAndWrite(score);
                z++;
            }
        }

    	}
    
    //this is what runs every iteration of the game (every 150ms)
    void GameTime() {
        
        if(currentDirection == 'w') {
            if(lastDirection == 's') {
                currentDirection = lastDirection;
            }
        }
        
        else if(currentDirection == 'a') {
            if(lastDirection == 'd') {
                currentDirection = lastDirection;
            }
        }
        else if(currentDirection == 's') {
            if(lastDirection == 'w') {
                currentDirection = lastDirection;
            }
        }
        else if(currentDirection == 'd') {
            if(lastDirection == 'a') {
                currentDirection = lastDirection;
            }
        }
        else {
            std::cout << "Something went wrong." << std::endl;
        }
        
        //moves the snake
        switch (currentDirection) {
            case 'd':
                s.snakeMove(0.04f, false);
                break;
                
            case 'a':
                s.snakeMove(-0.04f, false);
                break;
                
            case 'w':
                s.snakeMove(0.04f, true);
                break;
                
            case 's':
                s.snakeMove(-0.04f, true);
                break;
                
            default:
                break;
        }

        if (s.eaten()) {
            s.eatFalse();
        }
        
        
        //forces the snake to not get longer if it doesnt eat the food
        /*if (!(fabsf(s.getX() - f->getX()) < 0.00001)) {
            if (!(fabsf(s.getY() - f->getY()) < 0.00001)) {
                s.eatFalse();
            }
        }*/
        
        
        //checks if the snake hits the food and moves food
        if ((s.getX() - f->getX()) < 0.00001 && (s.getX() - f->getX()) > -0.00001) {
            if ((s.getY() - f->getY()) < 0.000001 && (s.getY() - f->getY()) > -0.000001) {
                score++;
                std::cout << "Food eaten.\nScore: " << score << std::endl;
                s.eatTrue();
                f->move();
            }
        }
        
        //checks if the snake hits itself or the walls
        gameOver = snakeDead(s, gameOver);
        lastDirection = currentDirection;
        
    }

    //registers the keypresses
    void GameKeyEvent(char keypress) {
        if(keypress == currentDirection) {
            return;
        }

        if(keypress == 'w') {
           if(currentDirection == 's') {
            	return;
            }
        }

        else if(keypress == 'a') {
            if(currentDirection == 'd') {
            	return;
            }
        }
        else if(keypress == 's') {
            if(currentDirection == 'w') {
            	return;
            }
        }
        else if(keypress == 'd') {
            if(currentDirection == 'a') {
            	return;
            }
        }
        else {
            std::cout << "Something went wrong." << std::endl;
        }
        currentDirection = keypress;
    }

};
