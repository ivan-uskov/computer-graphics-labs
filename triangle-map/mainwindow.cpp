#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils/mymath.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>

namespace
{
    const float DISCRETIZATION_FREQUENCY = 0.5;
}

using namespace std;

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    loadImages();
    setInitialTriangles();
    bindSliderEvents();
}

void MainWindow::updateComboTriangles()
{
    Points points;
    m_ui->combo->clearTriangles();
    auto oneTriangles = m_ui->one->triangles();
    auto twoTriangles = m_ui->two->triangles();

    if (oneTriangles.size() != twoTriangles.size())
    {
        qDebug() << "Different source size!";
        return;
    }

    for (size_t i = 0; i < oneTriangles.size(); ++i)
    {
        updateComboTriangle(points, i);
    }

    m_ui->combo->setPoints(points);
    m_ui->combo->update();
}

void MainWindow::updateComboTriangle(Points & points, size_t current)
{
    auto persents = m_ui->slider->value();
    auto one = m_ui->one->triangles()[current];
    auto two = m_ui->two->triangles()[current];

    auto bounding = one.boundingBox2D().toRect();
    auto trans = MyMath::getTransformation(one, two);
    auto combo = MyMath::interpolateTriangle(one, two, persents);
    auto trans2 = MyMath::getTransformation(one, combo);

    for (float x = bounding.left(); x < bounding.right(); x += DISCRETIZATION_FREQUENCY)
    {
        for (float y = bounding.top(); y < bounding.bottom(); y += DISCRETIZATION_FREQUENCY)
        {

            if (one.has2D(QPointF(x, y)))
            {
                QVector3D twoCord = trans * QVector3D(x, y, 0);
                QVector3D threeCord = trans2 * QVector3D(x, y, 0);
                auto three = QPointF(threeCord.x(), threeCord.y());
                if (two.has2D(QPointF(twoCord.x(), twoCord.y())) && combo.has2D(three))
                {
                    auto oneColor = m_ui->one->image().pixel(x, y);
                    auto twoColor = m_ui->two->image().pixel(twoCord.x(), twoCord.y());

                    auto threeColor = MyMath::interpolateColor(QColor(oneColor), QColor(twoColor), persents);
                    points.push_back({three, threeColor});
                }
            }
        }
    }

    m_ui->combo->addTriangle(combo);
}

void MainWindow::setInitialTriangles()
{
    m_ui->one->addTriangle({QVector3D(31, 86, 0), QVector3D(84, 106, 0), QVector3D(37, 111, 0)});
    m_ui->two->addTriangle({QVector3D(46, 86, 0), QVector3D(89, 101, 0), QVector3D(37, 107, 0)});

    m_ui->one->addTriangle({QVector3D(140, 82, 0), QVector3D(102, 108, 0), QVector3D(150, 113, 0)});
    m_ui->two->addTriangle({QVector3D(140, 74, 0), QVector3D(101, 99, 0), QVector3D(147, 105, 0)});

    m_ui->one->addTriangle({QVector3D(84, 106, 0), QVector3D(92, 79, 0), QVector3D(102, 108, 0)});
    m_ui->two->addTriangle({QVector3D(89, 101, 0), QVector3D(94, 74, 0), QVector3D(101, 99, 0)});

    m_ui->one->addTriangle({QVector3D(31, 86, 0), QVector3D(84, 106, 0), QVector3D(92, 79, 0)});
    m_ui->two->addTriangle({QVector3D(46, 86, 0), QVector3D(89, 101, 0), QVector3D(94, 74, 0)});

    m_ui->one->addTriangle({QVector3D(102, 108, 0), QVector3D(92, 79, 0), QVector3D(140, 82, 0)});
    m_ui->two->addTriangle({QVector3D(101, 99, 0),  QVector3D(94, 74, 0), QVector3D(140, 74, 0)});

    m_ui->one->addTriangle({QVector3D(37, 111, 0), QVector3D(53, 132, 0), QVector3D(84, 106, 0)});
    m_ui->two->addTriangle({QVector3D(37, 107, 0),  QVector3D(54, 131, 0), QVector3D(89, 101, 0)});

    m_ui->one->addTriangle({QVector3D(150, 113, 0), QVector3D(102, 108, 0), QVector3D(147, 128, 0)});
    m_ui->two->addTriangle({QVector3D(147, 105, 0),  QVector3D(101, 99, 0), QVector3D(144, 135, 0)});

    m_ui->one->addTriangle({QVector3D(92, 124, 0), QVector3D(53, 132, 0), QVector3D(84, 106, 0)});
    m_ui->two->addTriangle({QVector3D(94, 122, 0),  QVector3D(54, 131, 0), QVector3D(89, 101, 0)});

    m_ui->one->addTriangle({QVector3D(102, 108, 0), QVector3D(92, 124, 0), QVector3D(147, 128, 0)});
    m_ui->two->addTriangle({QVector3D(101, 99, 0),  QVector3D(94, 122, 0), QVector3D(144, 135, 0)});

    m_ui->one->addTriangle({QVector3D(102, 108, 0), QVector3D(92, 124, 0), QVector3D(84, 106, 0)});
    m_ui->two->addTriangle({QVector3D(101, 99, 0),  QVector3D(94, 122, 0), QVector3D(89, 101, 0)});
}

void MainWindow::bindSliderEvents()
{
    connect(m_ui->slider, SIGNAL(valueChanged(int)), this, SLOT(updateComboTriangles()));
    updateComboTriangles();
}

void MainWindow::loadImages()
{
    QSize scaleSize(m_ui->one->rect().width(), m_ui->one->rect().height());

    QImage image("../triangle-map/res/jolee.png");
    m_ui->one->setImage(image.scaled(scaleSize));

    image.load("../triangle-map/res/brad.png");
    m_ui->two->setImage(image.scaled(scaleSize));
}
