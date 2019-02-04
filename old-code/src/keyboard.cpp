#include    "keyboard.h"

#include    <QFileDialog>
#include    <QTranslator>
#include    <QMessageBox>
#include    <osgDB/ReadFile>

#include    "basis.h"
#include    "grid.h"

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
                                                    tr("OpenSceneGraph (*.osg *.osgt *.osgb);; DGLEngine (*.dmd)"));

    if (filePath.isEmpty())
        return;

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(filePath.toStdString());

    if (!model.valid())
    {
        QMessageBox msgBox;
        msgBox.setText("ERROR: model is't loaded!");
        msgBox.exec();
        return;
    }

    if (prevModel != nullptr)
        root->removeChild(prevModel);

    root->addChild(model.get());
    prevModel = model.get();

    openPath = QFileInfo(filePath).path();
    settings->setValue("openPath", openPath);

    emit loadAnimations(model.get());
}

