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

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(dir * size);
    geom->setVertexArray(vertices.get());

    osg::ref_ptr<osg::DrawArrays> da = new osg::DrawArrays(osg::PrimitiveSet::LINES,
                                                           0,
                                                           static_cast<int>(vertices->size()));

    geom->addPrimitiveSet(da.get());

    axis->addDrawable(geom.get());

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
