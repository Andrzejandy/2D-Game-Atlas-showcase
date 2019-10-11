#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
class Player
{
private:
            struct FrameAnimation
        {
            float FrameDelay;
            int FramePosX;
            int FramePosY;
            int FrameSizeX;
            int FrameSizeY;
        };

    public:
        Player();
        ~Player();
      //  Player(const Player& other);
      //  Player& operator=(const Player& other);

        bool LoadAnimations(void);

        int GetPlayerTextureFrames(void);
        void SetPlayerTextureFrames(int textureframes);
        double GetPlayerAngle(void);
        void SetPlayerAngle(double angle);
        double GetPlayerDeltaX(void);
        double GetPlayerDeltaY(void);
        void SetPlayerDeltaX(double deltaX);
        void SetPlayerDeltaY(double deltaY);
        double GetPlayerPosX(void);
        double GetPlayerPosY(void);
        void SetPlayerPosX(double PosX);
        void SetPlayerPosY(double PosY);

        bool LoadPlayerTexture(std::string TextureFileName);
        void DrawPlayer(sf::RenderWindow &refRenderWindow);
        void DrawFrame(sf::RenderWindow &refRenderWindow);
        sf::Sprite GetPlayerSprite(void);
        void SetPlayerSprite(sf::Sprite sprite);

//        FrameAnimation GetFrameData(int FrameIndex);
        void DrawFrameNo(int frameIndex, int frameData, sf::RenderWindow &refRenderWindow);

        void HandleMovement();

        bool manualFrame;
        int frameToRender;
        int frameData;

        bool Up;
        bool Down;
        bool Right;
        bool Left;

        double MaxSpeed;
        double playerSpeed;
        double playerAngle;
        float SlowingDown;
        float SlowingUp;

        float currentFrame;
        float frameIncrementVal;
        int maxFramesNow;
        sf::Sprite playerSprite;

        Animation StayAnimation;
        Animation WalkAnimation;
    protected:

    private:
//        sf::Texture playerTexture;
//        sf::Texture playerTexture_stay;


        double playerPosX;
        double playerPosY;
        double playerDeltaX;
        double playerDeltaY;
        int playerTextureFrames;


     //   FrameAnimation* FrameData;
     //   FrameAnimation* FrameStaying;
};

#endif // PLAYER_H
