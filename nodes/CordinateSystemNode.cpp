#include "CordinateSystemNode.h"

#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/MatrixTransform>

CoordinateSystemNode::CoordinateSystemNode()
    : osg::Transform()
{
    build();
}

CoordinateSystemNode::CoordinateSystemNode(const CoordinateSystemNode &fCopy, const osg::CopyOp &fCopyOp)
    : osg::Transform(fCopy, fCopyOp)
{
    build();
}

void CoordinateSystemNode::build()
{
    auto xAxisTransform = new osg::MatrixTransform;
    xAxisTransform->setMatrix(osg::Matrix::rotate(M_PI/2.0f, osg::Vec3f(0, 1, 0)));
    xAxisTransform->addChild(createArrow(osg::Vec4f(1, 0, 0, 1)));
    xAxisTransform->setName("x-axis");

    auto yAxisTransform = new osg::MatrixTransform;
    yAxisTransform->addChild(createArrow(osg::Vec4f(0, 1, 0, 1)));
    yAxisTransform->setName("y-axis");

    auto zAxisTransform = new osg::MatrixTransform;
    zAxisTransform->setMatrix(osg::Matrix::rotate(M_PI/2.0f, osg::Vec3f(1, 0, 0)));
    zAxisTransform->addChild(createArrow(osg::Vec4f(0, 0, 1, 1)));
    zAxisTransform->setName("z-axis");

    addChild(xAxisTransform);
    addChild(yAxisTransform);
    addChild(zAxisTransform);
}

osg::Node *CoordinateSystemNode::createArrow(const osg::Vec4f &fArrowColor)
{
    const auto arrowShaftRadius = 0.01f;
    const auto arrowTotalLength = 0.1f;

    auto coneRadius = 1.5f * arrowShaftRadius;
    auto coneHeight = coneRadius / 2.0f;
    auto shaftLength = arrowTotalLength - coneHeight;

    auto cylinder = new osg::Cylinder(osg::Vec3(0.0f, 0.0f, shaftLength/2.0f), arrowShaftRadius, shaftLength);
    auto cone = new osg::Cone(osg::Vec3f(0.0f, 0.0f, shaftLength + coneHeight / 4.0f), coneRadius, coneHeight);
    auto sphere = new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), coneRadius);

    auto arrowShaft = new osg::ShapeDrawable;
    arrowShaft->setShape(cylinder);
    arrowShaft->setColor(fArrowColor);

    auto arrowHead = new osg::ShapeDrawable;
    arrowHead->setShape(cone);
    arrowHead->setColor(fArrowColor);

    auto originSphere = new osg::ShapeDrawable;
    originSphere->setShape(sphere);
    const osg::Vec4 blackColor(0.0f, 0.0f, 0.0f, 1.0f);
    originSphere->setColor(blackColor);

    auto vectorArrow = new osg::Geode;
    vectorArrow->addDrawable(originSphere);
    vectorArrow->addDrawable(arrowHead);
    vectorArrow->addDrawable(arrowShaft);

    return vectorArrow;
}

