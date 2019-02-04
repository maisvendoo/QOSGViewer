#ifndef     SETTINGS_H
#define     SETTINGS_H

#include    <QString>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct settings_t
{
    QString         title;
    int             x;
    int             y;
    int             width;
    int             height;
    bool            decoration;
    bool            double_buffer;
    unsigned int    samples;
    double          fovy;
    double          zNear;
    double          zFar;

    settings_t()
        : title("OSG models viewer")
        , x(200)
        , y(200)
        , width(1280)
        , height(720)
        , decoration(true)
        , double_buffer(true)
        , samples(4)
        , fovy(30.0)
        , zNear(10.0)
        , zFar(1000.0)
    {

    }
};

#endif // SETTINGS_H
