#pragma once
#include "basestatsdiagramwidget.h"
#include "statskeyvaluemodel.h"
#include <vector>
#include <array>
#include <QTimer>
#include <QTime>

class StatsDiagram3DWidget : public BaseStatsDiagramWidget
{
    Q_OBJECT
public:
    explicit StatsDiagram3DWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *) override;

    void buildElementMap() override;

private:
    typedef std::array<QVector3D, 4> Polygon;
    typedef std::vector<Polygon> Points;

    struct DiagramElement
    {
        Points points;
        QColor color;
    };

    StatsDiagram3DWidget::Points getElementPoints(float startAngle, float spanAngle) const;
    bool isVisible(Polygon const& polygon) const;

    QTime m_time;
    QTimer m_timer;
    int m_radius = 100;
    int m_height = 10;
    std::vector<DiagramElement> m_elements;
};
