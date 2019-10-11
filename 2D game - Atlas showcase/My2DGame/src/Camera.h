#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>
#include <iostream>
class Camera
{
    public:
        Camera();
        virtual ~Camera();
        sf::View cameraView;
        //sf::RenderWindow &game_render_window;
        void BindView(sf::RenderWindow &g_window);
        void ChangeViewSize(sf::Vector2f viewsize);
        void ZoomView(float zoom);
        void PanView(float x, float y);

        float Zoom;
    protected:

    private:
};

#endif // CAMERA_H
