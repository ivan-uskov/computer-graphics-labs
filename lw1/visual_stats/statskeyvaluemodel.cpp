#include "statskeyvaluemodel.h"
#include <algorithm>
#include <functional>

namespace
{
    bool itemsLessByName(StatsKeyValueModel::Item const& lhs, StatsKeyValueModel::Item const& rhs)
    {
        return lhs.first.toLower() < rhs.first.toLower();
    }

    bool itemsLessByValue(StatsKeyValueModel::Item const& lhs, StatsKeyValueModel::Item const& rhs)
    {
        return lhs.second < rhs.second;
    }

    bool itemsMoreOrEqualByName(StatsKeyValueModel::Item const& lhs, StatsKeyValueModel::Item const& rhs)
    {
        return !itemsLessByName(lhs, rhs);
    }

    bool itemsMoreOrEqualByValue(StatsKeyValueModel::Item const& lhs, StatsKeyValueModel::Item const& rhs)
    {
        return !itemsLessByValue(lhs, rhs);
    }
}

StatsKeyValueModel::StatsKeyValueModel()
{
}

void StatsKeyValueModel::setSampleValues()
{
    m_items = {
        {"Russia", 146},
        {"USA", 310},
        {"China", 1350},
        {"India", 1160},
    };
}

void StatsKeyValueModel::sort(StatsKeyValueModel::Column column, Qt::SortOrder order)
{
    std::function<bool(StatsKeyValueModel::Item, StatsKeyValueModel::Item)> comparator;

    if (column == Column::Name)
    {
        if (order == Qt::AscendingOrder)
        {
            comparator = itemsLessByName;
        }
        else
        {
            comparator = itemsMoreOrEqualByName;
        }
    }
    else
    {
        if (order == Qt::AscendingOrder)
        {
            comparator = itemsLessByValue;
        }
        else
        {
            comparator = itemsMoreOrEqualByValue;
        }
    }

    std::sort(m_items.begin(), m_items.end(), comparator);
}

