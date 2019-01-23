#ifndef     VIEWER_H
#define     VIEWER_H

#include    <osgViewer/Viewer>

#include    <QObject>

#include    "settings.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class   QViewer : public QObject
{
    Q_OBJECT

public:

    QViewer(int argc, char *argv[], QObject *parent = Q_NULLPTR);

    ~QViewer();

    int exec();

private:

    osg::ref_ptr<osg::Group> root;

    osgViewer::Viewer   viewer;

    void init(int argc, char *argv[]);

    void initDisplay(osgViewer::Viewer *viewer, settings_t &settings);
};

#endif // VIEWER_H
