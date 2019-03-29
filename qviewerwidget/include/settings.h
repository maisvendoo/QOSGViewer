//------------------------------------------------------------------------------
//
//      Viewer settings structure (from settings.xml file)
//      (c) maisvendoo
//
//------------------------------------------------------------------------------
/*!
 * \file
 * \brief Viewer settings structure (from settings.xml file)
 * \copyright maisvendoo
 * \author maisvendoo
 * \date
 */

#ifndef     SETTINGS_H
#define     SETTINGS_H

#include    <string>

#include    <osg/Vec3>

/*!
 * \struct
 * \brief Main viewer settings
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct settings_t
{
    /// Vertical view angle
    double          fovy;
    ///
    double          zNear;
    ///
    double          zFar;
    /// Screen number
    unsigned int    screen_number;
    /// Client name for server autorization
    std::string     name;
    /// Set/unset window decorations
    bool            window_decoration;
    /// Set/unset double buffering
    bool            double_buffer;
    /// Set number of anialiasing samples
    bool            samples;

    /// Initial distance of extrnal camera
    float           ext_cam_init_dist;
    /// Initial height of extarnel camera
    float           ext_cam_init_height;
    /// Inital shift of external camera
    float           ext_cam_init_shift;
    /// External camera rotation coefficient
    float           ext_cam_rot_coeff;
    /// External camera motion speed
    float           ext_cam_speed;
    /// External camera speed coeff
    float           ext_cam_speed_coeff;
    /// External camera minimal distance
    float           ext_cam_min_dist;
    /// External camera initial horizontal angle
    float           ext_cam_init_angle_H;
    /// External camera initial vertical angle
    float           ext_cam_init_angle_V;

    /// Free camera initial position
    osg::Vec3       free_cam_init_pos;
    /// Free camera rotation coeff
    float           free_cam_rot_coeff;
    /// Free camera speed
    float           free_cam_speed;
    /// Free camera speed coeff
    float           free_cam_speed_coeff;
    /// Free camera FovY step
    float           free_cam_fovy_step;    

    settings_t()
        : fovy(30.0)
        , zNear(1.0)
        , zFar(1000.0)
        , screen_number(0)
        , name("QOSGViewer")
        , window_decoration(true)
        , double_buffer(true)
        , samples(4)        
        , ext_cam_init_dist(25.0f)
        , ext_cam_init_height(0.0f)
        , ext_cam_init_shift(0.0f)
        , ext_cam_rot_coeff(1.0f)
        , ext_cam_speed(5.0f)
        , ext_cam_speed_coeff(10.0f)
        , ext_cam_min_dist(5.0f)
        , ext_cam_init_angle_H(150.0f)
        , ext_cam_init_angle_V(15.0f)
        , free_cam_init_pos(osg::Vec3(2.5, 0.0, 1.75))
        , free_cam_rot_coeff(1.0f)
        , free_cam_speed(5.0f)
        , free_cam_speed_coeff(10.0f)
        , free_cam_fovy_step(1.0f)        

    {

    }
};

#endif // SETTINGS_H
