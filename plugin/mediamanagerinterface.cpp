// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// 
// Copyright (c) 2016 Jaguar Land Rover.
//
// This program is licensed under the terms and conditions of the
// Mozilla Public License, version 2.0. The full text of the 
// Mozilla Public License is at https://www.mozilla.org/MPL/2.0/
// 
// File:    mediamanagerinterface.cpp
// Project: Media Manager QML Plugin
// 
// Created by Jason Anderson
//
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#include "mediamanagerinterface.h"
#include <unistd.h>

using namespace v1_0::org::genivi::mediamanager;

/*static QObject* QueueListManagerCallback(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return &QueueListManager::instance();
}*/

Q_INVOKABLE const bool MediaManagerInterface::isPlaying()
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlaybackStatus status;
    std::cout << "Called getCurrentPlayQueue" << std::endl;

    CommonAPI::CallStatus callStatus;

    playerProxy->getPlaybackStatusAttribute().getValue(callStatus, status);

    return (status == ::v1_0::org::genivi::mediamanager::PlayerTypes::PlaybackStatus::PLAYING) ? true : false;
}

MediaManagerInterface::MediaManagerInterface(QQuickItem *parent):
    QQuickItem(parent)
{
    this->runtime = CommonAPI::Runtime::get();

    // Connect to the Media Manager Browser.
    this->browserProxy = this->runtime->buildProxy<BrowserProxy>("local", "");
    if (!this->browserProxy)
    {
        std::cout << "Could not build browser proxy!" << std::endl;
        return;
    }

    std::cout << "Checking availability of the Media Manager Browser." << std::endl;
    if (this->browserProxy->isAvailable())
        std::cout << "Browser is available!" << std::endl;
    else
        std::cout << "Browser is not available." << std::endl;

    // Connect to the Media Manager Indexer.
    this->indexerProxy = this->runtime->buildProxy<IndexerProxy>("local", "");
    if (!this->indexerProxy)
    {
        std::cout << "Could not build indexer proxy!" << std::endl;
        return;
    }

    std::cout << "Checking availability of the Media Manager Indexer." << std::endl;
    if (this->indexerProxy->isAvailable())
        std::cout << "Indexer is available!" << std::endl;
    else
        std::cout << "Indexer is not available." << std::endl;

    // Connect to the Media Manager Player.
    this->playerProxy = this->runtime->buildProxy<PlayerProxy>("local", "");
    if (!this->playerProxy)
    {
        std::cout << "Could not build player proxy!" << std::endl;
        return;
    }

    std::cout << "Checking availability of the Media Manager Player." << std::endl;
    if (this->playerProxy->isAvailable())
        std::cout << "Player is available!" << std::endl;
    else
        std::cout << "Player is not available." << std::endl;

    //qmlRegisterSingletonType<QueueListManager>("Automotive.MediaManagerInterface", 1, 0, "QueueListManager", QueueListManagerCallback);

    playerProxy->getCurrentTrackAttribute().getChangedEvent().subscribe([this](const uint64_t& trackIdx) {
              std::cout << "Current track changed: " << trackIdx << std::endl;
              this->sendPlayerAttribChanged(quint64(trackIdx));
              });

}

void MediaManagerInterface::sendPlayerAttribChanged(quint64 idx)
{
    emit playerAttributeChanged(idx);
}

Q_INVOKABLE QList<QString> MediaManagerInterface::discoverMediaManagers()
{
    CommonAPI::CallStatus status;
    ::v1_0::org::genivi::mediamanager::BrowserTypes::BrowserError e;
    std::vector<std::string> ret;
    QList<QString> out;

    this->browserProxy->discoverMediaManagers(status, ret, e);

    for( unsigned int i = 0; i < ret.size(); ++i)
    {
        out.push_back( QString::fromStdString ( ret[i] ) );
    }

    return out;
}

