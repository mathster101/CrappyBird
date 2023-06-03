#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include"entities.hpp"
#include<ctime>
#include<cstdlib>
#include<thread>
#include<chrono>

unsigned int score = 0;
bool first_time = true;

int starting_screen(sf::RenderWindow &window)
{
    sf::Text text, score_text, instr;
    sf::Font font;
    sf::Event event;

    if (!font.loadFromFile("assets/Zerafoc.ttf"))
    {
        std::cout<<"Font file is missing!\n";
        return 1;
    }

    text.setFont(font);
    instr.setFont(font);
    score_text.setFont(font);
    text.setCharacterSize(275);
    instr.setCharacterSize(80);
    score_text.setCharacterSize(100);
    text.setFillColor(sf::Color::Red);
    instr.setFillColor(sf::Color::White);
    score_text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(500,200));
    instr.setPosition(sf::Vector2f(770,900));
    score_text.setPosition(sf::Vector2f(800,700));
    

    window.setFramerateLimit(10);
    while(window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//close button
            {
                window.close();
                return 1;
            }
        }

        window.clear();
        text.setString("Crappy Bird");
        instr.setString("press enter to continue");
        window.draw(text);
        window.draw(instr);
        if(first_time == 0)
        {
            score_text.setString("Previous score : " + std::to_string(score));
            window.draw(score_text);
        }
        window.display();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            return 0;
        }

    }

    return 0;
}

int debug_loop(sf::RenderWindow &window)
{
    Bird bird;
    bool is_collided, is_crossed;
    std::vector<Pipe*> pipes;
    sf::Text score_text;
    sf::Font font;
    sf::Event event;

    window.setFramerateLimit(60);    
    first_time = false;
    score = 0;
    if (!font.loadFromFile("assets/Zerafoc.ttf"))
    {
        std::cout<<"Font file is missing!\n";
        return 1;
    }


    score_text.setFont(font);
    score_text.setCharacterSize(75); // in pixels, not points!
    score_text.setFillColor(sf::Color::Red);
    score_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    score_text.setPosition(sf::Vector2f(1000,100));
    
    for(int i = 0; i < 12; i++)
        pipes.push_back(new Pipe(i*400 + 800));
    
    while(window.isOpen())
    {

        window.clear();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//close button
            {
                window.close();
                return 1;    
            }
        }
        
        bird.set_position_dbg((sf::Vector2f)sf::Mouse::getPosition(window));

        // for(auto pipe : pipes)
        // {
        //     pipe->move();
        // }
        for(auto pipe : pipes)
        {
            pipe->draw(window);
        }
        bird.draw(window);

        is_collided = pipes[0]->is_collision(bird.get_points());
        // if(is_collided)
        // {
        //     std::this_thread::sleep_for(std::chrono::seconds(1));      
        //     break;
        // }
        if((pipes[0]->get_right_edge() < bird.get_left_point())&&is_crossed==false)
        {
            score += 1;
            is_crossed = true;
        }

        for(auto it = pipes.end() - 1; it >= pipes.begin(); it--)
        {
            if((*it)->is_off_screen())//check if oob
                {
                    pipes.erase(it);
                    pipes.push_back(new Pipe(pipes[pipes.size() - 1]->get_right_edge() + 400));//add new one offscreen at end
                    is_crossed = false;
                }
        }
        score_text.setString("Score : " + std::to_string(score));
        window.draw(score_text);
        window.display();
    }

    return 0;
}

int main_game_loop(sf::RenderWindow &window)
{
    Bird bird;
    bool is_collided, is_crossed;
    std::vector<Pipe*> pipes;
    sf::Text score_text;
    sf::Font font;
    sf::Event event;

    window.setFramerateLimit(60);    
    first_time = false;
    score = 0;
    if (!font.loadFromFile("assets/Zerafoc.ttf"))
    {
        std::cout<<"Font file is missing!\n";
        return 1;
    }
    score_text.setFont(font);
    score_text.setCharacterSize(75); // in pixels, not points!
    score_text.setFillColor(sf::Color::Red);
    score_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    score_text.setPosition(sf::Vector2f(1800,100));
    
    for(int i = 0; i < 12; i++)//generate pipes
        pipes.push_back(new Pipe(i*400 + 800));
    
    while(window.isOpen())
    {
        window.clear();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//close button
            {
                window.close();
                return 1;    
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))//input to fly
        {
            bird.move_up();
        }
        for(auto pipe : pipes)//move pipes and bird
        {
            pipe->move();
        }
        bird.move();

        for(auto pipe : pipes)
        {
            pipe->draw(window);
        }
        bird.draw(window);

        if((pipes[0]->get_right_edge() < bird.get_left_point())&&is_crossed==false)//check if pipe has been crossed
        {
            score += 1;
            is_crossed = true;
        }

        for(auto it = pipes.end() - 1; it >= pipes.begin(); it--)
        {
            if((*it)->is_off_screen())//check if oob
                {
                    pipes.erase(it);
                    //pipes.push_back(new Pipe(1500));//add new one offscreen right
                    pipes.push_back(new Pipe(pipes[pipes.size() - 1]->get_right_edge() + 400));//add new one offscreen at end
                    is_crossed = false;
                }
        }
        score_text.setString("Score : " + std::to_string(score));
        window.draw(score_text);
        window.display();
        is_collided = pipes[0]->is_collision(bird.get_points());//collision check with first pipe
        if(is_collided)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));      
            break;
        }
    }

    return 0;
}


int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(2500, 1500), "Crappy Bird");
    x:
        if(starting_screen(window) == true)
            return 0;
        
        
        if(main_game_loop(window) == true)
            return 0;
        
        // if(debug_loop(window) == 0)
        //     return 0;
        else
            goto x;

    window.close();
    return 0;
}