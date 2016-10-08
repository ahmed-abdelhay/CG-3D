#pragma once

#include <osg/Transform>

class CoordinateSystemNode : public osg::Transform
{
public:
    META_Node(osg, CoordinateSystemNode)

    CoordinateSystemNode();
    CoordinateSystemNode(const CoordinateSystemNode& fCopy, const osg::CopyOp& fCopyOp = osg::CopyOp::SHALLOW_COPY);

private:
    void build();
    osg::Node* createArrow(const osg::Vec4f& fArrowColor);
};
