#include "Q3DSurfacesListWidget.h"
#include <QColorDialog>
#include <QColor>

#include "infrastructure/ApplicationContext.h"
#include "infrastructure/SelectionManager.h"
#include "modelObjects/ThreeDObject.h"
#include "infrastructure/Type.h"
#include "events/Change3DObjectColorEvent.h"

Q3DSurfacesListWidget::Q3DSurfacesListWidget(QListWidget* _parent)
    :QListWidget(_parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    QObject::connect(this, SIGNAL(itemSelectionChanged()),
                     this, SLOT(selectionChanged()));

    QObject::connect(this, SIGNAL(doubleClicked(QModelIndex)),
                     this, SLOT(changeColor(QModelIndex)));
}

Q3DSurfacesListWidget::~Q3DSurfacesListWidget()
{
    if (context())
    {
        unsubscribePropertyChangedOnType(ThreeDObjectType, context());
        unsubscribeToContainerChanged(context());
    }
}

void Q3DSurfacesListWidget::setContext(ApplicationContext *_context)
{
    mContext = _context;

    subscribePropertyChangedOnType(ThreeDObjectType, context());
    subscribeToContainerChanged(context());
}

void Q3DSurfacesListWidget::propertyChanged(Type *_source, const std::string &_propertyName)
{
    if (_source->metaObject()->className() == ThreeDObjectType)
    {
        if (_propertyName == NameType)
        {
            for (int i = 0; i < mSurfacesList.size(); ++i)
            {
                auto object = dynamic_cast<ThreeDObject*>(_source);
                item(i)->setText(QString::fromStdString(object->getName()));
            }
        }
    }
}

void Q3DSurfacesListWidget::notifyContainerChanged(const std::shared_ptr<Type> &_object, ContainerChangeType _changeType)
{
    if (_object->metaObject()->className() == ThreeDObjectType)
    {
        auto object = dynamic_cast<ThreeDObject*>(_object.get());
        switch (_changeType)
        {
        case ContainerChangeType::OBJECT_ADDED:
            mSurfacesList.push_back(_object.get());
            insertItem(mSurfacesList.size() - 1, QString::fromStdString(object->getName()));
            break;
        case ContainerChangeType::OBJECT_REMOVED:
            for (int i = 0; i < mSurfacesList.size(); ++i)
            {
                if (_object.get() == mSurfacesList[i])
                {
                    takeItem(i);
                    mSurfacesList.erase(mSurfacesList.begin() + i);
                }
            }
            break;
        }
    }
}

void Q3DSurfacesListWidget::selectionChanged()
{
    if (context())
    {
        for (auto index : selectionModel()->selectedIndexes())
        {
            context()->selectionManager()->setSelectedObject(ThreeDObjectType, mSurfacesList[index.row()]);
        }
    }
}

void Q3DSurfacesListWidget::changeColor(QModelIndex _index)
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if( color.isValid() )
    {
        auto changeColorEvent = std::make_shared<Change3DObjectColorEvent>();
        changeColorEvent->object = mSurfacesList[_index.row()];
        changeColorEvent->color = color;
        context()->publish(changeColorEvent);
    }
}
