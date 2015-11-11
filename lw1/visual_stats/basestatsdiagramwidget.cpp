#include "basestatsdiagramwidget.h"
#include "mymath.h"
#include <algorithm>
#include <QMouseEvent>
#include <QDebug>

namespace
{
    const int MAX_DELTHA_ANGLE = 5;
}

BaseStatsDiagramWidget::BaseStatsDiagramWidget(QWidget *parent)
    : QWidget(parent)
    , m_colors({Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::gray})
{
}

void BaseStatsDiagramWidget::setModel(StatsKeyValueModel const& model)
{
    buildElementMap(model);
    emit repaint();
}

void BaseStatsDiagramWidget::buildElementMap(StatsKeyValueModel const& model)
{
    auto valueSum = model.commonValue();
    auto color = m_colors.begin();
    float currentAngle = MyMath::FULL_RING_D;

    m_elements.clear();
    std::for_each(model.begin(), model.end(), [this, valueSum, &currentAngle, &color](StatsKeyValueModel::Item const& item)
    {
        auto angle = ((static_cast<float>(item.second) / valueSum)) * MyMath::FULL_RING_D;
        this->m_elements.push_back({currentAngle, angle, *(color++)});
        currentAngle += angle;

        if (color == this->m_colors.end())
        {
            color = this->m_colors.begin();
        }
    });
}

void BaseStatsDiagramWidget::mouseMoveEvent(QMouseEvent * event)
{
    auto movePoint = event->pos();

    if (isPointInDiagram(movePoint))
    {
        if (!m_movePoints.empty())
        {
            auto oldPoint = m_movePoints.back();
            m_movePoints.pop_back();

            QVector2D baseVector(getBaseVector());
            QVector2D oldVector(oldPoint - getDiagramRect().center());
            QVector2D moveVector(movePoint - getDiagramRect().center());

            auto delthaAngle = MyMath::vectorsAngle(moveVector, baseVector) - MyMath::vectorsAngle(oldVector, baseVector);

            if (abs(delthaAngle) < MAX_DELTHA_ANGLE)
            {
                m_rotateAngle += moveVector.y() > 0 ? delthaAngle  * -1 : delthaAngle;
                emit repaint();
            }
        }

        m_movePoints.push_back(movePoint);
    }
}
