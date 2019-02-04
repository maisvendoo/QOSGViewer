#include    "grid.h"

#include    <osg/Geode>
#include    <osg/Material>
#include    <osg/Geometry>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Geode *createLine(const osg::Vec3 &p1,
                       const osg::Vec3 &p2,
                       const osg::Vec4 &color)
{
    osg::ref_ptr<osg::Geode> line = new osg::Geode;

    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setAmbient(osg::Material::FRONT_AND_BACK, color);
    material->setDiffuse(osg::Material::FRONT_AND_BACK, color);
    material->setEmission(osg::Material::FRONT_AND_BACK, color);
    line->getOrCreateStateSet()->setAttribute(material.get());

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back(p1);
    vertices->push_back(p2);

    geom->setVertexArray(vertices.get());

    osg::ref_ptr<osg::DrawArrays> da = new osg::DrawArrays(osg::PrimitiveSet::LINES,
                                                           0,
                                                           static_cast<int>(vertices->size()));

    geom->addPrimitiveSet(da.get());

    line->addDrawable(geom.get());

    return line.release();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Group *createGrid(float stepX, float stepY, int nx, int ny)
{
    osg::ref_ptr<osg::Group> grid = new osg::Group;

    float grey = 0.75f;
    osg::Vec4 color(grey, grey, grey, 1.0f);

    for (int i = -ny; i <= ny; ++i)
    {
        osg::Vec3 p1(-nx * stepX, i * stepY, 0.0);
        osg::Vec3 p2( nx * stepX, i * stepY, 0.0);

        grid->addChild(createLine(p1, p2, color));
    }

    for (int i = -nx; i <= nx; ++i)
    {
        osg::Vec3 p1( i * stepX, -ny * stepY, 0.0);
        osg::Vec3 p2( i * stepX,  ny * stepY, 0.0);

        grid->addChild(createLine(p1, p2, color));
    }

    return grid.release();
}
