#pragma once
#include <QWidget>
#include <vector>
#include <QColor>
#include "statskeyvaluemodel.h"

class BaseStatsDiagramWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseStatsDiagramWidget(QWidget *parent = 0);

    void setModel(StatsKeyValueModel const& model);

protected:
    struct DiagramElement
    {
        float startAngle;
        float spanAngle;
        QColor color;
    };

    void mouseMoveEvent(QMouseEvent *) override;
    virtual bool isPointInDiagram(QPoint const& point) const = 0;
    virtual QRectF getDiagramRect() const = 0;
    virtual QVector2D getBaseVector() const = 0;

    float m_rotateAngle = 0;
    std::vector<DiagramElement> m_elements;

private:

    void buildElementMap(StatsKeyValueModel const& model);

    std::vector<QColor> m_colors;
    std::vector<QPoint> m_movePoints;
};
