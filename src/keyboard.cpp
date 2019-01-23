#include    "keyboard.h"

#include    <QFileDialog>
#include    <QTranslator>
#include    <osgDB/ReadFile>

KeyboardHandler::KeyboardHandler(osg::Group *root)
    : root(root)
    , openPath("")
    , settings(new QSettings("maisvendoo", "RRS", nullptr))
    , prevModel(nullptr)
{
    openPath = settings->value("openPath", QDir::homePath()).toString();
    settings->setValue("openPath", openPath);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool KeyboardHandler::handle(const osgGA::GUIEventAdapter &ea,
                             osgGA::GUIActionAdapter &aa)
{
    switch (ea.getEventType())
    {
    case osgGA::GUIEventAdapter::KEYDOWN:
        {
            eventKeyDown(ea.getKey());

            break;
        }

    default:

        break;
    }

    return false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KeyboardHandler::eventKeyDown(int key)
{
    switch (key)
    {
    case osgGA::GUIEventAdapter::KEY_F3:

        loadModel();
        break;

    default:

        break;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KeyboardHandler::loadModel()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr,
                                                    QObject::tr("Open model File"),
                                                    openPath,
                                                    QObject::tr("OpenSceneGraph (*.osg *.osgt *.osgb);; DGLEngine (*.dmd)")
                                                    );

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(filePath.toStdString());

    if (prevModel != nullptr)
        root->removeChild(prevModel);

    root->addChild(model.get());
    prevModel = model.get();

    openPath = QFileInfo(filePath).path();
    settings->setValue("openPath", openPath);
}

