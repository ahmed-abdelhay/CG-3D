#-------------------------------------------------
#
# Project created by QtCreator 2016-09-20T22:02:13
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG-3D
TEMPLATE = app


SOURCES += \
    controllers/ApplicationManager.cpp \
    controllers/SceneGraphManager.cpp \
    core/TriMesh.cpp \
    infrastructure/ApplicationContext.cpp \
    infrastructure/ApplicationContextProvider.cpp \
    infrastructure/ApplicationDatastore.cpp \
    infrastructure/ContainerChangedHandler.cpp \
    infrastructure/ContextChangedPublisher.cpp \
    infrastructure/EventHandler.cpp \
    infrastructure/EventPublisher.cpp \
    infrastructure/ModelObject.cpp \
    infrastructure/PropertyChangedHandler.cpp \
    infrastructure/Type.cpp \
    nodes/CordinateSystemNode.cpp \
    nodes/TriMeshNode.cpp \
    ui/ApplicationMainWindow.cpp \
    ui/OSGWidget.cpp \
    main.cpp \
    services/RandomColorGenerator.cpp \
    modelObjects/ThreeDObject.cpp \
    controllers/MeshIOController.cpp \
    events/Read3DObjectEvent.cpp \
    events/Write3DObjectEvent.cpp \
    ui/MeshIOControlWidget.cpp \
    ui/Q3DSurfacesListWidget.cpp \
    events/DeleteSelected3DObjectEvent.cpp \
    controllers/ThreeDObjectsController.cpp \
    events/Change3DObjectColorEvent.cpp \
    core/Algorithms.cpp \
    modelObjects/PolygonalLasso.cpp \
    ui/LassoToolsWidget.cpp \
    events/LassoToolChangeEvent.cpp \
    controllers/LassoToolsController.cpp \
    events/AddLassoPointEvent.cpp

HEADERS  += \
    controllers/ApplicationManager.h \
    controllers/SceneGraphManager.h \
    core/TriMesh.h \
    infrastructure/ApplicationContext.h \
    infrastructure/ApplicationContextProvider.h \
    infrastructure/ApplicationDatastore.h \
    infrastructure/Common.h \
    infrastructure/ContainerChangedHandler.h \
    infrastructure/ContextChangedPublisher.h \
    infrastructure/Event.h \
    infrastructure/EventHandler.h \
    infrastructure/EventPublisher.h \
    infrastructure/ModelObject.h \
    infrastructure/PropertyChangedHandler.h \
    infrastructure/Type.h \
    nodes/CordinateSystemNode.h \
    nodes/TriMeshNode.h \
    ui/ApplicationMainWindow.h \
    ui/OSGWidget.h \
    services/RandomColorGenerator.h \
    modelObjects/ThreeDObject.h \
    controllers/MeshIOController.h \
    events/Read3DObjectEvent.h \
    events/Write3DObjectEvent.h \
    ui/MeshIOControlWidget.h \
    ui/Q3DSurfacesListWidget.h \
    events/DeleteSelected3DObjectEvent.h \
    controllers/ThreeDObjectsController.h \
    events/Change3DObjectColorEvent.h \
    core/Algorithms.h \
    modelObjects/PolygonalLasso.h \
    ui/LassoToolsWidget.h \
    events/LassoToolChangeEvent.h \
    controllers/LassoToolsController.h \
    events/AddLassoPointEvent.h

FORMS    += \
    ui/MainWindow.ui \
    ui/MeshIOControlWidtet.ui \
    ui/LassoToolsWidget.ui

LIBS += -lOpenThreads -losgViewer -losgText -losg -losgQt -losgUtil -losgDB -lOpenMeshCore -lOpenMeshTools -losgGA

RESOURCES += \
    cg-3d.qrc
