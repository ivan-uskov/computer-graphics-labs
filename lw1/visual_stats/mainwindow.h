#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <memory>

namespace Ui
{
    class MainWindow;
}
class StatsTableModel;
class StatsDocument;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newDocument_triggered();
    void on_saveDocument_triggered();
    void on_openDocument_triggered();
    void on_saveDocumentAs_triggered();
    void on_showTable_triggered();
    void on_showDiagram_triggered();
    void on_actionAbout_triggered();
    void on_actionInsertRow_triggered();
    void on_actionDeleteRow_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

    void onRowReady(QString text, int value);

private:
    void initTableData();
    void initDocument();
    bool verifyCanCloseDocument();
    QMessageBox::StandardButton processSaveChangesDialog();

    Ui::MainWindow * m_ui;
    std::shared_ptr<StatsTableModel> m_tableModel;
    std::unique_ptr<StatsDocument> m_document;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent * event);
};
