#include <RSGL/RSGL.hpp>

RSGL::window win("Lenny's Pong",{500,500,1000,500},{0,0,0});
bool running=true, init=false;

int paddleSpeed=17,ballSpeed=3;
RSGL::rect paddle1={20,0,48,144}, paddle2= {win.r.width-80,0,48,144};
RSGL::circle ball={win.r.width/2-34,win.r.length/2-34,34};

int main(){
    srand(time(NULL)); RSGL::point ballDir={0,0};
    while (running){
        win.checkEvents();
        switch(win.event.type){
            case RSGL::quit: running = false; break;
            case RSGL::KeyPressed:
                //player one controls
                if (win.isPressed("W") && paddle1.y > 0){ paddle1.y-=paddleSpeed; init=true;}
                else if (win.isPressed("S") && paddle1.y < win.r.length-paddle1.length){ paddle1.y+=paddleSpeed; init=true;}
                
                //player two controls
                if (win.isPressed("Up") && paddle2.y > 0){ paddle2.y-=paddleSpeed; init=true; }
                if (win.isPressed("Down") && paddle2.y < win.r.length-paddle2.length){ paddle2.y+=paddleSpeed; init=true;}
                break;
            default: break;
        }
        // ball physics
        if (init) while (!ballDir.x || !ballDir.y) ballDir = {(rand() % 3)-1,(rand() % 3)-1}; 
        ball.x+=ballDir.x*ballSpeed; ball.y+=ballDir.y*ballSpeed;
        // if the paddle hits a paddle
        if (RSGL::CircleCollideRect(ball,paddle1) || RSGL::CircleCollideRect(ball,paddle2)){
            if (RSGL::CircleCollideRect(ball,{paddle1.x,paddle1.y,paddle1.width,paddle1.length/2}) || RSGL::CircleCollideRect(ball,{paddle2.x,paddle2.y,paddle2.width,paddle2.length/2})) ballDir.y = 1;
            else  ballDir.y = -1;
            ballDir.x=ballDir.x*-1;
        }
        // if the ball hits the top/bottom of thte screen
        if (ball.y > win.r.length-ball.radius || ball.y < ball.radius) ballDir.y=ballDir.y*-1;
        // if ball goes too far
        if (ball.x > win.r.width-ball.radius || ball.x < 0){
            ballDir = {0,0}; paddle1.y=0; paddle2.y=0; init=false;
            ball.x=win.r.width/2-48; ball.y=win.r.length/2-48;
        }
        // draw the paddles
        RSGL::drawRect({paddle1.x,paddle1.y,paddle1.width,paddle1.length*(2/4)},{255,0,0});
        RSGL::drawSVG("res/images/paddle.svg",paddle1);
        RSGL::drawSVG("res/images/paddle.svg",paddle2);
        RSGL::drawSVG("res/images/ball.svg",{ball.x-7,ball.y-7,48,48});
        win.clear(); // clear the screen for next frame
    }
}