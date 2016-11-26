#pragma once

#include <QUndoCommand>
#include "statstablemodel.h"

class StatsTableModel;

class SortStatsModelCommand : public QUndoCommand
{
public:
    SortStatsModelCommand(StatsTableModel * tableModel, StatsKeyValueModel::Column column, Qt::SortOrder order);

    // QUndoCommand interface
public:
    void undo() override;
    void redo() override;

private:
    StatsTableModel * m_tableModel;
    StatsKeyValueModel m_oldModel;
    StatsKeyValueModel::Column m_sortColumn;
    Qt::SortOrder m_sortOrder;
};
