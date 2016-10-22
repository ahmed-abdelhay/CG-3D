#include "LassoToolsWidget.h"
#include "ui_LassoToolsWidget.h"

#include "infrastructure/ApplicationContext.h"
#include "events/LassoToolChangeEvent.h"

#include <memory>

LassoToolsWidget::LassoToolsWidget(QWidget *parent)
    : QWidget(parent),
      mUi(new Ui::LassoToolsWidget)
{
    mUi->setupUi(this);
}

LassoToolsWidget::~LassoToolsWidget()
{}

void LassoToolsWidget::setContext(ApplicationContext *fContext)
{
    mContext = fContext;
}

void LassoToolsWidget::on_actionPolygonalLassoClicked_toggled()
{
    auto event = std::make_shared<LassoToolChangeEvent>();
    event->lassoToolType = LassoToolChangeEvent::LassoToolType::POLYGONAL_LASSO_TOOL;
    event->toolState = mUi->polygonalLassoButton->isChecked();
    mContext->publish(event);
}
