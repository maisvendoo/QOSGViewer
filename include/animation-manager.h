#ifndef     ANIMATION_MANAGER_H
#define     ANIMATION_MANAGER_H

#include    <QObject>
#include    <osg/Node>

class AnimationManager : public QObject
{
    Q_OBJECT

public:

    AnimationManager(QObject *parent = Q_NULLPTR);

    ~AnimationManager();

public slots:

    void loadAnimations(osg::Node *model);

private:


};

#endif // ANIMATION_MANAGER_H