QVariantList MediaManagerInterface::resultMapListToQMapList(::v1_0::org::genivi::mediamanager::MediaTypes::ResultMapList& rml)
{
    QVariantList ret;

     std::cout << "Called resultMapListToQMapList" << std::endl;

    std::vector<::v1_0::org::genivi::mediamanager::MediaTypes::ResultMap>::iterator resMapIter = rml.begin();

    // Loop through result map list,
    for(; resMapIter != rml.end(); ++resMapIter)
    {
        std::cout << "Result map " << std::endl;
        std::unordered_map<std::string, ::v1_0::org::genivi::mediamanager::MediaTypes::ResultUnion>::iterator mapEntry = (*resMapIter).begin();

        QVariantMap hmap;

        // Iterate over result map
        for(; mapEntry != (*resMapIter).end(); ++mapEntry)
        {
            std::cout << "mapEntry" << std::endl;

            QVariant var;

            switch( mapEntry->second.getValueType() )
            {
                case 1: // std::string
                {
                std::cout << "Found std::string" << std::endl;
                    std::string data = mapEntry->second.get<std::string>();
                    var = QString::fromStdString(data);
                     std::cout << "after" << std::endl;
                }
                break;

                case 2: // double
                {
                std::cout << "Found double" << std::endl;
                    var = mapEntry->second.get<double>();
                     std::cout << "after" << std::endl;
                }
                break;

                case 3: // float
                {
                std::cout << "Found float" << std::endl;
                    var = mapEntry->second.get<float>();
                     std::cout << "after" << std::endl;
                }
                break;

                case 4: // bool
                {
                std::cout << "Found bool" << std::endl;
                   var = mapEntry->second.get<bool>();
                    std::cout << "after" << std::endl;
                }
                break;

                case 5: // uint64_t
                {
                std::cout << "Found uint64_t" << std::endl;
                    var = quint64(mapEntry->second.get<uint64_t>());
                     std::cout << "after" << std::endl;
                }
                break;

                case 6: // int64_t
                {
                std::cout << "Found int64_t" << std::endl;
                    var = qint64(mapEntry->second.get<int64_t>());
                     std::cout << "after" << std::endl;
                }
                break;

                case 7: // uint32_t
                {
                    std::cout << "Found uint32_t" << std::endl;
                    var = mapEntry->second.get<uint32_t>();
                     std::cout << "after" << std::endl;
                }
                break;

                case 8: // int32_t
                {
                    std::cout << "Found int32_t" << std::endl;
                    var = mapEntry->second.get<int32_t>();
                    std::cout << "after" << std::endl;

                }
                break;

                case 9: // StringList
                {
                    std::cout << "Found string list" << std::endl;
                    std::vector<std::string> data = mapEntry->second.get<std::vector<std::string>>();
                    std::cout << "Assigned to data" << std::endl;
                    QStringList tempList;
                    for( unsigned int i = 0; i < data.size(); ++i)
                    {
                        std::cout << "push item" << std::endl;
                        tempList.push_back( QString::fromStdString ( data[i] ) );
                        std::cout << "after push item" << std::endl;
                    }

                    std::cout << "after" << std::endl;

                    var = tempList;
                }
                break;

                default: //Unkown Type
                    //NOTHING!
                break;
            }

            std::cout << "hmap insert" << std::endl;

            hmap.insert(QString::fromStdString(mapEntry->first), var);
             std::cout << "after" << std::endl;

        }

        ret.push_back(hmap);
    }

    return ret;
}

Q_INVOKABLE QVariantList MediaManagerInterface::listContainers( QString path, quint64 offset, quint64 count, QList<QString> filter )
{
    ::v1_0::org::genivi::mediamanager::BrowserTypes::BrowserError e;
    CommonAPI::CallStatus status;

    std::vector<std::string> fltr;

    for(int i = 0; i < filter.size(); ++i)
    {
        fltr.push_back(filter[i].toStdString());
    }
    const std::string constPath = path.toStdString();

    ::v1_0::org::genivi::mediamanager::MediaTypes::ResultMapList rml;

    this->browserProxy->listContainers(path.toStdString(), offset, count, fltr, status, rml, e);

    return resultMapListToQMapList(rml);
}

