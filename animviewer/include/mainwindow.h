#ifndef     MAINWINDOW_H
#define     MAINWINDOW_H

#include    <QMainWindow>
#include    <QTimer>
#include    <QSettings>

#include    <osg/Node>
#include    <osgAnimation/BasicAnimationManager>

#include    "qviewerwidget.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
namespace Ui
{
    class MainWindow;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:

    Ui::MainWindow          *ui;

    QViewerWidget           *viewerWidget;

    QSettings               *settings;

    QString                 openPath;

    osg::ref_ptr<osg::Node> model;

    QTimer                  timer;
    QTimer                  controlTimer;    

    osgAnimation::AnimationList animations;

    osg::ref_ptr<osgAnimation::BasicAnimationManager> manager;

    void paintEvent(QPaintEvent *);

    void loadAnimations(osg::Node *model);

private slots:

    void update();

    void quit();

    void clean();

    void open();

    void play();

    void stop();

    void stopAll();

    void controlsUpdate();
};

#endif // MAINWINDOW_H
