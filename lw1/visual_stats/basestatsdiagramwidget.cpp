#include "basestatsdiagramwidget.h"

BaseStatsDiagramWidget::BaseStatsDiagramWidget(QWidget *parent)
    : QWidget(parent)
{
}

void BaseStatsDiagramWidget::setModel(StatsKeyValueModel const& model)
{
    m_model = model;
    buildElementMap();
    emit repaint();
}

