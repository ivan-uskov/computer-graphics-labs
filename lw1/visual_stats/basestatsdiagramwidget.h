#pragma once
#include <QWidget>
#include "statskeyvaluemodel.h"

class BaseStatsDiagramWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseStatsDiagramWidget(QWidget *parent = 0);

    void setModel(StatsKeyValueModel const & model);

protected:
    virtual void buildElementMap() = 0;

    StatsKeyValueModel m_model;
};
