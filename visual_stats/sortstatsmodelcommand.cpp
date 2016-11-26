#include "sortstatsmodelcommand.h"

SortStatsModelCommand::SortStatsModelCommand(StatsTableModel * tableModel, StatsKeyValueModel::Column column, Qt::SortOrder order)
    : m_tableModel(tableModel)
    , m_sortColumn(column)
    , m_sortOrder(order)
{
}

void SortStatsModelCommand::undo()
{
    m_tableModel->setStatsModel(m_oldModel);
}

void SortStatsModelCommand::redo()
{
    m_oldModel = m_tableModel->statsModel();
    m_tableModel->m_statsModel.sort(m_sortColumn, m_sortOrder);
}
