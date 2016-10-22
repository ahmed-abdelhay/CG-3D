#include "ThreeDObjectsController.h"
#include <QMessageBox>

#include "core/TriMesh.h"
#include "infrastructure/ApplicationContext.h"
#include "infrastructure/ApplicationDatastore.h"
#include "infrastructure/Event.h"
#include "events/DeleteSelected3DObjectEvent.h"
#include "events/Change3DObjectColorEvent.h"
#include "modelObjects/ThreeDObject.h"

ThreeDObjectsController::ThreeDObjectsController()
{}

ThreeDObjectsController::~ThreeDObjectsController()
{
    if(context())
    {
        unsubscribeToEvents(context());
    }
}

void ThreeDObjectsController::notify(const std::shared_ptr<Event> &_event)
{
    if (auto delete3DObjectEvent = std::dynamic_pointer_cast<DeleteSelected3DObjectEvent>(_event))
    {
        handleDeleteSelected3DObjectEvent(delete3DObjectEvent);
    }
    else if (auto changeColorEvent = std::dynamic_pointer_cast<Change3DObjectColorEvent>(_event))
    {
        handleChange3DObjectColorEvent(changeColorEvent);
    }
}

void ThreeDObjectsController::setContext(ApplicationContext *_context)
{
    mContext = _context;
    subscribeToEvents(context());
}

void ThreeDObjectsController::handleChange3DObjectColorEvent(const std::shared_ptr<Change3DObjectColorEvent> &_event)
{
    if (auto object = dynamic_cast<ThreeDObject*>(_event->object))
    {
        object->setColor(_event->color);
    }
}


void ThreeDObjectsController::handleDeleteSelected3DObjectEvent(const std::shared_ptr<DeleteSelected3DObjectEvent> &_event)
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
