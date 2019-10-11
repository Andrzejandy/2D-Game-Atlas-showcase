#include "Camera.h"

Camera::Camera()
{
    //ctor
    Zoom = 1.0f;
}

Camera::~Camera()
{
    //dtor
}

void Camera::PanView(float x, float y)
{
    cameraView.move(x,y);
}

void Camera::ZoomView(float zoom)
{
    Zoom *= zoom;
    cameraView.zoom(zoom);
    std::cout << Zoom << std::endl;
}

void Camera::BindView(sf::RenderWindow &g_window)
{
    cameraView = g_window.getDefaultView();
    Zoom = 0.5f;
    cameraView.zoom(0.5f);
    cameraView.setSize(1600,900);
}

void Camera::ChangeViewSize(sf::Vector2f viewsize)
{
    cameraView.setSize(viewsize);
}
