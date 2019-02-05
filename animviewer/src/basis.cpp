#include    "basis.h"

#include    <osg/Geode>
#include    <osg/Material>
#include    <osg/Geometry>
#include    <osg/ShapeDrawable>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Geode *createAxis(const float &size, const osg::Vec4 &color, const osg::Vec3 &dir)
{
    osg::ref_ptr<osg::Geode> axis = new osg::Geode;

    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setAmbient(osg::Material::FRONT_AND_BACK, color);
    material->setDiffuse(osg::Material::FRONT_AND_BACK, color);
    material->setEmission(osg::Material::FRONT_AND_BACK, color);
    axis->getOrCreateStateSet()->setAttribute(material.get());

    float thinkness = 0.005f;
    float length = size - thinkness;
    osg::Vec3 box = osg::Vec3(1.0f, 1.0f, 1.0f) * thinkness + dir * length;

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable;
    shape->setShape(new osg::Box(dir * size / 2.0f, box.x(), box.y(), box.z()));
    shape->setColor(color);
    axis->addDrawable(shape.get());

    return axis.release();
}

osg::Group *createBasis(float axisSize)
{
    osg::ref_ptr<osg::Group> basis = new osg::Group;

    basis->addChild(createAxis(axisSize, osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f), osg::Vec3(1, 0, 0)));
    basis->addChild(createAxis(axisSize, osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f), osg::Vec3(0, 1, 0)));
    basis->addChild(createAxis(axisSize, osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f), osg::Vec3(0, 0, 1)));

    return basis.release();
}
