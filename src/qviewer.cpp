#include    "qviewer.h"
#include    "qt-events.h"
#include    "basis.h"

#include    <osg/Group>
#include    <osg/GraphicsContext>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QViewer::QViewer(int argc, char *argv[], QObject *parent)
    : QObject(parent)
    , root(new osg::Group)
{
    init(argc, argv);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QViewer::~QViewer()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int QViewer::exec()
{
    return viewer.run();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void QViewer::init(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)

    settings_t settings;

    initDisplay(&viewer, settings);

    viewer.addEventHandler(new QtEventsHandler());

    keyboardHandler = new KeyboardHandler(root.get());
    viewer.addEventHandler(keyboardHandler);

    animManager = new AnimationManager();

    connect(keyboardHandler, &KeyboardHandler::loadAnimations,
            animManager, &AnimationManager::loadAnimations);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void QViewer::initDisplay(osgViewer::Viewer *viewer, settings_t &settings)
{
    if (viewer == nullptr)
        return;    

    root->addChild(createBasis(1.0f));

    viewer->setSceneData(root.get());

    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->x = settings.x;
    traits->y = settings.y;
    traits->width = settings.width;
    traits->height = settings.height;
    traits->windowName = settings.title.toStdString();
    traits->windowDecoration = settings.decoration;
    traits->doubleBuffer = settings.double_buffer;
    traits->samples = settings.samples;

    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());

    osg::Camera *camera = viewer->getCamera();
    camera->setGraphicsContext(gc.get());
    camera->setViewport(0, 0, traits->width, traits->height);
    camera->setClearColor(osg::Vec4(0.7f, 0.7f, 0.7f, 1.0f));
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (traits->height == 0) traits->height = 1;

    double aspect = static_cast<double>(traits->width) / static_cast<double>(traits->height);
    camera->setProjectionMatrixAsPerspective(settings.fovy, aspect, settings.zNear, settings.zFar);
}
