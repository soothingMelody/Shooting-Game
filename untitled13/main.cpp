#include "game.cpp"

using namespace std;

int main()
{
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    Player player=
    Player(sf::Vector2f(1,1),sf::Vector2f(100,100),sf::Vector2f(300,300));

    player.getExteriorBounds(0,window.getSize().y,0,window.getSize().x);

    sf::Texture playerTXT;                                               //set the texture
    if (!playerTXT.loadFromFile("JennySpriteSheet.png"))
        std::cerr << "Could not load texture" << std::endl;
    player.setTexture(playerTXT);
    player.setTextureRect(sf::IntRect(0,0,63,89));

    player.setOrigin(player.getTextureRect().width/2,player.getTextureRect().height/2);
    sf::Vector2f rotation,MouseCoord;
    sf::Vector2f dir;                                                   //for player movement

    //Crosshead
sf::Sprite crosshead;

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





    while (window.isOpen())
    {
        window.setFramerateLimit(60);
        srand(time(NULL));
        sf::Time elapsed = clock.restart();

        //CALCULATE ROTATION FOLLOWING MOUSE
        MouseCoord=window.mapPixelToCoords(sf::Mouse::getPosition());
        rotation=sf::Vector2f(MouseCoord.x-player.getPosition().x,
                              MouseCoord.y-player.getPosition().y);
        player.setRotation(90+atan2(rotation.y,rotation.x)*180/3.1415);





        ///MOVEMENT SECTION
        //we use different ifs so we can move diagonally
        //outside of Events to move smoothly
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if(player.t_>0)
                dir.y=-player.Speed_.y;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if(player.b_<player.BttScr)
                dir.y=player.Speed_.y;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if(player.l_>0)
                dir.x=-player.Speed_.x;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if(player.r_<player.RgtScr)
                dir.x=player.Speed_.x;
        }

        //if it's at the edges, make the speed in that direction 0
        if(player.t_<=0||player.b_>=player.BttScr)
            dir.y=0;
        if(player.l_<=0||player.r_>=player.RgtScr)
            dir.x=0;

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

        window.draw(player);


        // end the current frame
        window.display();

    }


    return 0;
}
