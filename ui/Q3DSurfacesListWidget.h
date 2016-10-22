#pragma once

#include <vector>
#include <QListWidget>
#include <QModelIndex>

#include "infrastructure/ApplicationContextProvider.h"
#include "infrastructure/PropertyChangedHandler.h"
#include "infrastructure/ContainerChangedHandler.h"

class Type;
class Q3DSurfacesListWidget : public QListWidget, public ApplicationContextProvider,
        public ContainerChangedHandler, public PropertyChangedHandler
{
    Q_OBJECT
public:
    Q3DSurfacesListWidget(QListWidget *_parent = nullptr);
    virtual ~Q3DSurfacesListWidget();

    void setContext(ApplicationContext *_context) override;

public slots:
    void selectionChanged();
    void changeColor(QModelIndex _index);

private:
    void propertyChanged(Type *_source, const std::string &_propertyName) override;
    void notifyContainerChanged(const std::shared_ptr<Type> &_object, ContainerChangeType _changeType) override;

    std::vector<Type*> mSurfacesList;
};
