#include <SFML/Graphics.hpp>
#include <time.h>
#include <cmath>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

float DEGTORAD = 0.017453f;

class Player{
  public:

    double x,y,dx,dy,angle,r;
    bool acc;

    Player(){
      x = 150;
      y = 150;
      dx = 0.01;
      dy = 0.01;
      r = 20;
      acc = false;
    }

    void update()
    {
     if (acc)
      { dx+=cos(angle*DEGTORAD)*0.2;
        dy+=sin(angle*DEGTORAD)*0.2; }
     else
      { dx*=0.99;
        dy*=0.99; }

    int maxSpeed=10;
    float speed = sqrt(dx*dx+dy*dy);
    if (speed>maxSpeed)
     { dx *= maxSpeed/speed;
       dy *= maxSpeed/speed; }

    x+=dx;
    y+=dy;

    if (x>WINDOW_WIDTH) x=0; if (x<0) x=WINDOW_WIDTH;
    if (y>WINDOW_HEIGHT) y=0; if (y<0) y=WINDOW_HEIGHT;
    }

    void draw(RenderWindow &app)
    {
      CircleShape circle(r, 3);
      circle.setFillColor(Color(0,0,0));
      circle.setOutlineThickness(1);
      circle.setOutlineColor(sf::Color(250, 255, 255));
      circle.setPosition(x,y);
      circle.setOrigin(r,r);
      circle.setRotation(angle);
      app.draw(circle);
    }

};

int main()
{  
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game!");
    Clock clock;
    Text text;
    Player player;
    Font font;

    if (!font.loadFromFile("./fonts/arcadeclassic.ttf"))
    {
      throw "Missing Fonts";
    }

    float timer=0, delay=0.01;

    window.setFramerateLimit(60);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    
    while (window.isOpen())
    {
      float time = clock.getElapsedTime().asSeconds();
      clock.restart();
      timer+=time;

      Event e;
      while (window.pollEvent(e))
      {
          if (e.type == Event::Closed)      
              window.close();
      }

    if (Keyboard::isKeyPressed(Keyboard::Right)) player.angle+=3;
    if (Keyboard::isKeyPressed(Keyboard::Left))  player.angle-=3;
    if (Keyboard::isKeyPressed(Keyboard::Up)) player.acc=true;
    else player.acc=false;

      if (timer>delay) {
        timer=0; 
        player.update();
        text.setString("X " + to_string((int) player.x) + "\n" + "Y " + to_string((int) player.y));
      }

      ////// draw  ///////
      window.clear();
      player.draw(window);
      window.draw(text);
      window.display();
  }

  return 0;
}
