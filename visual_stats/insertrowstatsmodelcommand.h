#pragma once

#include "statstablemodel.h"
#include <QUndoCommand>
#include <QUndoCommand>
#include <QModelIndex>

class InsertRowStatsModelCommand : public QUndoCommand
{
public:
    InsertRowStatsModelCommand(StatsTableModel * tableModel, QString const& name, int value);

    // QUndoCommand interface
public:
    void undo() override;
    void redo() override;

    StatsTableModel * m_tableModel;
    size_t m_position = 0;
    QModelIndex m_index;
    QString m_name;
    int m_value;
};
