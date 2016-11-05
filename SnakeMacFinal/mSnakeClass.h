#ifndef SnakeClass_h
#define SnakeClass_h

#include "SnakeLL.h"
#include "math.h"

bool floatCompare2(float x, float y) {
    if (fabsf(x - y) < 0.00001) {
        return true;
    } else {
        return false;
    }
    
}

//generates a random number
double randomNum() {
    
	int i = rand() % 76;
	while((i % 4) != 0) {
		i = rand() % 76;
	}

	return i;
}

//generates 0 or 1
int randomNeg() {
	return (rand() % 2);
}

//generates a random number between -0.76 and 0.76 that is mod 0.04.
float randomize() {
	float f = (float)(randomNum() / 100 * pow(-1, randomNeg()));
	return f;
}


//creates a segment that can either be used for food or the snake
class Segment{
private:
    float x;
    float y;
    
public:
    Segment(float x, float y){
        this->x = x;
        this->y = y;
    }

    float getX(){
        return x;
    }

    float getY(){
        return y;
    }
};


//creates the snake
class Snake{
private:
    float headx;
    float heady;
    LL<Segment*>* snake;
    int length;
    bool isEaten;
    
    
public:
    Snake(){
        headx = 0.0f;
        heady = 0.0f;
        snake = new LL<Segment*>();

        for(int i = 0; i < 10; i++) {
            snake->insert(i, new Segment(headx - (i* 0.04f), heady));
        }
    }
    
    //gets the x location of the head
    float getX(){
        return snake->item_at(0)->getX();
    }

    //gets the y location of the head
    float getY(){
        return snake->item_at(0)->getY();
    }

    float getXLoc(int position){
        return snake->item_at(position)->getX();
    }

    float getYLoc(int position){
        return snake->item_at(position)->getY();
    }
    
    bool eaten() {
        return isEaten;
    }
    
    void eatTrue() {
    	isEaten = true;
    }
    
    void eatFalse() {
    	isEaten = false;
    }

    void snakeMove(float distance, bool up){
        if (up){
            heady += distance;
        }
        else if (!up){
            headx += distance;
        }
        Segment* newHead = new Segment(headx, heady);
        snake->move(newHead, isEaten);

    }

    int getLength() {
        return snake->size();
    }
};

//creates the food
class Food{
private:
    float x;
    float y;
    Segment* food;
    Segment* temp;
    float fx;
    float fy;
    int length;
    bool onSnake;
    Snake* s;
    
public:
    Food(float x, float y, Snake* s){
        food = new Segment(x, y);
        onSnake = false;
        this->s = s;
        
    }
    
    ~Food() {
        delete food;
    }
    
    float getX(){
        return food->getX();
    }
    
    float getY(){
        return food->getY();
    }
    
    void move() {
        length = s->getLength();
        fx = randomize();
        fy = randomize();
        
        do {
            for (int i = 0; i<length-1; i++) {
                if (floatCompare2(s->getXLoc(i), fx) && floatCompare2(s->getYLoc(i), fy)) {
                    fx = randomize();
                    fy = randomize();
                    onSnake = true;
                    break;
                }
                onSnake = false;
            }
        } while (onSnake);
        
        
        delete food;
        
        food = new Segment(fx, fy);
    }
};

#endif
