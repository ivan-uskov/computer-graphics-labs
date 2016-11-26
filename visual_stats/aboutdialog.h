#pragma once

#include <QDialog>
#include <QTime>
#include <QTimer>
#include <QLine>
#include <QPainter>
#include <vector>

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
    std::vector<QLine> m_initialsFirstName;
    std::vector<QLine> m_initialsLastName;
    std::vector<QLine> m_initialsPatronimic;

    void drawInitials(std::vector<QLine> const& initials, QPainter & painter, float timeY);

    void initInitialsVector();
    void initFirstNameLetter(int x);
    void initLastNameLetter(int x);
    void initPatronymicLetter(int x);
};
