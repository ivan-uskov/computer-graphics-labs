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
    , isNew(true)
{
}

void StatsDocument::createNew()
{
    StatsKeyValueModel model;
    m_provider.setStatsModel(model);
    isNew = true;
}

bool StatsDocument::open()
{
    documentPath = selectOpenPath();
    if (documentPath.isEmpty())
    {
        return false;
    }

    StatsKeyValueModel model;
    StatsSerializer serializer(documentPath);
    if (!serializer.load(model))
    {
        return false;
    }

    m_provider.setStatsModel(model);
    m_provider.setIsSaved();
    isNew = false;
    return !isNew;
}

bool StatsDocument::save()
{
    if (isNew)
    {
        return saveAs();
    }
    else if (!documentPath.isEmpty())
    {
        return saveDocument(documentPath);
    }
}

bool StatsDocument::saveAs()
{
    documentPath = selectSavePath();
    return !documentPath.isEmpty() && saveDocument(documentPath + FILE_EXTENSION);
}

bool StatsDocument::saveDocument(const QString &filePath)
{
    StatsSerializer serializer(filePath);
    auto success = serializer.save(m_provider.statsModel());
    if (success)
    {
        isNew = false;
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
