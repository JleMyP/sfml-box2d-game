#include "player.h"


#define SCALE 30.f
#define DEG 57.29577f



Player::Player(float radius, b2World* world, float startX, float startY, float speed): radius(radius), moveSpeed(speed), world(world) {
    sprite.setRadius(radius);
    sprite.setOrigin(radius, radius);
    sprite.setFillColor(sf::Color::Green);

    b2BodyDef bdef;
    bdef.type = b2_dynamicBody;
    bdef.position.Set(startX / SCALE, startY / SCALE);

    shape.m_radius = radius / SCALE;

    body = world->CreateBody(&bdef);
    body->CreateFixture(&shape, 2);
}

Player::~Player() {
    //world->DestroyBody(body);
}


sf::Vector2f Player::getCenter() {
    b2Vec2 pos = body->GetPosition();
    sf::Vector2f vec;
    
    vec.x = pos.x * SCALE;
    vec.y = pos.y * SCALE;

    return vec;
}


void Player::Update() {
    b2Vec2 pos = body->GetPosition();
    sprite.setPosition(pos.x * SCALE, pos.y * SCALE);
}


void Player::draw(sf::RenderWindow* window) {
    window->draw(sprite);
}


void Player::setSpeed(sf::Vector2f speed) {
    sf::Vector2f vec = speed * moveSpeed;
    body->SetLinearVelocity(b2Vec2(vec.x, vec.y));
}


void Player::setAngle(float angle) {
    this->angle = angle;

}