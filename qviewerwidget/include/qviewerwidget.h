#ifndef     QVIEWER_WIDGET_H
#define     QVIEWER_WIDGET_H

#include    <QWidget>
#include    <QtGlobal>

#include    <osgViewer/Viewer>
#include    <osgQt/GraphicsWindowQt>

#include    "settings.h"

#if defined(QVIEWER_WIDGET_LIB)
    #define QVIEWER_EXPORT  Q_DECL_EXPORT
#else
    #define QVIEWER_EXPORT  Q_DECL_IMPORT
#endif

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class QVIEWER_EXPORT QViewerWidget : public QWidget
{
public:

    QViewerWidget(const QRect &geometry);

    virtual ~QViewerWidget();

    osg::Group *getScene();

    osgViewer::Viewer *getViewer();

protected:

    osg::ref_ptr<osg::Group> scene;

    osgViewer::Viewer   viewer;

private:

    settings_t  settings;

    osgQt::GraphicsWindowQt *createGraphicsWindow(const QRect &geometry);

    void initCamera(const QRect &geometry);

    void paintEvent(QPaintEvent *);
};

#endif // QVIEWER_WIDGET_H
