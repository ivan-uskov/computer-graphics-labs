#include "insertrowdialog.h"
#include "ui_insertrowdialog.h"
#include <QPushButton>

InsertRowDialog::InsertRowDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InsertRowDialog)
{
    ui->setupUi(this);

    connect(this, SIGNAL(accepted()), this, SLOT(onAccepted()));
    connect(ui->editValue, SIGNAL(valueChanged(int)), this, SLOT(valueFieldChanged(int)));
    connect(ui->editName, SIGNAL(textChanged(QString)), this, SLOT(disableSubmitIsEmpty(QString)));
    connect(ui->editValue, SIGNAL(valueChanged(QString)), this, SLOT(disableSubmitIsEmpty(QString)));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

InsertRowDialog::~InsertRowDialog()
{
    delete ui;
}

void InsertRowDialog::onAccepted()
{
    emit rowReady(ui->editName->text(), ui->editValue->value());
}

void InsertRowDialog::disableSubmitIsEmpty(QString const& newValue)
{
    auto button = ui->buttonBox->button(QDialogButtonBox::Ok);
    if (newValue.trimmed().isEmpty())
    {
        button->setEnabled(false);
    }
    else
    {
        button->setEnabled(true);
    }
}

void InsertRowDialog::valueFieldChanged(int value)
{
    auto button = ui->buttonBox->button(QDialogButtonBox::Ok);
    if (value == 0)
    {
        button->setEnabled(false);
    }
    else
    {
        button->setEnabled(true);
    }
}
