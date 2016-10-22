#include "MeshIOController.h"
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <algorithm>
#include <QMessageBox>

#include "core/TriMesh.h"
#include "infrastructure/ApplicationContext.h"
#include "infrastructure/ApplicationDatastore.h"
#include "infrastructure/Event.h"
#include "events/Read3DObjectEvent.h"
#include "events/Write3DObjectEvent.h"
#include "services/RandomColorGenerator.h"

MeshIOController::MeshIOController()
{}

MeshIOController::~MeshIOController()
{
    if(context())
    {
        unsubscribeToEvents(context());
    }
}

void MeshIOController::notify(const std::shared_ptr<Event> &_event)
{
    if (auto read3DObjectEvent = std::dynamic_pointer_cast<Read3DObjectEvent>(_event))
    {
        handleRead3DObjectEvent(read3DObjectEvent);
    }
    else if (auto write3DObjectEvent = std::dynamic_pointer_cast<Write3DObjectEvent>(_event))
    {
        handleWrite3DObjectEvent(write3DObjectEvent);
    }
}

void MeshIOController::setContext(ApplicationContext *_context)
{
    mContext = _context;
    subscribeToEvents(context());
}

void MeshIOController::handleRead3DObjectEvent(const std::shared_ptr<Read3DObjectEvent> &_event)
{
    auto mesh = std::make_shared<TriMesh>();
    if (OpenMesh::IO::read_mesh(*mesh, _event->meshFileName))
    {
        auto object = std::make_shared<ThreeDObject>();
        object->setMesh(mesh);
        object->setName(getMeshNameFromFileName(_event->meshFileName));
        object->setColor(RandomColorGenerator::generateRandomColor());

        if (context())
        {
            context()->dataStore()->insertObject(object);
        }
    }
}

void MeshIOController::handleWrite3DObjectEvent(const std::shared_ptr<Write3DObjectEvent> &_event)
{
    OpenMesh::IO::write_mesh(*_event->object->getMesh(), _event->meshFileName);
}

std::string MeshIOController::getMeshNameFromFileName(const std::string &_fileName) const
{
    auto checkSeparator = [](const char& ch) -> bool
    {
        return ch == '\\' || ch == '/';
    };

    return std::string(std::find_if(_fileName.rbegin(), _fileName.rend(), checkSeparator).base(), _fileName.end());
}
