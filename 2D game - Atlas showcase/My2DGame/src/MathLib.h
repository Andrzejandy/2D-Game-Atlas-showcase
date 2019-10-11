#include <math.h>
#include <SFML/Graphics.hpp>
#define PI 3.14159265358979323846

   inline double DistanceTwoPoints(double const& X0, double const& Y0, double const& X1, double const& Y1)
    {
        return sqrt((X1-X0)*(X1-X0)+(Y1-Y0)*(Y1-Y0));
    }

    inline double DotProduct(float const& uX, float const& uY, float const& vX, float const& vY)
    {
        return sqrt(uX*vX + uY*vY);
    }

    inline bool AABBCol(float const& min_ax, float const& max_ax, float const& min_ay, float const& max_ay,
                      float const& min_bx, float const& max_bx, float const& min_by, float const& max_by)
    {
      if(max_ax < min_bx || min_ax > max_bx) return false;
      if(max_ay < min_by || min_ay > max_by) return false;

      return true;
    }

    inline bool CircleCol(float x_posx, float x_posy, float x_radius, float y_posx, float y_posy, float y_radius )
    {
        float r = x_radius + y_radius;
        r *= r;
        if(r < (x_posx + y_posx)*(x_posx+y_posy) + (x_posy + y_posy)*(x_posx+y_posy))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

/*
    sf::Vector2f VectorReflection(sf::Vector2f const& U, sf::Vector2f const& V)
    {
        float dotproduct = sqrt(U.x*V.x + U.y*V.y);
        return 2*dotproduct*V-U;
    }

    sf::Vector2f rotatePoint(sf::Vector2f const& point, sf::Vector2f const& center, float const& angle)
    {
        float x = center.x + (point.x - center.x)*cos(angle*(PI/180)) - (point.y - center.y)*sin(angle*(PI/180)) ;
        float y = center.y + (point.x - center.x)*sin(angle*(PI/180)) + (point.y - center.y)*cos(angle*(PI/180)) ;
        return sf::Vector2f(x,y) ;
    }

    sf::Vector2f Interpolate(sf::Vector2& V0, sf::Vector2& V1,	float value)
    {
        if( value > 1.0f ){
            value = 1.0f;}

        else if( value < 0.0f ){
            value = 0.0f;}

        return V0 + (V1 - V0) * value;
       //     value+=(App.GetFrameTime() * speed);
       //     sprite.SetPosition(Interpolate(V0, V1, value));
    }
*/

