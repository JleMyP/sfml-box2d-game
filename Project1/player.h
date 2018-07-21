#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>



class Player {
public:
    Player(float radius, b2World* world, float startX = 0, float startY = 0, float speed = 0);
    ~Player();

    void Update();
    void draw(sf::RenderWindow* window);

    sf::Vector2f getCenter();

    void setSpeed(sf::Vector2f speed);
    void setAngle(float angle);


    float radius;
    float moveSpeed;
    float angle;

    sf::CircleShape sprite;
    sf::Texture texture;

    b2CircleShape shape;
    b2World* world;
    b2Body* body;
};