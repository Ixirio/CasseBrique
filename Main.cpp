#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <time.h>
#include "Main.h"

using namespace sf;
int main()
{

    srand(time(0));

    const int windowLength = 520;
    const int windowHeight = 450;

    RenderWindow window(VideoMode(windowLength, windowHeight), "Casse brique");
    window.setFramerateLimit(60);

    const float racketLength = 60;
    const float racketHeight = 10;
    const float size = 10;
    float brickLength = 47;
    float brickHeight = 20;

    float posX = 260;
    float posY = 380;
    float ballPosX = 260;
    float ballPosY = 360;
    float dx = 6, dy = 5;

    int vie = 1;
    int score = 0;

    Font arial; 
    arial.loadFromFile("arial.ttf");

    Text score1;
    score1.setFont(arial);
    score1.setCharacterSize(16);
    score1.setFillColor(Color::Red);
    score1.setPosition(500, 400);

    // création de la balle
    CircleShape ball(size);
    ball.setFillColor(Color::Red);
    ball.setPosition(ballPosX - size, ballPosY);
    // création de la raquette
    RectangleShape racket({ racketLength, racketHeight });
    racket.setFillColor(Color::White);
    racket.setPosition(posX - (racketLength / 2), posY);

    // Intialisation du tableau de briques
    RectangleShape brick[10][4];

    // création des briques
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= 4; j++) {
            brick[i][j].setSize(Vector2f(brickLength, brickHeight));
            brick[i][j].setFillColor(Color::White);
            brick[i][j].setPosition(i * brickLength + i, j * brickHeight + j);
        }
    }

    while (window.isOpen())
    {

        window.clear();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }


        ballPosX += dx;
        for (int i = 0; i <= 10; i++)
            for (int j = 0; j <= 4; j++){
                if (FloatRect(ballPosX + 3, ballPosY + 3, 6, 6).intersects(brick[i][j].getGlobalBounds())){
                    brick[i][j].setPosition(-100, 0); dx = -dx;
                    score++;
                }
            }
            
        ballPosY += dy;
        for (int i = 0; i <= 10; i++)
            for (int j = 0; j <= 4; j++){
                if (FloatRect(ballPosX + 3, ballPosY + 3, 6, 6).intersects(brick[i][j].getGlobalBounds())) {
                    brick[i][j].setPosition(-100, 0); dy = -dy;
                    score++;
                }
            }
            
        if (ballPosX < 0 || ballPosX > 520 - size) {
            dx = -dx;
        }

        if (ballPosY < 0) { 
            dy = -dy; 
        }

        if (Keyboard::isKeyPressed(Keyboard::Right) && posX + (racketLength / 2) + 8 <= windowLength) {
            posX += 8;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) && posX - (racketLength / 2) - 8 >= 0) {
            posX -= 8;
        }
        racket.setPosition(posX - (racketLength / 2), posY);

        if (FloatRect(ballPosX, ballPosY, 12, 12).intersects(racket.getGlobalBounds())){
            dy = -(rand() % 5 + 1);
        }


        for (int i = 0; i <= 10; i++){
            for (int j = 0; j <= 4; j++){
                window.draw(brick[i][j]);
            }
        }
        if (ballPosY > posY) {
            vie--;
        }

        if (vie > 0) {
            ball.setPosition(ballPosX, ballPosY);
        } else if (vie == 0) {

            window.close();
        }

        window.draw(ball);
        window.draw(racket);
        std::string Score_str = std::to_string(score);
        score1.setString(Score_str);
        window.draw(score1);
        window.display();
    }

    return 0;
}