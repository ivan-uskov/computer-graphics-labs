#include "editstatsmodelcommand.h"
#include "statstablemodel.h"

EditStatsModelCommand::EditStatsModelCommand(StatsTableModel * tableModel, QModelIndex const& index, QVariant const& value)
    : m_tableModel(tableModel)
    , m_index(index)
    , m_newValue(value)
    , m_oldValue(tableModel->data(index, Qt::DisplayRole))
{
}

void EditStatsModelCommand::undo()
{
    setValue(m_oldValue);
}

void EditStatsModelCommand::redo()
{
    setValue(m_newValue);
}

void EditStatsModelCommand::setValue(QVariant const& value)
{
    if (m_index.column() == static_cast<int>(StatsKeyValueModel::Column::Name))
    {
        m_tableModel->m_statsModel.setKey(m_index.row(), value.toString());
    }
    else if (m_index.column() == static_cast<int>(StatsKeyValueModel::Column::Value))
    {
        m_tableModel->m_statsModel.setValue(m_index.row(), value.toInt());
    }
}
