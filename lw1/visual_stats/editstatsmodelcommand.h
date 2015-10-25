#pragma once

#include "statstablemodel.h"
#include <QUndoCommand>
#include <QModelIndex>
#include <QVariant>

class EditStatsModelCommand : public QUndoCommand
{
public:
    EditStatsModelCommand(StatsTableModel * tableModel, QModelIndex const& index, QVariant const& value);

    // QUndoCommand interface
public:
    void undo() override;
    void redo() override;

private:
    void setValue(QVariant const& value);

    StatsTableModel * m_tableModel;
    QModelIndex m_index;
    QVariant m_newValue;
    QVariant m_oldValue;
};
