// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// 
// Copyright (c) 2016 Jaguar Land Rover.
//
// This program is licensed under the terms and conditions of the
// Mozilla Public License, version 2.0. The full text of the 
// Mozilla Public License is at https://www.mozilla.org/MPL/2.0/
// 
// File:    mediamanagerinterface_plugin.h
// Project: Media Manager QML Plugin
// 
// Created by Jason Anderson
//
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#ifndef MEDIAMANAGERINTERFACE_PLUGIN_H
#define MEDIAMANAGERINTERFACE_PLUGIN_H

#include <QQmlExtensionPlugin>

class MediaManagerInterfacePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // MEDIAMANAGERINTERFACE_PLUGIN_H
