#pragma once

#include "infrastructure/ApplicationContextProvider.h"
#include <QWidget>

namespace Ui { class LassoToolsWidget;}

class LassoToolsWidget : public QWidget, public ApplicationContextProvider
{
    Q_OBJECT

public:
    LassoToolsWidget(QWidget *parent = nullptr);
    ~LassoToolsWidget();

    void setContext(ApplicationContext *fContext) override;

private slots:
    void on_actionPolygonalLassoClicked_toggled();

private:
    Ui::LassoToolsWidget *mUi;
};
