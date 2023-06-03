#include <SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include<cstdlib>



class Pipe{
    private:
        float y_top;
        const float width = 100;
        static float velocity;
        sf::RectangleShape *pipe_top;
        sf::RectangleShape *pipe_bottom;
    public:
        Pipe(int x);
        ~Pipe();
        void draw(sf::RenderWindow &window);
        bool is_off_screen();
        void move();
        bool is_collision_single_point(sf::Vector2f point);
        bool is_collision(std::vector<sf::Vector2f> points);
        float get_right_edge();
        void dbg(){pipe_top->setFillColor(sf::Color::Red);pipe_bottom->setFillColor(sf::Color::Red);}

};

class Bird{
    private:
        float x_pos, y_pos;
        float velocity;
        sf::CircleShape *circle;
        sf::Texture texture;
    public:
        Bird();
        ~Bird();
        void draw(sf::RenderWindow &window);
        void move_up();
        void move();
        std::vector<sf::Vector2f> get_points();
        float get_left_point();
        void set_position_dbg(sf::Vector2f new_position);
};