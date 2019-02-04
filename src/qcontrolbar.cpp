#include    "qcontrolbar.h"
#include    <osgViewer/Viewer>
#include    <osgViewer/ViewerEventHandlers>
#include    <osgQt/QWidgetImage>
#include    <osg/Texture2D>

#include    <QPushButton>
#include    <QVBoxLayout>

QControlBar::QControlBar(QRect geometry)
    : QMainWindow ()
{
    this->setGeometry(geometry);

    this->setLayout(new QVBoxLayout);

    QPushButton *button = new QPushButton("Play");
    this->layout()->addWidget(button);

    osg::ref_ptr<osgQt::QWidgetImage> widgetImage = new osgQt::QWidgetImage(this);

    osg::ref_ptr<osgViewer::InteractiveImageHandler> handler =
            new osgViewer::InteractiveImageHandler(widgetImage.get());

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage(widgetImage.get());

    osg::ref_ptr<osg::Geometry> quad =
    osg::createTexturedQuadGeometry(osg::Vec3(), osg::X_AXIS, osg::Z_AXIS);
    quad->setEventCallback( handler.get() );
    quad->setCullCallback( handler.get() );

    geode = new osg::Geode;
    geode->addDrawable( quad.get() );
    geode->getOrCreateStateSet()->setTextureAttributeAndModes( 0, texture.get() );
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    geode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
}

QControlBar::~QControlBar()
{

}

osg::Geode *QControlBar::getPtr()
{
    return geode.release();
}
