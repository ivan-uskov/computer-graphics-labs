#pragma once
#include "basestatsdiagramwidget.h"
#include "statskeyvaluemodel.h"

class StatsDiagram2DWidget : public BaseStatsDiagramWidget
{
    Q_OBJECT
public:
    explicit StatsDiagram2DWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *) override;

    bool isPointInDiagram(QPoint const& point) const override;
    QRectF getDiagramRect() const override;
    QVector2D getBaseVector() const override;
};
