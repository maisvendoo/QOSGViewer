#include    "mainwindow.h"
#include    "ui_mainwindow.h"

#include    <QGridLayout>
#include    <QFileDialog>
#include    <QDir>
#include    <QFileInfo>

#include    <osgDB/ReadFile>

#include    "basis.h"
#include    "grid.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , viewerWidget(Q_NULLPTR)
    , settings(new QSettings("maisvendoo", "RRS", Q_NULLPTR))
    , openPath("./")
    , model(nullptr)
{
    ui->setupUi(this);

    QGridLayout *layout = new QGridLayout;
    viewerWidget = new QViewerWidget(QRect(0, 0, ui->frame->width(), ui->frame->height()));
    layout->addWidget(viewerWidget);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    ui->frame->setLayout(layout);        

    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quit);
    connect(ui->actionClean, &QAction::triggered, this, &MainWindow::clean);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);

    viewerWidget->getScene()->addChild(createGrid(1.0f, 1.0f, 20, 20));
    viewerWidget->getScene()->addChild(createBasis(20.0f));

    ui->twAnimations->setColumnWidth(0, 249);
    ui->twAnimations->setColumnWidth(1, 99);
    ui->twAnimations->setColumnWidth(2, 99);
    ui->twAnimations->verticalHeader()->setDefaultSectionSize(18);

    connect(ui->pbPlay, &QPushButton::released, this, &MainWindow::play);
    connect(ui->pbStop, &QPushButton::released, this, &MainWindow::stop);
    connect(ui->pbStopAll, &QPushButton::released, this, &MainWindow::stopAll);

    connect(&controlTimer, &QTimer::timeout, this, &MainWindow::controlsUpdate);
    controlTimer.start(100);

    openPath = settings->value("openPath", QDir::homePath()).toString();
    settings->setValue("openPath", openPath);    

    connect(&timer, &QTimer::timeout, this, &MainWindow::update);
    timer.start(40);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::paintEvent(QPaintEvent *)
{
    ui->frame->update();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::loadAnimations(osg::Node *model)
{
    if (model == nullptr)
        return;

    manager = dynamic_cast<osgAnimation::BasicAnimationManager *>(model->getUpdateCallback());

    if (manager == nullptr)
        return;

    const osgAnimation::AnimationList &animations = manager->getAnimationList();

    if (animations.size() == 0)
        return;

    ui->pbPlay->setEnabled(true);
    ui->pbIncFrame->setEnabled(true);
    ui->pbDecFrame->setEnabled(true);

    this->animations = animations;

    int i = 1;

    for (auto it = animations.begin(); it != animations.end(); ++it)
    {
        std::string name = (*it)->getName();
        ui->twAnimations->insertRow(i - 1);
        ui->twAnimations->setItem(i - 1, 0, new QTableWidgetItem(QString(name.c_str())));
        ++i;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::update()
{
    QMainWindow::update();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::quit()
{
    QApplication::quit();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::clean()
{
    if (!model.valid())
        return;

    viewerWidget->getScene()->removeChild(model.get());
    ui->twAnimations->setRowCount(0);
    ui->pbDecFrame->setEnabled(false);
    ui->pbIncFrame->setEnabled(false);
    ui->pbPlay->setEnabled(false);
    ui->pbStop->setEnabled(false);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::open()
{
    clean();

    QString path = QFileDialog::getOpenFileName(Q_NULLPTR,
                                                tr("Open model file"),
                                                openPath,
                                                tr("OpenSceneGraph (*.osg *.osgt *.osgb *.ivi)"));
    if (path.isEmpty())
        return;

    openPath = QFileInfo(path).path();
    settings->setValue("openPath", openPath);

    model = osgDB::readNodeFile(path.toStdString());
    viewerWidget->getScene()->addChild(model.get());

    loadAnimations(model.get());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::play()
{
    size_t i = static_cast<size_t>(ui->twAnimations->currentRow());

    if (i > animations.size() - 1)
        return;

    manager->playAnimation(animations[i].get());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::stop()
{
    size_t i = static_cast<size_t>(ui->twAnimations->currentRow());

    if (i > animations.size() - 1)
        return;

    manager->stopAnimation(animations[i].get());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::stopAll()
{
    if (manager.valid())
        manager->stopAll();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::controlsUpdate()
{
    if (animations.size() == 0)
        return;

    size_t i = static_cast<size_t>(ui->twAnimations->currentRow());

    if (i > animations.size() - 1)
        return;

    if (manager->isPlaying(animations[i]))
    {
        ui->pbDecFrame->setEnabled(false);
        ui->pbIncFrame->setEnabled(false);
        ui->pbPlay->setEnabled(false);
        ui->pbStop->setEnabled(true);
    }
    else
    {
        ui->pbDecFrame->setEnabled(true);
        ui->pbIncFrame->setEnabled(true);
        ui->pbPlay->setEnabled(true);
        ui->pbStop->setEnabled(false);
    }
}
