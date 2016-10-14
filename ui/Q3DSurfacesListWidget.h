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
    Q3DSurfacesListWidget(QListWidget *fParent = nullptr);
    virtual ~Q3DSurfacesListWidget();

    void setContext(ApplicationContext *fContext) override;
    void propertyChanged(Type *fSource, const std::string &fPropertyName) override;
    void notifyContainerChanged(const std::shared_ptr<Type> &fObject, ContainerChangeType fChangeType) override;

public slots:
    void selectionChanged();
    void changeColor(QModelIndex fIndex);

private:
    std::vector<Type*> mSurfacesList;
};
