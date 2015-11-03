#pragma once

#include <QDialog>
#include <QTime>
#include <QTimer>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

// QWidget interface
protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::AboutDialog *m_ui;
    QTime m_time;
    QTimer m_timer;

    void drawFirstNameLetter(QPainter & painter, int x, int y);
    void drawLastNameLetter(QPainter & painter, int x, int y);
    void drawPatronymicLetter(QPainter & painter, int x, int y);
};
