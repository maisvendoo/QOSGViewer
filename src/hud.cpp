#include    "hud.h"

HeadUpDisplay::HeadUpDisplay(int width, int height, QObject *parent)
    : QObject(parent)
{
    camera = createHUDCamera(width, height);
    camera->addChild(createLabel(10, 10, "F3 - open file", 10.0f));

    camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
}

void HeadUpDisplay::setFont(const std::string &fontPath)
{
    g_font = osgText::readFontFile(fontPath);
}

osg::Camera *HeadUpDisplay::getCamera()
{
    return camera.release();
}

osg::Camera *HeadUpDisplay::createHUDCamera(int width, int height)
{
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder(osg::Camera::POST_RENDER);
    camera->setAllowEventFocus(false);

    camera->setProjectionMatrix(osg::Matrix::ortho2D(0, width,
                                                     0, height));

    return camera.release();
}

osgText::Text *HeadUpDisplay::createText(const osg::Vec2 &pos,
                                         const std::string &content,
                                         float size)
{
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    text->setFont(g_font.get());
    text->setCharacterSize(size);
    text->setAxisAlignment(osgText::TextBase::XY_PLANE);
    text->setPosition(osg::Vec3(pos.x(), pos.y(), 0.0));
    text->setText(content);

    return text.release();
}

osg::Geode *HeadUpDisplay::createLabel(float x, float y,
                                       std::string text,
                                       float size)
{
    osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
    textGeode->addDrawable(createText(osg::Vec2(x, y), text, size));

    return textGeode.release();
}
