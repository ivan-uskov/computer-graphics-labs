#include "editstatsmodelcommand.h"
#include "insertrowstatsmodelcommand.h"
#include "deleterowsstatsmodelcommand.h"
#include "sortstatsmodelcommand.h"
#include "statstablemodel.h"
#include "statsdocument.h"
#include <algorithm>
#include <QErrorMessage>

namespace
{
    static const char COLUMN_TITLE_NAME[] = "Country Name";
    static const char COLUMN_TITLE_VALUE[] = "Population (in millions)";
}

StatsTableModel::StatsTableModel(QObject * parent)
    : QAbstractTableModel(parent)
{
    m_statsModel.setSampleValues();
    m_isSaved = false;
}

const StatsKeyValueModel &StatsTableModel::statsModel() const
{
    return m_statsModel;
}

void StatsTableModel::setStatsModel(StatsKeyValueModel const& statsModel)
{
    emit layoutAboutToBeChanged();
    m_statsModel = statsModel;
    m_isSaved = false;
    emit layoutChanged();
}

bool StatsTableModel::isSaved() const
{
    return m_isSaved;
}

void StatsTableModel::setIsSaved()
{
    m_isSaved = true;
}

int StatsTableModel::rowCount(QModelIndex const& parent) const
{
    (void)parent;
    return (int)m_statsModel.size();
}

int StatsTableModel::columnCount(QModelIndex const& parent) const
{
    (void)parent;
    return StatsKeyValueModel::COLUMNS_COUNT;
}

QVariant StatsTableModel::data(QModelIndex const& index, int role) const
{
    if (static_cast<size_t>(index.row()) > m_statsModel.size())
    {
        return QVariant();
    }

    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        switch (index.column())
        {
        case StatsKeyValueModel::Column::Name:
            return m_statsModel.key(index.row());
        case StatsKeyValueModel::Column::Value:
            return m_statsModel.value(index.row());
        }
    }

    return QVariant();
}

QVariant StatsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case StatsKeyValueModel::Column::Name:
            return QLatin1String(COLUMN_TITLE_NAME);
        case StatsKeyValueModel::Column::Value:
            return QLatin1String(COLUMN_TITLE_VALUE);
        default:
            break;
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags StatsTableModel::flags(QModelIndex const& index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool StatsTableModel::setData(QModelIndex const& index, QVariant const& value, int role)
{
    auto isIndexValid = static_cast<size_t>(index.row()) < m_statsModel.size();

    if (role == Qt::EditRole && isIndexValid)
    {
        m_isSaved = false;

        emit layoutAboutToBeChanged();

        auto editCommand = std::make_shared<EditStatsModelCommand>(this, index, value);
        editCommand->redo();
        m_undoStack.push_back(editCommand);
        clearRedoStack();

        emit layoutChanged();

        return true;
    }
    return QAbstractTableModel::setData(index, value, role);
}

void StatsTableModel::deleteRows(std::set<int> const& rowsToDelete)
{
    auto editCommand = std::make_shared<DeleteRowsStatsModelCommand>(this, rowsToDelete);
    editCommand->redo();
    m_undoStack.push_back(editCommand);
    clearRedoStack();
}

void StatsTableModel::insertRow(QString const& name, int value)
{
    emit layoutAboutToBeChanged();

    auto insertCommand = std::make_shared<InsertRowStatsModelCommand>(this, name, value);
    insertCommand->redo();
    m_undoStack.push_back(insertCommand);
    clearRedoStack();

    emit layoutChanged();
}

void StatsTableModel::undo()
{
    if (m_undoStack.empty())
    {
        return;
    }

    emit layoutAboutToBeChanged();

    auto lastCommand = m_undoStack.back();
    lastCommand->undo();
    m_redoStack.push_back(lastCommand);
    m_undoStack.pop_back();

    emit layoutChanged();

    if (m_undoStack.empty())
    {
        emit unavailableForUndo();
    }
    else
    {
        emit availableForUndo();
    }

    emit availableForRedo();
}

void StatsTableModel::redo()
{
    if (m_redoStack.empty())
    {
        return;
    }

    emit layoutAboutToBeChanged();

    auto lastCommand = m_redoStack.back();
    lastCommand->redo();
    m_undoStack.push_back(lastCommand);
    m_redoStack.pop_back();

    emit layoutChanged();

    if (m_redoStack.empty())
    {
        emit unavailableForRedo();
    }
    else
    {
        emit availableForRedo();
    }

    emit availableForUndo();
}

void StatsTableModel::sort(int column, Qt::SortOrder order)
{
    emit layoutAboutToBeChanged();

    auto sortCommand = std::make_shared<SortStatsModelCommand>(this, static_cast<StatsKeyValueModel::Column>(column), order);
    sortCommand->redo();
    m_undoStack.push_back(sortCommand);
    clearRedoStack();

    emit layoutChanged();
}

void StatsTableModel::clearRedoStack()
{
    m_redoStack.clear();
    emit unavailableForRedo();
}
