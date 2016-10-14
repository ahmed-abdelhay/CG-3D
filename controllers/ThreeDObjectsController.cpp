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

void ThreeDObjectsController::notify(const std::shared_ptr<Event> &fEvent)
{
    if (auto delete3DObjectEvent = std::dynamic_pointer_cast<DeleteSelected3DObjectEvent>(fEvent))
    {
        handleDeleteSelected3DObjectEvent(delete3DObjectEvent);
    }
    else if (auto changeColorEvent = std::dynamic_pointer_cast<Change3DObjectColorEvent>(fEvent))
    {
        handleChange3DObjectColorEvent(changeColorEvent);
    }
}

void ThreeDObjectsController::setContext(ApplicationContext *fContext)
{
    mContext = fContext;
    subscribeToEvents(context());
}

void ThreeDObjectsController::handleChange3DObjectColorEvent(const std::shared_ptr<Change3DObjectColorEvent> &fEvent)
{
    if (auto object = dynamic_cast<ThreeDObject*>(fEvent->object))
    {
        object->setColor(fEvent->color);
    }
}


void ThreeDObjectsController::handleDeleteSelected3DObjectEvent(const std::shared_ptr<DeleteSelected3DObjectEvent> &fEvent)
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
