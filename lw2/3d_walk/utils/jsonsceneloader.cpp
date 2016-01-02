#include "jsonsceneloader.h"
#include "../utils/scenenodefactory.h"
#include "../config/jsonkey.h"
#include <QFile>
#include <QIODevice>
#include <QJsonArray>
#include <QDebug>


JsonSceneLoader::JsonSceneLoader(QString const& jsonFileName)
    : m_jsonFileName(jsonFileName)
{
}

bool JsonSceneLoader::loadScene(SceneNode * root) const
{
    auto rootObject = parseJsonDocument().object();

    if (rootObject.isEmpty())
    {

        return false;
    }

    auto objects = rootObject[JsonKey::OBJECTS].toArray();
    if (objects.isEmpty())
    {
        return false;
    }

    return parseSceneObjects(root, objects);
}

bool JsonSceneLoader::parseSceneObjects(SceneNode * root, QJsonArray const& objects) const
{
    bool success = true;

    for (auto const object : objects)
    {
        if (!SceneNodeFactory::createSceneObject(root, object.toObject()))
        {
            success = false;
            break;
        }
    }

    return success;
}

QJsonDocument JsonSceneLoader::parseJsonDocument() const
{
    QFile input(m_jsonFileName);
    input.open(QIODevice::ReadOnly | QIODevice::Text);

    return QJsonDocument::fromJson(input.readAll());
}

