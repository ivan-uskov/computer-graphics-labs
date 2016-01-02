#pragma once
#include <QString>
#include <QJsonDocument>
#include "../gl/scenenode.h"

class JsonSceneLoader
{
public:
    JsonSceneLoader(QString const& jsonFileName);

    bool loadScene(SceneNode * root)const;

private:
    bool parseSceneObjects(SceneNode * root, QJsonArray const& objects)const;
    QJsonDocument parseJsonDocument()const;

    QString m_jsonFileName;
};
