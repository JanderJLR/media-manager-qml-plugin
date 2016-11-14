// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// 
// Copyright (c) 2016 Jaguar Land Rover.
//
// This program is licensed under the terms and conditions of the
// Mozilla Public License, version 2.0. The full text of the 
// Mozilla Public License is at https://www.mozilla.org/MPL/2.0/
// 
// File:    mediamanagerinterface_plugin.cpp
// Project: Media Manager QML Plugin
// 
// Created by Jason Anderson
//
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#include "mediamanagerinterface_plugin.h"
#include "mediamanagerinterface.h"

#include <qqml.h>

void MediaManagerInterfacePlugin::registerTypes(const char *uri)
{
    // @uri Automotive.MediaManagerInterface
    qmlRegisterType<MediaManagerInterface>(uri, 1, 0, "MediaManagerInterface");
    qRegisterMetaType<MediaManagerInterface::AttribType>("MediaManagerInterface::AttribType");
}

