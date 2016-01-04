#include "jsonsceneloader.h"
#include "../utils/scenenodefactory.h"
#include "../config/jsonkey.h"
#include "../utils/mycast.h"
#include <QFile>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonDocument>


JsonSceneLoader::JsonSceneLoader(QString const& jsonFileName)
    : m_jsonFileName(jsonFileName)
{
    parseJsonDocument();
}

bool JsonSceneLoader::loadScene(SceneNode * root) const
{
    auto objects = m_rootObject[JsonKey::OBJECTS].toArray();
    if (objects.isEmpty())
    {
        return false;
    }

    return parseSceneObjects(root, objects);
}

bool JsonSceneLoader::loadCamera(Camera & camera) const
{
    auto cameraJson = m_rootObject[JsonKey::CAMERA].toObject();
    auto eyeJson = cameraJson[JsonKey::EYE].toArray();
    auto atJson  = cameraJson[JsonKey::AT].toArray();
    auto upJson  = cameraJson[JsonKey::UP].toArray();

    if (!(MyCast::isVector3DJson(eyeJson) && MyCast::isVector3DJson(atJson) && MyCast::isVector3DJson(upJson)))
    {
        return false;
    }

    camera.setEye(MyCast::jsonArrayToVector3D(eyeJson));
    camera.setAt(MyCast::jsonArrayToVector3D(atJson));
    camera.setUp(MyCast::jsonArrayToVector3D(upJson));
    return true;
}

bool JsonSceneLoader::parseSceneObjects(SceneNode * root, QJsonArray const& objects) const
{
    bool success = true;

    for (auto const& object : objects)
    {
        if (!SceneNodeFactory::createSceneObject(root, object.toObject()))
        {
            success = false;
            break;
        }
    }

    return success;
}

void JsonSceneLoader::parseJsonDocument()
{
    QFile input(m_jsonFileName);
    input.open(QIODevice::ReadOnly | QIODevice::Text);

    m_rootObject = QJsonDocument::fromJson(input.readAll()).object();
}

