#include<libraries.h>


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

    void ifEdge(const sf::Vector2f &screenSize){

        setAssetBounds();

        if (up <= 0 || down >= screenSize.y){
            speedY = speedY*-1;
        }
        if (left <= 0 || right >= screenSize.x){
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


class Player: public AnimatedAsset
{
public:
    float TopScr,BttScr,LftScr,RgtScr,t_,b_,l_,r_;  //limits for collisions
    sf::Vector2f Speed_;
    int lives = 3;

    Player(sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity)
    {
        scale(size);
        setPosition(position);
        Speed_=velocity;
    }
    void setInteriorBounds()        //we save the bounds of the sprite
    {
        t_=getGlobalBounds().top;
        b_=getGlobalBounds().top+getGlobalBounds().height;
        l_=getGlobalBounds().left;
        r_=getGlobalBounds().left+getGlobalBounds().width;

    }
    //we save the bounds of the screen
    ///WE CALL IT ON THE MAIN
    void getExteriorBounds(const double &t, const double &b, const double &l, const double &r)
    {
        TopScr=t;
        BttScr=b;
        LftScr=l;
        RgtScr=r;
    }
    void DoMove(const sf::Time &elapsed, const sf::Vector2f &speed)
    {
        setInteriorBounds();
        move(speed.x*elapsed.asSeconds(),speed.y*elapsed.asSeconds());  //we apply the x-y movement
    }

};


class Bullet : public AnimatedAsset{
public:

    sf::Texture texture_;

    Bullet(const std::string& path)
    {
        if (!texture_.loadFromFile(path)) {
            std::cerr << "Could not load texture" << std::endl;
        }
        setTexture(texture_);
    }
    bool checkCollisions(std::vector<std::unique_ptr<Bullet>>  &v, Bullet b)
    {
        bool t=false;
        for (auto i = v.begin(); i != v.end();)
        {
            if(b.getGlobalBounds().intersects((**i).getGlobalBounds()))
            {
                t=true;
                v.erase(i);

            }
            else i++;
        }
        return t;
    }

};


void moveBackground(sf::View &view , const sf::Time &elapsed){
    int x = 1 * elapsed.asSeconds(); int y = 1.5 * elapsed.asSeconds();
    if (y <= 1200){
        y = y*-1;
    }
    if (x <= 1200){
        x = x*-1;
    }
    view.move(x, y);
}

