#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include"entities.hpp"

#define DEBUG false


float Pipe::velocity = 5;

Pipe::Pipe(int x = 0)
{
    y_top = 350+rand()%650;
    pipe_top = new sf::RectangleShape(sf::Vector2f(width, y_top));//width, height
    pipe_bottom = new sf::RectangleShape(sf::Vector2f(width, 1500 - 400 - y_top));//width, height

    pipe_top->setFillColor(sf::Color::Green);
    pipe_top->setOutlineColor(sf::Color::White);
    pipe_top->setOutlineThickness(5);
    pipe_top->setPosition(x,0);


    pipe_bottom->setFillColor(sf::Color::Green);
    pipe_bottom->setOutlineColor(sf::Color::White);
    pipe_bottom->setOutlineThickness(5);
    pipe_bottom->setPosition(x,y_top + 400);
}

Pipe::~Pipe()
{
    delete pipe_top,pipe_bottom;
}

void Pipe::draw(sf::RenderWindow &window)
{
    window.draw(*pipe_top);
    window.draw(*pipe_bottom);
}

bool Pipe::is_off_screen()
{
    bool val = pipe_top->getPosition().x+100<= 0?true:false;
    return val;
}

void Pipe::move()
{
    pipe_top->move(sf::Vector2f(-velocity,0));
    pipe_bottom->move(sf::Vector2f(-velocity,0));
}

bool Pipe::is_collision_single_point(sf::Vector2f point)
{
    float left_x = pipe_top->getPosition().x;
    float right_x = left_x + width;
    if(point.x>left_x&&point.x<right_x)
    {
        //std::cout<<"in x range\n";
        if(point.y>0&&point.y<y_top)
        {
            //std::cout<<point.x<<","<<point.y<<"\n";
            return true;
        }
        
        if(point.y>=y_top+400&&point.y<=1500)
        {
            //std::cout<<point.x<<","<<point.y<<"\n";
            return true;    
        }
        
    }
    return false;
}

bool Pipe::is_collision(std::vector<sf::Vector2f> points)
{
    bool collided = false;
    for(auto p : points)
        collided = collided||is_collision_single_point(p);

    return collided;
}

float Pipe::get_right_edge()
{
    return pipe_top->getPosition().x + width;
}

Bird::Bird()
{
    x_pos = 100;
    y_pos = 750;
    circle = new sf::CircleShape(60, 50);
    circle->setPosition(sf::Vector2f(x_pos, y_pos));

    if (!texture.loadFromFile("assets/bad_birb.png"))
    {
        std::cout<<"No texture found";
    }
    texture.setSmooth(true);
    circle->setTexture(&texture);
}

Bird::~Bird()
{
    delete circle;
}

void Bird::draw(sf::RenderWindow &window)
{
    window.draw(*circle);
    auto pt = get_points();
    
    #if DEBUG
        for(auto point : pt)
        {
        sf::VertexArray line(sf::Lines,2);
        line[0].position = sf::Vector2f(0,0);
        line[1].position = point;
        window.draw(line);
        }
    #endif
}

void Bird::move_up()
{
    velocity = -15;
}

void Bird::move()
{
    y_pos += velocity;
    if(y_pos >= 1500)
        y_pos = 1450;
    if(y_pos <= 0)
        y_pos = 150;
    circle->setPosition(sf::Vector2f(x_pos, y_pos));
    
    velocity += 3;
    if(velocity > 30)
        velocity = 50;
}

std::vector<sf::Vector2f> Bird::get_points()
{
    std::vector<sf::Vector2f> points;
    for(int i = 0; i < circle->getPointCount(); i++)
    {
        points.push_back(circle->getPoint(i) + circle->getPosition());// - sf::Vector2f(circle->getRadius(),circle->getRadius()));
    }
    return points;
}

float Bird::get_left_point()
{
    std::vector<sf::Vector2f> points = get_points();
    float min = 1000000000000;
    for(auto p : points)
    {
        if(p.x <= min)
            min = p.x;
    }
    return min;
}

void Bird::set_position_dbg(sf::Vector2f new_position)
{
    circle->setPosition((sf::Vector2f)new_position);
}