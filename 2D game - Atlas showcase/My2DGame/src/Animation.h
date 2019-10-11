#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
    public:
        Animation();
        ~Animation();
      //  Animation(const Animation& other);
      //  Animation& operator=(const Animation& other);

        bool ConstructAnim(std::string TextureFileName, int num_of_frames);
        void DeconstructAnim();
        void FillFrameData(int width, int height, int outline, int columns, float frame_delay);
        void FillFrameData(int width, int height, int outline, int columns, float frame_delay, int frame);
        void Update();

        int Num_Of_Frames;
        float CurrentFrame;
        sf::Sprite AnimationSprite;
        sf::Texture AnimationTexture;
        //Zmienic na private
        struct FrameData
        {
            float FrameDelay;
            int FramePosX;
            int FramePosY;
            int FrameSizeX;
            int FrameSizeY;
        };

        FrameData* frame_animation;
    protected:

    private:
};

#endif // ANIMATION_H
