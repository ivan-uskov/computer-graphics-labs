#pragma once

#include "statstablemodel.h"
#include <QUndoCommand>
#include <vector>

class DeleteRowsStatsModelCommand : public QUndoCommand
{
public:
    DeleteRowsStatsModelCommand(StatsTableModel * tableModel, std::set<int> const& rowsToDelete);

    // QUndoCommand interface
public:
    void undo() override;
    void redo() override;

private:
    typedef std::pair<size_t, StatsKeyValueModel::Item> DeletedItem;

    StatsTableModel * m_tableModel;
    std::set<int> m_rowsToDelete;
    std::vector<DeletedItem> m_deletedItems;
};
