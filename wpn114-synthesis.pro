TARGET = WPN114-synthesis
TEMPLATE = lib
CONFIG += c++11 dll
QT += quick

localmod: DESTDIR = $$QML_MODULE_DESTDIR/WPN114/Audio/Synthesis
else {
    DESTDIR = $$[QT_INSTALL_QML]/WPN114/Audio/Synthesis
    QML_MODULE_DESTDIR = $$[QT_INSTALL_QML]
}

for(FILE,QMLDIR_FILES) {
    QMAKE_POST_LINK += $$quote(cp $${FILE} $${DESTDIR}$$escape_expand(\n\t))
}

WPN114_AUDIO_REPOSITORY = ../WPN114-audio
INCLUDEPATH += $$WPN114_AUDIO_REPOSITORY
LIBS += -L$$QML_MODULE_DESTDIR/WPN114/Audio -lWPN114-audio
QMAKE_LFLAGS += -Wl,-rpath,$$QML_MODULE_DESTDIR/WPN114/Audio

HEADERS += $$PWD/source/ashes/ashes.hpp
SOURCES += $$PWD/source/ashes/ashes.cpp

SOURCES += $$PWD/qml_plugin.cpp
HEADERS += $$PWD/qml_plugin.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
