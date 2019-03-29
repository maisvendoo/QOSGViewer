#include    "qviewerwidget.h"

#include    <osgViewer/ViewerEventHandlers>
#include    <osgGA/TrackballManipulator>
#include    <osgGA/GUIEventAdapter>

#include    <QGridLayout>

#include    "camera-switcher.h"
#include    "free-manipulator.h"
#include    "train-manipulator.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QViewerWidget::QViewerWidget(const QRect &geometry)
    : QWidget()
    , scene(new osg::Group)
{
    initCamera(geometry);

    viewer.setSceneData(scene);
    viewer.addEventHandler(new osgViewer::StatsHandler);
    viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);

    osgQt::GraphicsWindowQt *gw = static_cast<osgQt::GraphicsWindowQt *>(viewer.getCamera()->getGraphicsContext());

    QGridLayout *layout = new QGridLayout;

    if (layout != Q_NULLPTR)
    {
        layout->addWidget(gw->getGLWidget());
        this->setLayout(layout);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QViewerWidget::~QViewerWidget()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Group *QViewerWidget::getScene()
{
    return scene.get();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osgViewer::Viewer *QViewerWidget::getViewer()
{
    return &viewer;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osgQt::GraphicsWindowQt *QViewerWidget::createGraphicsWindow(const QRect &geometry)
{
    osg::DisplaySettings *ds = osg::DisplaySettings::instance().get();

    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowName = settings.name;
    traits->windowDecoration = false;
    traits->x = geometry.x();
    traits->y = geometry.y();
    traits->width = geometry.width();
    traits->height = geometry.height();

    if (traits->height == 0) traits->height = 1;

    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();

    return new osgQt::GraphicsWindowQt(traits.get());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void QViewerWidget::initCamera(const QRect &geometry)
{
    osg::Camera *camera = viewer.getCamera();

    osg::ref_ptr<osgQt::GraphicsWindowQt> gw = createGraphicsWindow(geometry);
    gw->setTouchEventsEnabled(true);
    camera->setGraphicsContext(gw.get());

    const osg::GraphicsContext::Traits *traits = gw->getTraits();
    camera->setClearColor(osg::Vec4(0.7f, 0.7f, 0.7f, 1.0f));

    camera->setViewport(0, 0, traits->width, traits->height);

    double aspect = static_cast<double>(traits->width) / static_cast<double>(traits->height);
    camera->setProjectionMatrixAsPerspective(settings.fovy, aspect, settings.zNear, settings.zFar);

    // Define camera manipulators
    osg::ref_ptr<TrainManipulator> tm = new TrainManipulator(settings);
    osg::ref_ptr<FreeManipulator>  fm = new FreeManipulator(settings);

    osg::ref_ptr<CameraSwitcher> cs = new CameraSwitcher;
    cs->addMatrixManipulator(osgGA::GUIEventAdapter::KEY_1, "EXTERNAL_CAMERA", tm.get());
    cs->addMatrixManipulator(osgGA::GUIEventAdapter::KEY_2, "FREE_CAMERA", fm.get());

    viewer.setCameraManipulator(cs.get());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void QViewerWidget::paintEvent(QPaintEvent *)
{
    viewer.frame();
}
