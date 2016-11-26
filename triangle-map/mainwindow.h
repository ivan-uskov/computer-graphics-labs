#pragma once
#include <QMainWindow>
#include <memory>
#include "model/point.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = 0);

private slots:
    void updateComboTriangles();

private:
    void updateComboTriangle(Points & points, size_t current);
    void setInitialTriangles();
    void bindSliderEvents();
    void loadImages();

    std::shared_ptr<Ui::MainWindow> m_ui;
};