Q_INVOKABLE QVariantList MediaManagerInterface::listChildren(QString path, quint64 offset, quint64 count, QList<QString> filter)
{
    ::v1_0::org::genivi::mediamanager::BrowserTypes::BrowserError e;
    CommonAPI::CallStatus status;

    std::vector<std::string> fltr;

    for(int i = 0; i < filter.size(); ++i)
    {
        fltr.push_back(filter[i].toStdString());
    }

    ::v1_0::org::genivi::mediamanager::MediaTypes::ResultMapList rml;

    this->browserProxy->listChildren(path.toStdString(), offset, count, fltr, status, rml, e);

    return resultMapListToQMapList(rml);
}


Q_INVOKABLE QVariantList MediaManagerInterface::listItems(QString path, quint64 offset, quint64 count, QList<QString> filter)
{
    ::v1_0::org::genivi::mediamanager::BrowserTypes::BrowserError e;
    CommonAPI::CallStatus status;

    std::vector<std::string> fltr;

    for(int i = 0; i < filter.size(); ++i)
    {
        fltr.push_back(filter[i].toStdString());
    }

    ::v1_0::org::genivi::mediamanager::MediaTypes::ResultMapList rml;

    this->browserProxy->listItems(path.toStdString(), offset, count, fltr, status, rml, e);

    return resultMapListToQMapList(rml);
}


MediaManagerInterface::~MediaManagerInterface()
{
}

Q_INVOKABLE void MediaManagerInterface::next()
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;

    playerProxy->next(status, e);
}

Q_INVOKABLE void MediaManagerInterface::openUri(QString _uri)
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;

    playerProxy->openUri(_uri.toStdString(), status, e);
}

Q_INVOKABLE void MediaManagerInterface::enqueueUri(QString _uri)
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;
    playerProxy->enqueueUri(_uri.toStdString(), status, e);
}

Q_INVOKABLE void MediaManagerInterface::dequeueIndex(qint64 _pos)
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;
    playerProxy->dequeueIndex(_pos, status, e);
}

// MAP
Q_INVOKABLE QVariantList MediaManagerInterface::getCurrentPlayQueue()
{
    QList<QHash<QString, QVariant>> ret;

    ::v1_0::org::genivi::mediamanager::MediaTypes::ResultMapList rml;
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;

    std::cout << "Called getCurrentPlayQueue" << std::endl;

    playerProxy->getCurrentPlayQueue(status, rml, e);

    std::cout << "Returned from proxy getCurrentPlayQueue" << std::endl;

    return resultMapListToQMapList(rml);
}

Q_INVOKABLE void MediaManagerInterface::dequeueAll()
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;
    playerProxy->dequeueAll(status, e);
}

Q_INVOKABLE void MediaManagerInterface::openPlaylist(QString _uri)
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;
    playerProxy->openPlaylist(_uri.toStdString(), status, e);
}

Q_INVOKABLE void MediaManagerInterface::pause()
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;
    playerProxy->pause(status, e);
}

Q_INVOKABLE void MediaManagerInterface::play()
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;
    playerProxy->play(status, e);
}

Q_INVOKABLE void MediaManagerInterface::playPause()
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;
    playerProxy->playPause(status, e);
}

Q_INVOKABLE void MediaManagerInterface::previous()
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;
    playerProxy->previous(status, e);
}

Q_INVOKABLE void MediaManagerInterface::seek(qint64 _pos)
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;
    playerProxy->seek(_pos, status, e);
}

Q_INVOKABLE void MediaManagerInterface::setPosition(qint64 _pos)
{
    ::v1_0::org::genivi::mediamanager::PlayerTypes::PlayerError e;
    CommonAPI::CallStatus status;
    playerProxy->setPosition(_pos, status, e);
}

Q_INVOKABLE const quint64 MediaManagerInterface::getPositionAttribute()
{
    CommonAPI::CallStatus status;
    uint64_t ret;
    playerProxy->getPositionAttribute().getValue(status, ret);
    return quint64(ret);
}

Q_INVOKABLE const quint64 MediaManagerInterface::getDurationAttribute()
{
    CommonAPI::CallStatus status;
    uint64_t ret;
    playerProxy->getDurationAttribute().getValue(status, ret);
    return quint64(ret);
}
