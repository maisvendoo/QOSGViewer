#ifndef     KEYBOARD_H
#define     KEYBOARD_H

#include    <osgGA/GUIEventHandler>
#include    <osgViewer/Viewer>

#include    <QString>
#include    <QSettings>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class KeyboardHandler : public osgGA::GUIEventHandler
{
public:

    KeyboardHandler(osg::Group *root);

    virtual bool handle(const osgGA::GUIEventAdapter &ea,
                        osgGA::GUIActionAdapter &aa);

private:

    osg::Group *root;

    QString openPath;

    QSettings *settings;

    osg::Node *prevModel;

    void eventKeyDown(int key);

    void loadModel();
};

#endif // KEYBOARD_H
