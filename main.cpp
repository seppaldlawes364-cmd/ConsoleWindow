#include <iostream>
#include <unistd.h>
struct Vec2d
{
    int x;
    int y;
};
class Shape{
    public:
    
    Vec2d pos;
    const Vec2d size = {3,3};
    //if % sign then the pixel should be  transparent you can change the transparent char in the window draw function
    char sprite[3][3] = {{'1','2','3'},
                         {'4','5','6'},
                         {'7','8','9'}};
    void setPosition(Vec2d pos){
        this -> pos = pos;
    }
    void move(Vec2d pos){
        this -> pos.y += pos.y;
        this -> pos.x += pos.x;
    }
    bool intersects(Shape shape){
        //look if the pos+size etc. intersect
        if(this->pos.x+this->size.x >  shape.pos.x|| this-> pos.x > shape.pos.x+shape.size.x){
            if(this -> pos.y+this->size.y >  shape.pos.y|| this -> pos.y > shape.pos.y+shape.size.y){
                return true;
            }
        }
        return false;
    }
    void rotate(int angle){
        //please dont look for comments i dont know either how i got this working
        //please dont look for comments i dont know either how i got this working
        //please dont look for comments i dont know either how i got this working
        //please dont look for comments i dont know either how i got this working
        //please dont look for comments i dont know either how i got this working
        if(angle > 360 || angle < -360){
            std::cerr << "Failed to set angle Reason: angle over 360°";
            return;
        }
        char copy[3][3];
        //copy the array
        for(int y = 0; y < size.y;y++){
            for(int x = 0;x < size.x;x++){
                copy[y][x] = sprite[y][x];
            }
        }
        if(angle == 90 || angle == -270){
            for(int copyY = 0,spriteY = size.y-1; copyY < size.y; copyY++,spriteY--){   
                for(int copyX = 0,spriteX = size.x-1; copyX < size.x; copyX++,spriteX--){   
                    copy[copyX][spriteY] = sprite[copyY][copyX];
                }
            }
        }
        else if(angle == 180){
            for(int copyY = 0,spriteY = size.y-1; copyY < size.y; copyY++,spriteY--){   
                for(int copyX = 0,spriteX = size.x-1; copyX < size.x; copyX++,spriteX--){   
                    copy[copyY][copyX] = sprite[spriteY][spriteX];
                }
            }
        }
        else if(angle == 270 || angle == -90){
            for(int copyY = 0,spriteY = size.y-1; copyY < size.y; copyY++,spriteY--){   
                for(int copyX = 0,spriteX = size.x-1; copyX < size.x; copyX++,spriteX--){   
                    copy[spriteX][copyY] = sprite[copyY][copyX];
                }
            }
        }
        //copy the changed values into the sprite array
        for(int y = 0; y < size.y;y++){
            for(int x = 0;x < size.x;x++){
                sprite[y][x] = copy[y][x];
            }
        }
    }
};
class Window{
    //going to make the size class and window size compatible in the future the same for the shape class
    const Vec2d size = {19,10};
    //const int WinX = 19;
    //const int WinY = 10;
    char window[10][19];
    float delayPerFrame = 1/5; // standard framerate 5fps if no fps is specified
    public:
    void setMaxFramerate(const float fps){
        //set the delay for each frame
        delayPerFrame = 1/fps;
    }
    void clear(char background){
        //convert seconds into microseconds and sleep for that time
        /*this is not located in the display function to leave space 
        in case the user needs to add something for example for debuging
        please dont haunt me for not using proper delta time*/
        usleep(delayPerFrame*1000000);
        //clear current frame
        system("clear");
        //loop through x and y coords
        for(int y = 0; y< size.y;y++){
            for(int x = 0; x < size.x; x++){
                //set every character in the array to # to test if every char is initialised
                window[y][x] = background;
            }
        }
        
    }
    void display(){
        //loop through x and y coords
        for(int y = 0; y< size.y;y++){
            for(int x = 0; x < size.x; x++){
                //print the window
                std::cout << window[y][x];
            }
            //new line after every y level increase
            std::cout << "\n";
        }
    }
    void setOutline(char outline){
        //set an outline at every side
        for(int y = 0; y < size.y; y++){
            for(int x = 0; x < size.x; x++){
                if(y == 0 || y == size.y-1){
                    window[y][x] = outline;
                }
                else if(x == 0 || x == size.x-1){
                    window[y][x] = outline;
                }
            }
        }
    }
    void draw(Shape shape){
        for(int y = 0; y<shape.size.y;y++){
            for(int x = 0; x < shape.size.x;x++){
                //if the char is a % then the shape pixel is transparent
                if(shape.sprite[y][x] != '%'){
                    //draw pixel only if in window to prevent error
                    if(y+shape.pos.y <= size.y && x+shape.pos.x <= size.x){
                        if(y+shape.pos.y >= 0&& x+shape.pos.x >= 0){
                            window[y+shape.pos.y][x+shape.pos.x] = shape.sprite[y][x];
                        }
                    }       
                }
            }
        }
        
    }
    char getPixel(Vec2d coordinate){
        //self explainatory 
        return window[coordinate.y][coordinate.x];
    }
};
//code example and syntax
class Game{
    private:
    Window *window = new Window;
    Shape *shape = new Shape;
    bool gameRunning = true;
    char input;
    int angle = 0;
    public:
    Game(){
        window->setMaxFramerate(2);
        shape->setPosition({2,2});
    }
    ~Game(){
        delete window;
        delete shape;
    }
    void update(){
        shape->rotate(90);
    }
    void render(){
        //sfml based
        window->clear('.');
        
        window->draw(*shape);

        window->setOutline('O');
        window->display();
        
    }
    void run(){
        //code example
        while(gameRunning){
            update();
            render();
        }
    }
};
int main(){
    Game game;
    game.run();
    return 0;
}