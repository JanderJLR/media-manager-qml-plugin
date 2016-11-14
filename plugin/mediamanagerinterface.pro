TEMPLATE = lib
TARGET = MediaManagerInterface
QT += qml quick
CONFIG += qt plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = Automotive.MediaManagerInterface

SYSROOT = $$(PKG_CONFIG_SYSROOT_DIR)
MM_SRC_DIR = $${SYSROOT}/usr/src/media-manager/v1_0/org/genivi/mediamanager/

# Input
SOURCES += \
    mediamanagerinterface_plugin.cpp \
    mediamanagerinterface.cpp \
    $${MM_SRC_DIR}/BrowserDBusDeployment.cpp \
    $${MM_SRC_DIR}/BrowserDBusProxy.cpp \
    $${MM_SRC_DIR}/BrowserDBusStubAdapter.cpp \
    $${MM_SRC_DIR}/BrowserStubDefault.cpp \
    $${MM_SRC_DIR}/BrowserTypes.cpp \
    $${MM_SRC_DIR}/BrowserTypesDBusDeployment.cpp \
    $${MM_SRC_DIR}/Indexer.cpp \
    $${MM_SRC_DIR}/IndexerDBusDeployment.cpp \
    $${MM_SRC_DIR}/IndexerDBusProxy.cpp \
    $${MM_SRC_DIR}/IndexerDBusStubAdapter.cpp \
    $${MM_SRC_DIR}/IndexerStubDefault.cpp \
    $${MM_SRC_DIR}/MediaTypes.cpp \
    $${MM_SRC_DIR}/MediaTypesDBusDeployment.cpp \
    $${MM_SRC_DIR}/PlayerDBusDeployment.cpp \
    $${MM_SRC_DIR}/PlayerDBusProxy.cpp \
    $${MM_SRC_DIR}/PlayerDBusStubAdapter.cpp \
    $${MM_SRC_DIR}/PlayerStubDefault.cpp \
    $${MM_SRC_DIR}/PlayerTypes.cpp \
    $${MM_SRC_DIR}/PlayerTypesDBusDeployment.cpp

HEADERS += \
    mediamanagerinterface_plugin.h \
    mediamanagerinterface.h \
    $${MM_SRC_DIR}/Browser.hpp \
    $${MM_SRC_DIR}/BrowserDBusDeployment.hpp \
    $${MM_SRC_DIR}/BrowserDBusProxy.hpp \
    $${MM_SRC_DIR}/BrowserDBusStubAdapter.hpp \
    $${MM_SRC_DIR}/BrowserProxy.hpp \
    $${MM_SRC_DIR}/BrowserProxyBase.hpp \
    $${MM_SRC_DIR}/BrowserStub.hpp \
    $${MM_SRC_DIR}/BrowserStubDefault.hpp \
    $${MM_SRC_DIR}/BrowserTypes.hpp \
    $${MM_SRC_DIR}/BrowserTypesDBusDeployment.hpp \
    $${MM_SRC_DIR}/Indexer.hpp \
    $${MM_SRC_DIR}/IndexerDBusDeployment.hpp \
    $${MM_SRC_DIR}/IndexerDBusProxy.hpp \
    $${MM_SRC_DIR}/IndexerDBusStubAdapter.hpp \
    $${MM_SRC_DIR}/IndexerProxy.hpp \
    $${MM_SRC_DIR}/IndexerProxyBase.hpp \
    $${MM_SRC_DIR}/IndexerStub.hpp \
    $${MM_SRC_DIR}/IndexerStubDefault.hpp \
    $${MM_SRC_DIR}/MediaTypes.hpp \
    $${MM_SRC_DIR}/MediaTypesDBusDeployment.hpp \
    $${MM_SRC_DIR}/Player.hpp \
    $${MM_SRC_DIR}/PlayerDBusDeployment.hpp \
    $${MM_SRC_DIR}/PlayerDBusProxy.hpp \
    $${MM_SRC_DIR}/PlayerDBusStubAdapter.hpp \
    $${MM_SRC_DIR}/PlayerProxy.hpp \
    $${MM_SRC_DIR}/PlayerProxyBase.hpp \
    $${MM_SRC_DIR}/PlayerStub.hpp \
    $${MM_SRC_DIR}/PlayerStubDefault.hpp \
    $${MM_SRC_DIR}/PlayerTypes.hpp \
    $${MM_SRC_DIR}/PlayerTypesDBusDeployment.hpp

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter -Wno-ignored-qualifiers -Wno-maybe-uninitialized -Wno-uninitialized \
                          -Wno-deprecated-declarations

INCLUDEPATH += $${SYSROOT}/usr/include/dbus-1.0/ \
               $${SYSROOT}/usr/lib/dbus-1.0/include/ \
               $${SYSROOT}/usr/include/CommonAPI-3.1/ \
               $${SYSROOT}/usr/lib/ \
               $${SYSROOT}/usr/src/media-manager

LIBS += -lCommonAPI -lCommonAPI-DBus

#unix:!macx: LIBS += -ldbus-1
