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
    Q_PROPERTY(QColor color READ getColor  WRITE setColor)
    Q_PROPERTY(std::string name READ getName  WRITE setName)
    Q_PROPERTY(std::shared_ptr<TriMesh> mesh READ getMesh  WRITE setMesh)

public:
    ThreeDObject();
    virtual ~ThreeDObject();

    QColor getColor() const;
    std::string getName() const;
    std::shared_ptr<TriMesh> getMesh() const;

    void setColor(QColor fColor);
    void setName(std::string fName);
    void setMesh(const std::shared_ptr<TriMesh>& fMesh);

private:
    std::string mName;
    QColor mColor;
    std::shared_ptr<TriMesh> mMesh;
};
