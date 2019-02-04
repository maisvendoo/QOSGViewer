#include    "mainwindow.h"
#include    "ui_mainwindow.h"

#include    <QGridLayout>

#include    "basis.h"
#include    "grid.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGridLayout *layout = new QGridLayout;
    viewerWidget = new QViewerWidget(QRect(0, 0, ui->frame->width(), ui->frame->height()));
    layout->addWidget(viewerWidget);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    ui->frame->setLayout(layout);

    connect(&timer, &QTimer::timeout, this, &MainWindow::update);
    timer.start(40);

    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quit);

    viewerWidget->getScene()->addChild(createGrid(1.0f, 1.0f, 20, 20));
    viewerWidget->getScene()->addChild(createBasis(20.0f));
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
