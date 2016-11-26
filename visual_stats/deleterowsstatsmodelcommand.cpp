#include "deleterowsstatsmodelcommand.h"
#include <algorithm>

DeleteRowsStatsModelCommand::DeleteRowsStatsModelCommand(StatsTableModel *tableModel, const std::set<int> &rowsToDelete)
    : m_tableModel(tableModel)
    , m_rowsToDelete(rowsToDelete)
{
}

void DeleteRowsStatsModelCommand::undo()
{
    std::for_each(m_deletedItems.rbegin(), m_deletedItems.rend(), [this](DeletedItem const& deletedItem){
        auto & statsModel = this->m_tableModel->m_statsModel;
        auto newElementIt = statsModel.getIterator(deletedItem.first);
        auto & newElement = deletedItem.second;

        if (newElementIt < statsModel.end())
        {
            statsModel.insert(newElementIt, newElement);
        }
        else
        {
            statsModel.append(newElement.first, newElement.second);
        }
    });
}

void DeleteRowsStatsModelCommand::redo()
{
    m_deletedItems.clear();
    StatsKeyValueModel newModel;
    for (size_t i = 0, n = m_tableModel->m_statsModel.size(); i < n; ++i)
    {
        if (m_rowsToDelete.count(static_cast<int>(i)))
        {
            m_deletedItems.push_back({i, m_tableModel->m_statsModel.getItem(i)});
            continue;
        }
        newModel.append(m_tableModel->m_statsModel.key(i), m_tableModel->m_statsModel.value(i));
    }
    m_tableModel->setStatsModel(newModel);
}

