#include "statsdocument.h"
#include "statskeyvaluemodel.h"
#include "istatsmodelprovider.h"
#include "statsserializer.h"
#include <QWidget>
#include <QFileDialog>
#include <QStandardPaths>
#include <QErrorMessage>

namespace
{
    static const QLatin1String FILE_EXTENSION(".json");
    static const QLatin1String FILE_FORMAT_FILTER("*.json");
    static const QLatin1String SAVE_ACTION_ERROR_MSG("Failed to save file");
}

StatsDocument::StatsDocument(QWidget *parent, IStatsModelProvider &provider)
    : QObject(parent)
    , m_provider(provider)
    , m_isNew(true)
{
}

void StatsDocument::createNew()
{
    StatsKeyValueModel model;
    m_provider.setStatsModel(model);
    m_isNew = true;
}

bool StatsDocument::open()
{
    m_documentPath = selectOpenPath();
    if (m_documentPath.isEmpty())
    {
        return false;
    }

    StatsKeyValueModel model;
    StatsSerializer serializer(m_documentPath);
    if (!serializer.load(model))
    {
        return false;
    }

    m_provider.setStatsModel(model);
    m_provider.setIsSaved();
    m_isNew = false;
    return !m_isNew;
}

bool StatsDocument::save()
{
    if (m_isNew)
    {
        return saveAs();
    }
    else if (!m_documentPath.isEmpty())
    {
        return saveDocument(m_documentPath);
    }

    return false;
}

bool StatsDocument::saveAs()
{
    m_documentPath = selectSavePath();
    return !m_documentPath.isEmpty() && saveDocument(m_documentPath + FILE_EXTENSION);
}

bool StatsDocument::saveDocument(const QString &filePath)
{
    StatsSerializer serializer(filePath);
    auto success = serializer.save(m_provider.statsModel());
    if (success)
    {
        m_provider.setIsSaved();
        m_isNew = false;
    }
    else
    {
        QErrorMessage errorBox;
        errorBox.showMessage(SAVE_ACTION_ERROR_MSG);
        errorBox.exec();
    }

    return success;
}

QString StatsDocument::selectSavePath() const
{
    QString fromDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    auto parentWindow = qobject_cast<QWidget *>(parent());
    return QFileDialog::getSaveFileName(parentWindow, QString(), fromDir, FILE_FORMAT_FILTER);
}

QString StatsDocument::selectOpenPath() const
{
    QString fromDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    auto parentWindow = qobject_cast<QWidget *>(parent());
    return QFileDialog::getOpenFileName(parentWindow, QString(), fromDir, FILE_FORMAT_FILTER);
}
