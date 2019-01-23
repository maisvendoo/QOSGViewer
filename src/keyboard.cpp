#include    "keyboard.h"

#include    <QFileDialog>
#include    <QTranslator>
#include    <osgDB/ReadFile>

#include    "basis.h"

KeyboardHandler::KeyboardHandler(osg::Group *root, QObject *parent)
    : QObject(parent)
    , osgGA::GUIEventHandler()
    , root(root)
    , openPath("")
    , settings(new QSettings("maisvendoo", "RRS", nullptr))
    , prevModel(nullptr)
{
    openPath = settings->value("openPath", QDir::homePath()).toString();
    settings->setValue("openPath", openPath);

    qRegisterMetaType<osg::Node *>();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool KeyboardHandler::handle(const osgGA::GUIEventAdapter &ea,
                             osgGA::GUIActionAdapter &aa)
{
    Q_UNUSED(aa)

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
                                                    tr("Open model File"),
                                                    openPath,
                                                    tr("OpenSceneGraph (*.osg *.osgt *.osgb);; DGLEngine (*.dmd)")
                                                    );

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(filePath.toStdString());

    root->removeChildren(0, root->getNumChildren());

    root->addChild(createBasis(1.0f));
    root->addChild(model.get());

    openPath = QFileInfo(filePath).path();
    settings->setValue("openPath", openPath);

    emit loadAnimations(model.get());
}

