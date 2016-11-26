#include "insertrowstatsmodelcommand.h"

InsertRowStatsModelCommand::InsertRowStatsModelCommand(StatsTableModel *tableModel, const QString &name, int value)
    : m_tableModel(tableModel)
    , m_name(name)
    , m_value(value)
{
}

void InsertRowStatsModelCommand::undo()
{
    m_tableModel->m_statsModel.erase(m_position);
}

void InsertRowStatsModelCommand::redo()
{
    m_position = m_tableModel->m_statsModel.size();
    m_tableModel->m_statsModel.append(m_name, m_value);
}
