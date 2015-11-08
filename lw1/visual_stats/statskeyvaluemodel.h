#pragma once

#include "basekeyvaluemodel.h"

class StatsKeyValueModel : public BaseKeyValueModel<QString, int>
{
public:
    enum class Column
    {
        Name = 0,
        Value = 1
    };

    static const int COLUMNS_COUNT = 2;

    StatsKeyValueModel();

    void setSampleValues();
    void sort(Column column, Qt::SortOrder order);

    size_t commonValue();
};
