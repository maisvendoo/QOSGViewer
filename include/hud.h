#ifndef     HUD_H
#define     HUD_H

#include    <QObject>
#include    <osgText/Font>
#include    <osgText/Text>

#include    <settings.h>

class HeadUpDisplay : public QObject
{
    Q_OBJECT

public:

    HeadUpDisplay(int widht, int height, QObject *parent = Q_NULLPTR);

    void setFont(const std::string &fontPath);

    osg::Camera *getCamera();

private:

    osg::ref_ptr<osgText::Font> g_font;

    osg::ref_ptr<osg::Camera>   camera;

    osg::Camera *createHUDCamera(int width, int height);

    osgText::Text *createText(const osg::Vec2 &pos,
                              const std::string &content,
                              float size);

    osg::Geode *createLabel(float x, float y, std::string text, float size);
};

#endif // HUD_H
