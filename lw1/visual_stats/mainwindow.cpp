#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statstablemodel.h"
#include "statsdocument.h"
#include "insertrowdialog.h"
#include "aboutdialog.h"
#include <QTableView>
#include <QDebug>
#include <unordered_set>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QErrorMessage>

namespace
{
    static const QString HAS_CHANGES_MSG("Has not saved changes");
    static const QString SAVE_QUESTION_MSG("Save?");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    initTableData();
    initDocument();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_newDocument_triggered()
{
    if (verifyCanCloseDocument())
    {
        m_document->createNew();
    }
}

void MainWindow::on_saveDocument_triggered()
{
    m_document->save();
}

void MainWindow::on_openDocument_triggered()
{
    if (verifyCanCloseDocument())
    {
        m_document->open();
    }
}

void MainWindow::on_saveDocumentAs_triggered()
{
    m_document->saveAs();
}

void MainWindow::on_showTable_triggered()
{
}

void MainWindow::on_showDiagram_triggered()
{
}

void MainWindow::on_actionAbout_triggered()
{
    std::unique_ptr<AboutDialog> dialog(new AboutDialog(this));
    dialog->exec();
}

void MainWindow::on_actionInsertRow_triggered()
{
    std::unique_ptr<InsertRowDialog> dialog(new InsertRowDialog(this));
    connect(dialog.get(), SIGNAL(rowReady(QString, int)), this, SLOT(onRowReady(QString, int)));
    dialog->exec();
}

void MainWindow::on_actionUndo_triggered()
{
    m_tableModel->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    m_tableModel->redo();
}

void MainWindow::onRowReady(QString text, int value)
{
    m_tableModel->insertRow(text, value);
}

void MainWindow::on_actionDeleteRow_triggered()
{
    std::set<int> deletedRows = m_ui->tableData->selectedRows();
    if (deletedRows.size() == 0)
    {
        return;
    }

    m_tableModel->deleteRows(deletedRows);
}

void MainWindow::initTableData()
{
    m_tableModel = std::make_shared<StatsTableModel>();
    m_ui->tableData->setModel(m_tableModel.get());
    m_ui->tableData->setAlternatingRowColors(true);

    connect(m_tableModel.get(), &StatsTableModel::availableForUndo, [=](){
        m_ui->actionUndo->setEnabled(true);
    });
    connect(m_tableModel.get(), &StatsTableModel::unavailableForUndo, [=](){
        m_ui->actionUndo->setDisabled(true);
    });
    connect(m_tableModel.get(), &StatsTableModel::availableForRedo, [=](){
        m_ui->actionRedo->setEnabled(true);
    });
    connect(m_tableModel.get(), &StatsTableModel::unavailableForRedo, [=](){
        m_ui->actionRedo->setDisabled(true);
    });
}

void MainWindow::initDocument()
{
    m_ui->newDocument->setShortcut(QKeySequence(QKeySequence::New));
    m_ui->openDocument->setShortcut(QKeySequence(QKeySequence::Open));
    m_ui->saveDocument->setShortcut(QKeySequence(QKeySequence::Save));
    m_ui->saveDocumentAs->setShortcut(QKeySequence(QKeySequence::SaveAs));

    m_document.reset(new StatsDocument(this, *m_tableModel));
}

bool MainWindow::verifyCanCloseDocument()
{
    auto canClose = true;

    if (!m_tableModel->isSaved())
    {
        switch (processSaveChangesDialog())
        {
        case QMessageBox::Yes:
            on_saveDocument_triggered();
        case QMessageBox::No:
            break;
        default:
            canClose = false;
        }
    }
    return canClose;
}

QMessageBox::StandardButton MainWindow::processSaveChangesDialog()
{
    return QMessageBox::question(
                this,
                HAS_CHANGES_MSG,
                SAVE_QUESTION_MSG,
                QMessageBox::Yes |
                QMessageBox::No  |
                QMessageBox::Cancel);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QRect tableArea = QRect(QPoint(0, 0), event->size());
    m_ui->tableData->setGeometry(tableArea);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (verifyCanCloseDocument())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
