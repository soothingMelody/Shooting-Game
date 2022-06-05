#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>

class AnimatedAsset : public sf::Sprite{
public:
    float up_edge, down_edge, left_edge, right_edge, up, down, left, right, t_;
    int speedX, speedY, fps_ = 10;
    unsigned int fragments_index = 0;
    std::vector<sf::IntRect> running_frames;

    void setWindowBounds(const float& up_edge_, const float& down_edge_, const float& left_edge_, const float& right_edge_){
        up_edge = up_edge_;
        down_edge = down_edge_;
        left_edge = left_edge_;
        right_edge = right_edge_;
    }

    void setAssetBounds(){
        up = getGlobalBounds().top;
        down = getGlobalBounds().top+getGlobalBounds().height;
        left = getGlobalBounds().left;
        right = getGlobalBounds().left+getGlobalBounds().width;
    }

    void ifEdge(){

        setAssetBounds();

        if (up <= 0 || down >= 600){
            speedY = speedY*-1;
        }
        if (left <= 0 || right >= 800){
            speedX = speedX*-1;
        }
    }



    void VerticalSpeed(const int speed){ speedY = speed; };

    void HorizontalSpeed(const int speed){ speedX = speed; };

    void Move (sf::Time &elapsed){
        float time = elapsed.asSeconds();
        move (speedX*time,speedY*time);
    }



    void addAnimationFrame(const sf::IntRect& frame)
    {
        if(running_frames.size() >= 6)
        {
            running_frames.erase(running_frames.begin(),running_frames.end());
        }
        running_frames.emplace_back(frame);
    }

    void Animate (const sf::Time &elapsed)
    {
        float dt = elapsed.asSeconds();
        t_ = t_ + dt;

        if(t_ > 1.0/fps_)
        {
            fragments_index++;
            t_ = 0.0;
            if(fragments_index == running_frames.size())
            {
                fragments_index = 0;
            }
        }
        setTextureRect(running_frames[fragments_index]);
    }


};

class Bullet : public AnimatedAsset{
public:

    sf::Texture texture_;

    float d_ = 0.0, t_ = 0.0, goalX, goalY;


    Bullet(  const std::string& path)
    {
        if (!texture_.loadFromFile(path)) {
            std::cerr << "Could not load texture" << std::endl;
        }
        setTexture(texture_);
        setPosition(200,200);
    }



};

int main()
{



       sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

       Bullet bulletE("C:/Users/agama/Desktop/Szkola/Qt Projects/textures/bulletSpriteSheet.png");
       bulletE.setWindowBounds(0, window.getSize().y, 0, window.getSize().x);
       bulletE.HorizontalSpeed(rand()%250 );
       bulletE.VerticalSpeed(rand()%250 );

       sf::Clock clock;

       bulletE.setScale(10,10);

           bulletE.addAnimationFrame(sf::IntRect(0, 12, 10, 10));
           bulletE.addAnimationFrame(sf::IntRect(0, 12, 10, 10));
           bulletE.addAnimationFrame(sf::IntRect(0, 12, 10, 10));
           bulletE.addAnimationFrame(sf::IntRect(12, 12, 10, 10));
           bulletE.addAnimationFrame(sf::IntRect(12, 12, 10, 10));
           bulletE.addAnimationFrame(sf::IntRect(12, 12, 10, 10));

        std::vector<Bullet> bulletsE;

        bulletsE.emplace_back(bulletE);




        for (int i = 0;i<5;i++){

        Bullet bullet1 = bulletE;
        bullet1.HorizontalSpeed(rand()%250 );
        bullet1.VerticalSpeed(rand()%250 );

        bulletsE.emplace_back(bullet1);

        };

        for( auto g: bulletsE){
            std::cout << g.speedX << ' ';
        }

               Bullet bs = bulletsE[1];






       while (window.isOpen()) {

           sf::Time elapsed = clock.restart();
           sf::Event event;

           while (window.pollEvent(event)) {
               if (event.type == sf::Event::Closed)
                   window.close();
           }







           window.clear(sf::Color::Black);



           bulletE.Move(elapsed);
           bulletE.ifEdge();

           bulletE.Animate(elapsed);


           window.draw(bulletE);


           bs.Move(elapsed);
           bs.ifEdge();

           bs.Animate(elapsed);


           window.draw(bs);






           window.display();
       }
    return 0;
}
