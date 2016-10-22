#pragma once

#include "infrastructure/ModelObject.h"
#include "core/TriMesh.h"

#include <memory>
#include <string>
#include <QColor>

//a mode object class for the 3D shapes
class ThreeDObject : public ModelObject
{
    Q_OBJECT

    Q_PROPERTY(QColor Color READ getColor  WRITE setColor)
    Q_PROPERTY(std::string Name READ getName  WRITE setName)
    Q_PROPERTY(std::shared_ptr<TriMesh> Mesh READ getMesh  WRITE setMesh)

public:
    ThreeDObject();
    virtual ~ThreeDObject();

    QColor getColor() const;
    std::string getName() const;
    std::shared_ptr<TriMesh> getMesh() const;

    void setColor(QColor _color);
    void setName(std::string _name);
    void setMesh(const std::shared_ptr<TriMesh>& _mesh);

private:
    std::string mName;
    QColor mColor;
    std::shared_ptr<TriMesh> mMesh;
};
