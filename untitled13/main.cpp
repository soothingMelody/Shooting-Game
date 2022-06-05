#include <iostream>
#import "game.cpp"
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <memory>

using namespace std;

int main()
{
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

        ///PLAYER DECLARATION
    Player player=
    Player(sf::Vector2f(1,1),sf::Vector2f(100,100),sf::Vector2f(300,300));

    player.getExteriorBounds(0,window.getSize().y,0,window.getSize().x);

                            //set the texture
    sf::Texture playerTXT;
    if (!playerTXT.loadFromFile("JennySpriteSheet.png"))
        std::cerr << "Could not load texture" << std::endl;
    player.setTexture(playerTXT);
    player.setTextureRect(sf::IntRect(0,0,63,89));

    player.setOrigin(player.getTextureRect().width/2,player.getTextureRect().height/2);
    sf::Vector2f rotation,MouseCoord;
    sf::Vector2f dir;                        //for player movement
        ///PLAYER DECLARATION END


    //Crosshead
    sf::Sprite crosshead;
    sf::Texture crossTXT;
    if (!crossTXT.loadFromFile("crosshead.png"))
        std::cerr << "Could not load texture" << std::endl;

///TO ITERATE OVER BULLETS AND DELETE THEM
//    std::vector<std::unique_ptr<int>> v;
//    for (auto i = v.begin(); i != v.end();)
//    {
//        if(**i>(2))       //pointer to the pointer gives the value
//        {                         //or compare *i with make_unique<int>(2)
//            v.erase(i);
//        }
//        else
//        {
//            i++;          //advance in the vector
//        }
//    }
//The bullets should check individually if they collide with the player,
//take it out of the vector and take away a life

///BULLETS
    Bullet bulletE("bulletSpriteSheet.png");    ///IF YOU AREN'T BLAZE CHANGE THIS
    bulletE.setWindowBounds(0, window.getSize().y, 0, window.getSize().x);
    bulletE.HorizontalSpeed(rand()%100 +300 );
    bulletE.VerticalSpeed(rand()%100 +300 );

    bulletE.setScale(2.5,2.5);

    bulletE.addAnimationFrame(sf::IntRect(0, 12, 10, 10));
    bulletE.addAnimationFrame(sf::IntRect(0, 12, 10, 10));
    bulletE.addAnimationFrame(sf::IntRect(0, 12, 10, 10));
    bulletE.addAnimationFrame(sf::IntRect(12, 12, 10, 10));
    bulletE.addAnimationFrame(sf::IntRect(12, 12, 10, 10));
    bulletE.addAnimationFrame(sf::IntRect(12, 12, 10, 10));

    std::vector<Bullet> bulletsE;  //ALL BULLETS GO HERE
    bulletsE.emplace_back(bulletE);


     for (int i = 0;i<5;i++){

         Bullet bullet1 = bulletE;
         bulletE.HorizontalSpeed(rand()%100 +300 );
         bulletE.VerticalSpeed(rand()%100 +300 );

         bulletsE.emplace_back(bullet1);

     }


    while (window.isOpen())
    {
        window.setFramerateLimit(60);
        srand(time(NULL));
        sf::Time elapsed = clock.restart();

        //CALCULATE ROTATION FOLLOWING MOUSE
        MouseCoord=window.mapPixelToCoords(sf::Mouse::getPosition());
        rotation=sf::Vector2f(MouseCoord.x-player.getPosition().x,
                              MouseCoord.y-player.getPosition().y);
        //ANGLE OF ROTATION
        float angle=90+atan2(rotation.y,rotation.x)*180/3.1415;
        player.setRotation(angle);
        crosshead.setPosition(MouseCoord);


        ///MOVEMENT SECTION
        //we use different ifs so we can move diagonally
        //outside of Events to move smoothly
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if(player.t_>0)
                dir.y=-player.Speed_.y;
            else
                dir.y=player.Speed_.y;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if(player.b_<player.BttScr)
                dir.y=player.Speed_.y;
            else
                dir.y=-player.Speed_.y;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if(player.l_>0)
                dir.x=-player.Speed_.x;
            else
                dir.x=player.Speed_.x;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if(player.r_<player.RgtScr)
                dir.x=player.Speed_.x;
            else
                dir.x=-player.Speed_.x;
        }

        player.DoMove(elapsed,dir);
        ///END OF MOVEMENT SECTION


        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type==sf::Event::KeyPressed)
            {

            }
            //if player stops pressing a movement key, stop moving in that direction
            if(event.type==sf::Event::KeyReleased)
            {
                if(event.key.code==sf::Keyboard::W)
                {
                    dir.y=0;
                }
                if(event.key.code==sf::Keyboard::S)
                {
                    dir.y=0;
                }
                if(event.key.code==sf::Keyboard::A||event.key.code==sf::Keyboard::D)
                {
                    dir.x=0;
                }
            }
            if(event.type == sf::Event::MouseButtonPressed)
              {
                  if(event.mouseButton.button == sf::Mouse::Left)
                  {

                  }
              }
        }


        // clear the window with black color
        window.clear(sf::Color::Black);

        ///DRAW PLAYER UNDER BULLETS
        window.draw(player);

        ///DRAW BULLETS
        for(auto &i:bulletsE){
            i.Move(elapsed);
            i.ifEdge(sf::Vector2f(window.getSize()));
            i.Animate(elapsed);
            window.draw(i);
         };

        window.draw(crosshead);

        // end the current frame
        window.display();

    }


    return 0;
}
