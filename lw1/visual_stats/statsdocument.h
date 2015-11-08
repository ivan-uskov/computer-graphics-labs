#pragma once

#include <QObject>
#include <memory>
#include "istatsmodelprovider.h"

class QWidget;
class IStatsModelProvider;

class StatsDocument : public QObject
{
    Q_OBJECT
public:
    explicit StatsDocument(QWidget *parent, IStatsModelProvider &provider);

    void createNew();
    bool open();
    bool save();
    bool saveAs();

private:
    bool saveDocument(QString const& filePath);

    QString selectSavePath() const;
    QString selectOpenPath() const;

    bool m_isNew;
    QString m_documentPath;
    IStatsModelProvider & m_provider;
};
