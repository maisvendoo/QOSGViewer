#ifndef     QCONTROL_BAR_H
#define     QCONTROL_BAR_H

#include    <QWidget>
#include    <QMainWindow>
#include    <osg/Geode>


class QControlBar : public QMainWindow
{
    Q_OBJECT

public:

    QControlBar(QRect geometry);

    ~QControlBar();

    osg::Geode *getPtr();

private:

   osg::ref_ptr<osg::Geode> geode;
};

#endif // QCONTROL_BAR_H
