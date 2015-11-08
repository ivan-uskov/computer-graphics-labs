#pragma once
#include "basestatsdiagramwidget.h"
#include <QColor>
#include <QString>
#include <vector>
#include "statskeyvaluemodel.h"

class StatsDiagram2DWidget : public BaseStatsDiagramWidget
{
    Q_OBJECT
public:
    explicit StatsDiagram2DWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;

    void buildElementMap() override;

private:
    struct DiagramElement
    {
        float startAngle;
        float spanAngle;
        QColor color;
    };

    bool isPointInDiagram(QPoint const& point) const;

    float m_rotateAngle = 0;
    std::vector<DiagramElement> m_elements;
    std::vector<QPoint> m_movePoints;
};
