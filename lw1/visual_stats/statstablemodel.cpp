#include "statstablemodel.h"
#include "statsdocument.h"
#include <QSortFilterProxyModel>
#include <algorithm>
#include <QErrorMessage>

namespace
{
    static const char COLUMN_TITLE_NAME[] = "Country Name";
    static const char COLUMN_TITLE_VALUE[] = "Population (in millions)";
}

StatsTableModel::StatsTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_statsModel.setSampleValues();
    m_isSaved = false;
}

const StatsKeyValueModel &StatsTableModel::statsModel() const
{
    return m_statsModel;
}

void StatsTableModel::setStatsModel(const StatsKeyValueModel &statsModel)
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

int StatsTableModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return (int)m_statsModel.size();
}

int StatsTableModel::columnCount(const QModelIndex &parent) const
{
    (void)parent;
    return StatsKeyValueModel::COLUMNS_COUNT;
}

QVariant StatsTableModel::data(const QModelIndex &index, int role) const
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

Qt::ItemFlags StatsTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}


bool StatsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole && static_cast<size_t>(index.row()) < m_statsModel.size())
    {
        m_isSaved = false;
        switch (index.column())
        {
        case StatsKeyValueModel::Column::Name:
            m_statsModel.setKey(index.row(), value.toString());
            return true;
        case StatsKeyValueModel::Column::Value:
            m_statsModel.setValue(index.row(), value.toInt());
            return true;
        default:
            break;
        }
    }
    return QAbstractTableModel::setData(index, value, role);
}

void StatsTableModel::sort(int column, Qt::SortOrder order)
{
    emit layoutAboutToBeChanged();

    m_statsModel.sort(static_cast<StatsKeyValueModel::Column>(column), order);

    emit layoutChanged();
}
