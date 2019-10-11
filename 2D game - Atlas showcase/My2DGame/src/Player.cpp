#include "Player.h"

Player::Player()
{
    playerAngle = 0.0;
    playerDeltaX = 0.0;
    playerDeltaY = 0.0;
    playerPosX = 250;
    playerPosY = 250;
    Up=Down=Left=Right=false;
    MaxSpeed = 2.5;
    SlowingDown = 0.4;
    SlowingUp = 0.6;
    manualFrame = false;
    frameData = 0;
    frameIncrementVal = 0.03;

    if(!LoadAnimations()) { std::cout << "error while loading animations" << std::endl;}

    //ctor
    std::cout << "player class" << std::endl;
}

Player::~Player()
{

}

/* ctor
Player::Player(const Player& other)
{
    //copy ctor
}

Player& Player::operator=(const Player& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
*/

bool Player::LoadAnimations(void)
{
    if(StayAnimation.ConstructAnim("Stay.png",37) == false) {std::cout << "Couldn't load Stay.png" << std::endl; return false;}
     else   {std::cout << "Stay.png loaded" << std::endl;  }
    if(WalkAnimation.ConstructAnim("Walk.png",27) == false) { std::cout << "Couldn't load Walk.png" << std::endl; return false;}
     else { std::cout << "Walk.png loaded" << std::endl; }
    StayAnimation.FillFrameData(407,306,1,7,0.03);
    WalkAnimation.FillFrameData(409,307,1,7,0.03);
    playerSprite.setOrigin(204,158);
	playerSprite.setPosition(playerPosX, playerPosY);
    return true;
}
void Player::HandleMovement()
{
    //Forward
    if(Up && playerSpeed < MaxSpeed)
    {
        if(playerSpeed < 0){ playerSpeed += SlowingDown; }
        else playerSpeed += SlowingUp;
    }

	//Backwards
    if(Down && playerSpeed > -MaxSpeed)
    {
        if(playerSpeed > 0){ playerSpeed -= SlowingDown; }
        else playerSpeed -= SlowingDown;
    }

    if(!Up && !Down)
    {
        if(playerSpeed - SlowingDown > 0) playerSpeed -= SlowingDown;
        else if(playerSpeed + SlowingDown < 0) playerSpeed += SlowingDown;
        else playerSpeed = 0;
    }

    playerPosX += (sin(playerAngle)*playerSpeed);
    playerPosY -= (cos(playerAngle)*playerSpeed);
    playerSprite.setPosition(playerPosX, playerPosY);
    playerSprite.setRotation(playerAngle*180/3.14159);
}

void Player::DrawFrame(sf::RenderWindow &refRenderWindow)
{
    if(manualFrame == false)
    {
        if(playerSpeed != 0)
        {
            playerSprite.setTexture(WalkAnimation.AnimationTexture);
            WalkAnimation.CurrentFrame += 0.3;
            if(WalkAnimation.CurrentFrame >= WalkAnimation.Num_Of_Frames)
            {
                WalkAnimation.CurrentFrame = 1;
            }
            playerSprite.setTextureRect(sf::IntRect(
                                                    WalkAnimation.frame_animation[(int)WalkAnimation.CurrentFrame].FramePosX,
                                                    WalkAnimation.frame_animation[(int)WalkAnimation.CurrentFrame].FramePosY,
                                                    WalkAnimation.frame_animation[(int)WalkAnimation.CurrentFrame].FrameSizeX,
                                                    WalkAnimation.frame_animation[(int)WalkAnimation.CurrentFrame].FrameSizeY));
            refRenderWindow.draw(playerSprite);
        }
        else
        {
            playerSprite.setTexture(StayAnimation.AnimationTexture);
            StayAnimation.CurrentFrame += 0.3;
            if(StayAnimation.CurrentFrame >= StayAnimation.Num_Of_Frames)
            {
                StayAnimation.CurrentFrame = 1;
            }
            playerSprite.setTextureRect(sf::IntRect(
                                                    StayAnimation.frame_animation[(int)StayAnimation.CurrentFrame].FramePosX,
                                                    StayAnimation.frame_animation[(int)StayAnimation.CurrentFrame].FramePosY,
                                                    StayAnimation.frame_animation[(int)StayAnimation.CurrentFrame].FrameSizeX,
                                                    StayAnimation.frame_animation[(int)StayAnimation.CurrentFrame].FrameSizeY));
            refRenderWindow.draw(playerSprite);
        }
    }
}

void Player::DrawFrameNo(int frameIndex, int frameData, sf::RenderWindow &refRenderWindow)
{
    if(frameData<0)
    {
        this->frameData = 0;
        playerSprite.setTexture(StayAnimation.AnimationTexture);
    }
    else if(frameData>1)
    {
        this->frameData = 1;
        playerSprite.setTexture(WalkAnimation.AnimationTexture);
    }
    if(frameData == 0){
        this->frameData = 0;
        playerSprite.setTexture(StayAnimation.AnimationTexture);
    }
    else if(frameData == 1){
        this->frameData = 1;
        playerSprite.setTexture(WalkAnimation.AnimationTexture);
    }
    refRenderWindow.draw(playerSprite);

}

void Player::DrawPlayer(sf::RenderWindow &refRenderWindow)
{
    playerSprite.setTextureRect(sf::IntRect(0,0,64,64));
    refRenderWindow.draw(playerSprite);
}

sf::Sprite Player::GetPlayerSprite(void)
{
    return playerSprite;
}

void Player::SetPlayerSprite(sf::Sprite sprite)
{
    playerSprite = sprite;
}

int Player::GetPlayerTextureFrames(void)
{
    return playerTextureFrames;
}

void Player::SetPlayerTextureFrames(int textureframes)
{
    playerTextureFrames = textureframes;
}

double Player::GetPlayerAngle(void)
{
    return playerAngle;
}

void Player::SetPlayerAngle(double angle)
{
    playerAngle = angle;
}

double Player::GetPlayerDeltaX(void)
{
    return playerDeltaX;
}
double Player::GetPlayerDeltaY(void)
{
    return playerDeltaY;
}
void Player::SetPlayerDeltaX(double deltaX)
{
    playerDeltaX = deltaX;
}
void Player::SetPlayerDeltaY(double deltaY)
{
    playerDeltaY = deltaY;
}

double Player::GetPlayerPosX(void)
{
    return playerPosX;
}
double Player::GetPlayerPosY(void)
{
    return playerPosY;
}
void Player::SetPlayerPosX(double PosX)
{
    playerPosX = PosX;
}
void Player::SetPlayerPosY(double PosY)
{
    playerPosY = PosY;
}
