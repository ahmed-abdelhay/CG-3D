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
#include "events/DeleteSelected3DObjectEvent.h"
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

void MeshIOController::notify(const std::shared_ptr<Event> &fEvent)
{
    if (auto read3DObjectEvent = std::dynamic_pointer_cast<Read3DObjectEvent>(fEvent))
    {
        handleRead3DObjectEvent(read3DObjectEvent);
    }
    else if (auto write3DObjectEvent = std::dynamic_pointer_cast<Write3DObjectEvent>(fEvent))
    {
        handleWrite3DObjectEvent(write3DObjectEvent);
    }
    else if (auto deleteSelected3DObjectEvent = std::dynamic_pointer_cast<DeleteSelected3DObjectEvent>(fEvent))
    {
        handleDeleteSelected3DObjectEvent(deleteSelected3DObjectEvent);
    }
}

void MeshIOController::setContext(ApplicationContext *fContext)
{
    mContext = fContext;
    subscribeToEvents(context());
}

void MeshIOController::handleRead3DObjectEvent(const std::shared_ptr<Read3DObjectEvent> &fEvent)
{
    auto mesh = std::make_shared<TriMesh>();
    if (OpenMesh::IO::read_mesh(*mesh, fEvent->meshFileName))
    {
        auto object = std::make_shared<ThreeDObject>();
        object->setMesh(mesh);
        object->setName(getMeshNameFromFileName(fEvent->meshFileName));
        object->setColor(RandomColorGenerator::generateRandomColor());

        if (context())
        {
            context()->dataStore()->insertObject(object);
        }
    }
}

void MeshIOController::handleWrite3DObjectEvent(const std::shared_ptr<Write3DObjectEvent> &fEvent)
{
    OpenMesh::IO::write_mesh(*fEvent->object->getMesh(), fEvent->meshFileName);
}

void MeshIOController::handleDeleteSelected3DObjectEvent(const std::shared_ptr<DeleteSelected3DObjectEvent> &fEvent)
{
    if (auto selected3DObject = dynamic_cast<ThreeDObject*>(context()->getSelectedObject()))
    {
        context()->dataStore()->removeObject(selected3DObject->getID());
        context()->setSelectedObject(nullptr);
    }
    else
    {
        QMessageBox::warning(nullptr, tr("Delete 3D object"),
                             tr("there is no selected 3D object"));
    }
}

std::string MeshIOController::getMeshNameFromFileName(const std::string &fFileName) const
{
    auto checkSeparator = [](const char& ch) -> bool
    {
        return ch == '\\' || ch == '/';
    };

    return std::string(std::find_if(fFileName.rbegin(), fFileName.rend(), checkSeparator).base(), fFileName.end());
}
