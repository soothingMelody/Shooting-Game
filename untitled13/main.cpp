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
    Player(sf::Vector2f(1,1),sf::Vector2f(1000,500),sf::Vector2f(300,300));

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


    ///CROSSHEAD
    sf::Sprite crosshead;
    crosshead.setScale(1,1);
    sf::Texture crossTXT;
    if (!crossTXT.loadFromFile("crosshead.png"))
        std::cerr << "Could not load texture" << std::endl;
    crosshead.setTexture(crossTXT);
    crosshead.setOrigin(crosshead.getTextureRect().width/2,crosshead.getTextureRect().height/2);

    window.setMouseCursorVisible(false);





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

///BULLETS ENEMY
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

    std::vector<Bullet> bulletsE;  //ALL ENEMY BULLETS GO HERE
    bulletsE.emplace_back(bulletE);

    ///BULLETS ALLY
    Bullet bulletA("bulletSpriteSheet.png");        ///IF YOU AREN'T BLAZE CHANGE THIS
    bulletA.setWindowBounds(0, window.getSize().y, 0, window.getSize().x);
    bulletA.HorizontalSpeed(rand()%100 +300 );
    bulletA.VerticalSpeed(rand()%100 +300 );

    bulletA.setScale(2.5,2.5);

    bulletA.addAnimationFrame(sf::IntRect(0, 0, 10, 10));
    bulletA.addAnimationFrame(sf::IntRect(0, 0, 10, 10));
    bulletA.addAnimationFrame(sf::IntRect(0, 0, 10, 10));
    bulletA.addAnimationFrame(sf::IntRect(12, 0, 10, 10));
    bulletA.addAnimationFrame(sf::IntRect(12, 0, 10, 10));
    bulletA.addAnimationFrame(sf::IntRect(12, 0, 10, 10));

    std::vector<Bullet> bulletsA;  //ALL ALLY BULLETS GO HERE
    bulletsA.emplace_back(bulletA);

    ///MUSIC______________
    sf::Music music;
    if (!music.openFromFile("DigitalOne.ogg"))
        return -1; // error
    music.play();
    music.setLoop(1);
    music.setVolume(50);
    ///__________________________

    ///SFX
    // To play SFX anywhere, just put down:
    // "play.(name of the sound variable)() in the if or while statement.

    //Firing Sound - for firing the player's cannon.
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("fire.ogg"))
            return -1; //Returns an error, if the audio file is missing
    sf::Sound shootSound;
    shootSound.setBuffer(buffer);
    shootSound.setVolume(40); //Use this to set the volume (0-100)

    //BulletDeath Sound - for when the player bullet and enemy bullet collide.
    sf::SoundBuffer buffer2;
    if (!buffer2.loadFromFile("bulletdeath.ogg"))
            return -1; //Returns an error, if the audio file is missing
    sf::Sound bulletDeathSound;
    bulletDeathSound.setBuffer(buffer2);
    bulletDeathSound.setVolume(40); //Use this to set the volume (0-100)

    //Death Sound - for when the player loses a life.
    sf::SoundBuffer buffer3;
    if (!buffer3.loadFromFile("death.ogg"))
            return -1; //Returns an error, if the audio file is missing
    sf::Sound deathSound;
    deathSound.setBuffer(buffer3);
    deathSound.setVolume(40); //Use this to set the volume (0-100)

    //Game Over Sound - for when the player loses all lives.
    sf::SoundBuffer buffer4;
    if (!buffer4.loadFromFile("gameover.ogg"))
            return -1; //Returns an error, if the audio file is missing
    sf::Sound gameoverSound;
    gameoverSound.setBuffer(buffer4);
    gameoverSound.setVolume(40); //Use this to set the volume (0-100)
    ///__________________________

    int b =0;

    while (window.isOpen())
    {
        window.setFramerateLimit(60);
        srand(time(NULL));
        sf::Time elapsed = clock.restart();


        //CALCULATE ROTATION FOLLOWING MOUSE
        MouseCoord = window.mapPixelToCoords(sf::Mouse::getPosition());
        rotation = sf::Vector2f(MouseCoord.x-player.getPosition().x,
                              MouseCoord.y-player.getPosition().y);
        //turn to unit vector
        rotation = sf::Vector2f(rotation.x/sqrt(pow(rotation.x,2)+pow(rotation.y,2)),
                              rotation.y/sqrt(pow(rotation.x,2)+pow(rotation.y,2)));


        //ANGLE OF ROTATION
        float angle=90+atan2(rotation.y,rotation.x)*180/3.1415;
        player.setRotation(angle);
        crosshead.setPosition(MouseCoord);

        if (MouseCoord.y <= 20)     //to see when closing the window
            window.setMouseCursorVisible(true);
        else
            window.setMouseCursorVisible(false);



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

        if (b==100){
            Bullet bullet1 = bulletE;
            bulletE.HorizontalSpeed(rand()%100 +300 );
            bulletE.VerticalSpeed(rand()%100 +300 );

            bulletsE.emplace_back(bullet1);
            bullet1.setPosition(10,10);
            b=0;
        }
        else {
            b++;
        }

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
                if(event.key.code==sf::Keyboard::W||event.key.code==sf::Keyboard::S)
                    dir.y=0;
                if(event.key.code==sf::Keyboard::A||event.key.code==sf::Keyboard::D)
                    dir.x=0;

            }
            if(event.type == sf::Event::MouseButtonPressed)
              {
                  if(event.mouseButton.button == sf::Mouse::Left)
                  {
                        //multiply the rotation by the speed of bullet
                      bulletA.HorizontalSpeed(400*rotation.x);
                      bulletA.VerticalSpeed(400*rotation.y);
                      bulletA.setPosition(player.getPosition());
                      shootSound.play();

                      bulletsA.emplace_back(bulletA);
                  }
              }
        }


        // clear the window with black color
        window.clear(sf::Color::Black);



        ///DRAW ENEMY BULLETS
        for(auto &i:bulletsE){
            i.Move(elapsed);
            i.ifEdge(sf::Vector2f(window.getSize()));
            i.Animate(elapsed);
            window.draw(i);
         }
        ///DRAW PLAYER UNDER ENEMY BULLETS
        window.draw(player);

        ///DRAW ALLY BULLETS
        for(auto &i:bulletsA){
            i.Move(elapsed);
            i.Animate(elapsed);
            window.draw(i);
         }

        window.draw(crosshead);

        // end the current frame
        window.display();

    }


    return 0;
}
