// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// 
// Copyright (c) 2016 Jaguar Land Rover.
//
// This program is licensed under the terms and conditions of the
// Mozilla Public License, version 2.0. The full text of the 
// Mozilla Public License is at https://www.mozilla.org/MPL/2.0/
// 
// File:    mediamanagerinterface.h
// Project: Media Manager QML Plugin
// 
// Created by Jason Anderson
//
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#ifndef MEDIAMANAGERINTERFACE_H
#define MEDIAMANAGERINTERFACE_H

#include <QQuickItem>
#include <CommonAPI/CommonAPI.hpp>

#include <v1_0/org/genivi/mediamanager/BrowserProxy.hpp>
#include <v1_0/org/genivi/mediamanager/IndexerProxy.hpp>
#include <v1_0/org/genivi/mediamanager/PlayerProxy.hpp>


class MediaManagerInterface : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(MediaManagerInterface)


    QVariantList resultMapListToQMapList(::v1_0::org::genivi::mediamanager::MediaTypes::ResultMapList& rml);

    Q_PROPERTY(bool shuffle READ shuffle WRITE setShuffle)
    Q_PROPERTY(QString repeat  READ repeat WRITE setRepeat)


public:
    MediaManagerInterface(QQuickItem *parent = 0);
    ~MediaManagerInterface();

    bool shuffle() {
            CommonAPI::CallStatus callStatus;
            ::v1_0::org::genivi::mediamanager::PlayerTypes::ShuffleStatus response;

            playerProxy->getShuffleAttribute().getValue(callStatus, response);

            return (response == ::v1_0::org::genivi::mediamanager::PlayerTypes::ShuffleStatus::SHUFFLE);
    }

    void setShuffle(bool shuff) {
        CommonAPI::CallStatus callStatus;
        ::v1_0::org::genivi::mediamanager::PlayerTypes::ShuffleStatus response;

        playerProxy->getShuffleAttribute().setValue(
                 shuff ? ::v1_0::org::genivi::mediamanager::PlayerTypes::ShuffleStatus::SHUFFLE :
                     ::v1_0::org::genivi::mediamanager::PlayerTypes::ShuffleStatus::UNSHUFFLE ,
                 callStatus,
                 response);
    }

    QString repeat() {

            CommonAPI::CallStatus callStatus;
            ::v1_0::org::genivi::mediamanager::PlayerTypes::RepeatStatus response;

            playerProxy->getRepeatAttribute().getValue(callStatus, response);

            if (response == ::v1_0::org::genivi::mediamanager::PlayerTypes::RepeatStatus::REPEAT) {
                       return QString("REPEAT");
                } else if (response == ::v1_0::org::genivi::mediamanager::PlayerTypes::RepeatStatus::REPEAT_SINGLE) {
                    return QString("REPEAT_SINGLE");
                } else if (response == ::v1_0::org::genivi::mediamanager::PlayerTypes::RepeatStatus::NO_REPEAT) {
                   return QString("NO_REPEAT");
                } else {
                    return QString("Unknown repeat value, should be REPEAT, NO_REPEAT or REPEAT_SINGLE");
                }
    }

    void setRepeat(QString status) {
        CommonAPI::CallStatus callStatus;
        ::v1_0::org::genivi::mediamanager::PlayerTypes::RepeatStatus response;

         if (status == "REPEAT") {
             playerProxy->getRepeatAttribute().setValue(
                  ::v1_0::org::genivi::mediamanager::PlayerTypes::RepeatStatus::REPEAT,
                  callStatus,
                  response);
          } else if (status == "REPEAT_SINGLE") {
              playerProxy->getRepeatAttribute().setValue(
                  ::v1_0::org::genivi::mediamanager::PlayerTypes::RepeatStatus::REPEAT_SINGLE,
                  callStatus,
                  response);
          } else if (status == "NO_REPEAT") {
              playerProxy->getRepeatAttribute().setValue(
                  ::v1_0::org::genivi::mediamanager::PlayerTypes::RepeatStatus::NO_REPEAT,
                  callStatus,
                  response);
          }
    }


    // Browser Methods
    Q_INVOKABLE QList<QString> discoverMediaManagers();
    Q_INVOKABLE QVariantList listContainers(QString path, quint64 offset, quint64 count, QList<QString> filter);
    Q_INVOKABLE QVariantList listChildren(QString path, quint64 offset, quint64 count, QList<QString> filter);
    Q_INVOKABLE QVariantList listItems(QString path, quint64 offset, quint64 count, QList<QString> filter);

    // Indexer Methods

    // Player Methods

    Q_INVOKABLE void next();
    Q_INVOKABLE void openUri(QString _uri);
    Q_INVOKABLE void enqueueUri(QString _uri);
    Q_INVOKABLE void dequeueIndex(qint64 _pos);

    Q_INVOKABLE QVariantList getCurrentPlayQueue();

    Q_INVOKABLE void dequeueAll();
    Q_INVOKABLE void openPlaylist(QString _uri);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void play();
    Q_INVOKABLE void playPause();
    Q_INVOKABLE void previous();
    Q_INVOKABLE void seek(qint64 _pos);
    Q_INVOKABLE void setPosition(qint64 _pos);

    Q_INVOKABLE const quint64 getPositionAttribute();
    Q_INVOKABLE const quint64 getDurationAttribute();

    Q_INVOKABLE const bool getShuffleAttribute();
    //Q_INVOKABLE const

    Q_INVOKABLE const bool isPlaying();

    enum AttribType {
        CURRENT_TRACK,
        SHUFFLE,
        REPEAT,
        UNKNOWN
    };
    Q_ENUMS(AttribType)

    void sendPlayerAttribChanged(quint64 idx);

signals:

    void playerAttributeChanged(quint64 idx);

private:

    std::shared_ptr<CommonAPI::Runtime> runtime;
    std::shared_ptr<v1_0::org::genivi::mediamanager::BrowserProxy<>> browserProxy;
    std::shared_ptr<v1_0::org::genivi::mediamanager::IndexerProxy<>> indexerProxy;
    std::shared_ptr<v1_0::org::genivi::mediamanager::PlayerProxy<>> playerProxy;
};

Q_DECLARE_METATYPE(MediaManagerInterface::AttribType)

#endif // MEDIAMANAGERINTERFACE_H
