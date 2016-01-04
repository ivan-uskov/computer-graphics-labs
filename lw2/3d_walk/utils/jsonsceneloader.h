#pragma once
#include <QString>
#include <QJsonObject>
#include "../gl/scenenode.h"
#include "../gl/camera.h"

class JsonSceneLoader
{
public:
    JsonSceneLoader(QString const& jsonFileName);

    bool loadScene(SceneNode * root) const;
    bool loadCamera(Camera & camera) const;

private:
    bool parseSceneObjects(SceneNode * root, QJsonArray const& objects) const;
    void parseJsonDocument();

    QString m_jsonFileName;
    QJsonObject m_rootObject;
};
