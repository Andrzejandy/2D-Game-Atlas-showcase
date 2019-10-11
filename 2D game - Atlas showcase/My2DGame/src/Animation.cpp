#include "Animation.h"

Animation::Animation()
{
    frame_animation = NULL;
    //AnimationSprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
    //ctor
    std::cout << "animation class" << std::endl;
}

Animation::~Animation()
{
    std::cout << "deconstructor animation" << std::endl;
    //dtor
}
/*
Animation::Animation(const Animation& other)
{
    //copy ctor
}

Animation& Animation::operator=(const Animation& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
*/
bool Animation::ConstructAnim(std::string TextureFileName, int num_of_frames)
{
    if(!AnimationTexture.loadFromFile("Data\\Textures\\Player\\" + TextureFileName))
    {
        std::cout << "Animation: couldn't load: " << TextureFileName << std::endl;
        return false;
    }
    frame_animation = new FrameData[num_of_frames+1];
    Num_Of_Frames = num_of_frames;
    AnimationSprite.setTexture(AnimationTexture);
    return true;
}

void Animation::DeconstructAnim()
{
    delete frame_animation;
    frame_animation = nullptr;
}

void Animation::FillFrameData(int width, int height, int outline, int columns, float frame_delay)
{
    int modulo_rows = 1;
    for(int frame = 1; frame <= Num_Of_Frames; frame++)
    {
        int modulo_columns = frame % columns;
        int x = (width * modulo_columns) + outline - width;
        int y = (height * modulo_rows) + outline - height;
        if(x<=0) { x = width*(columns-1)+1; }
        //frame_animation[frame] = {5,outline,outline,width-1,height-1};
        frame_animation[frame] = {frame_delay,x,y,width-1,height-1};
        CurrentFrame = frame;
        if(modulo_columns == 0) { modulo_rows++; }
    }
}

void Animation::FillFrameData(int width, int height, int outline, int columns, float frame_delay, int frame)
{
        int modulo_rows = frame % (int)(Num_Of_Frames/columns);
        int modulo_columns = frame % columns;
        int x = (width * modulo_columns) + outline - width;
        int y = (height * modulo_rows) + outline - height;
        if(x<=0) { x = width*(columns-1)+1; }
        //frame_animation[frame] = {5,outline,outline,width-1,height-1};
        frame_animation[frame] = {frame_delay,x,y,width-1,height-1};
        CurrentFrame = frame;
        if(modulo_columns == 0) { modulo_rows++; }
}

void Animation::Update()
{

}
