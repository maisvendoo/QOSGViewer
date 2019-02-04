#ifndef     KEYBOARD_H
#define     KEYBOARD_H

#include    <osgGA/GUIEventHandler>
#include    <osgViewer/Viewer>

#include    <QObject>
#include    <QString>
#include    <QSettings>
#include    <QMetaType>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class KeyboardHandler : public QObject, public osgGA::GUIEventHandler
{
    Q_OBJECT

public:

    KeyboardHandler(osg::Group *root, QObject *parent = Q_NULLPTR);

    virtual bool handle(const osgGA::GUIEventAdapter &ea,
                        osgGA::GUIActionAdapter &aa);

signals:

    void loadAnimations(osg::Node *model);

private:

    osg::Group *root;

    QString openPath;

    QSettings *settings;

    osg::Node *prevModel;

    void eventKeyDown(int key);

    void loadModel();
};

Q_DECLARE_METATYPE(osg::Node *)

#endif // KEYBOARD_H
