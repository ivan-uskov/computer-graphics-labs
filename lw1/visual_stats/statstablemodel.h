#pragma once

#include "statskeyvaluemodel.h"
#include "istatsmodelprovider.h"
#include <QAbstractTableModel>
#include <vector>
#include <QUndoStack>
#include <memory>
#include <set>

class StatsDocument;
class QWidget;

class StatsTableModel : public QAbstractTableModel, public IStatsModelProvider
{
    Q_OBJECT
public:
    explicit StatsTableModel(QObject *parent = 0);

    StatsKeyValueModel const& statsModel() const override;
    void setStatsModel(StatsKeyValueModel const& statsModel) override;
    bool isSaved() const override;
    void setIsSaved() override;
    void deleteRows(std::set<int> const& rowsToDelete);
    void insertRow(QString const& name, int value);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    void sort(int column, Qt::SortOrder order);

private:
    bool m_isSaved = false;
    StatsKeyValueModel m_statsModel;
    std::unique_ptr<QUndoStack> m_undoStack;
};
