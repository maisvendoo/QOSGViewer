#include    "animation-manager.h"

#include    <QDebug>
#include    <osgAnimation/BasicAnimationManager>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
AnimationManager::AnimationManager(QObject *parent)
    : QObject(parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
AnimationManager::~AnimationManager()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AnimationManager::loadAnimations(osg::Node *model)
{
    if (model == nullptr)
        return;

    osgAnimation::BasicAnimationManager *manager =
            dynamic_cast<osgAnimation::BasicAnimationManager *>(model->getUpdateCallback());

    if (manager == nullptr)
        return;

    const osgAnimation::AnimationList &animations = manager->getAnimationList();

    for (auto it = animations.begin(); it != animations.end(); ++it)
    {
        manager->playAnimation((*it).get());
    }
}
