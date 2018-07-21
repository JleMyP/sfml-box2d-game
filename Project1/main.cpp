#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include <Box2D\Box2D.h>

#include <iostream>

#include "player.h"



#define SCALE 30.f
#define DEG 57.29577f

b2Vec2 gravity(0, 0);
b2World world(gravity);


std::unique_ptr<sf::RectangleShape> createWall(int x, int y, int w, int h) {
    std::unique_ptr<sf::RectangleShape> shape (new sf::RectangleShape(sf::Vector2f(w * 2, h * 2)));
    shape->setOrigin(w, h);
    shape->setPosition(x, y);

    b2PolygonShape gr;
    gr.SetAsBox(w / SCALE, h / SCALE);

    b2BodyDef bdef;
    bdef.position.Set(x / SCALE, y / SCALE);

    b2Body *b_ground = world.CreateBody(&bdef);
    b_ground->CreateFixture(&gr, 1);

    return shape;
}


int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");

    sf::Font font;
    sf::Text text;

    if (!font.loadFromFile("Jelly Donuts.otf")) {
        std::cout << "error" << std::endl;
    } else {
        text.setFont(font);
        text.setString("Hello world");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setPosition(50, 10);
    }

    std::vector<std::unique_ptr<sf::RectangleShape>> walls;
    walls.push_back(createWall(15, 50, 15, 100));
    walls.push_back(createWall(320, 465, 320, 15));
    walls.push_back(createWall(320, 160, 100, 15));

    sf::Clock sfclock;
    Player player(30, &world, 320, 240, 10);


    float zoom = 1;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) window.close();

                if (event.key.code == sf::Keyboard::W && zoom < 4)
                    zoom += 0.25;
                else if (event.key.code == sf::Keyboard::S && zoom > 0.5)
                    zoom -= 0.25;
            }
        }

        sf::Time dt = sfclock.restart();
        world.Step(dt.asSeconds(), 8, 3);
        sf::Vector2f sp;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) sp.x += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  sp.x -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  sp.y -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  sp.y += 1;

        player.setSpeed(sp);
        player.Update();

        sf::View view(sf::FloatRect(0, 0, 640 * zoom, 480 * zoom));
        view.setCenter(player.getCenter());
        window.setView(view);

        window.clear();
        player.draw(&window);
        window.draw(text);

        window.draw(*walls[0]);
        window.draw(*walls[1]);
        window.draw(*walls[2]);
        window.display();
    }


    for (b2Body* it = world.GetBodyList(); it != 0; it = it->GetNext()) {
        //world.DestroyBody(it);
    }

    return 0;
}

