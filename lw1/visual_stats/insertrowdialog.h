#pragma once
#include <QDialog>

namespace Ui {
class InsertRowDialog;
}

class InsertRowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertRowDialog(QWidget *parent = 0);
    ~InsertRowDialog();

signals:
    void rowReady(QString text, int value);

private slots:
    void onAccepted();
    void disableSubmitIsEmpty(QString const& newValue);
    void valueFieldChanged(int newValue);

private:
    Ui::InsertRowDialog *ui;
};
