#pragma once
#include "basestatsdiagramwidget.h"
#include "statskeyvaluemodel.h"
#include <QPainter>
#include "myrange.h"

class StatsDiagram3DWidget : public BaseStatsDiagramWidget
{
    Q_OBJECT
public:
    explicit StatsDiagram3DWidget(QWidget * parent = 0);

protected:
    void paintEvent(QPaintEvent *) override;

    bool isPointInDiagram(const QPoint &point) const override;
    QRectF getDiagramRect() const override;
    QVector2D getBaseVector() const override;

private:
    void drawDiagramElementBottom(QPainter & painter, MyRange const& visibleAngles);
};
