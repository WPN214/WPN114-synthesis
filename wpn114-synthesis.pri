WPN114_AUDIO_REPOSITORY = ../WPN114-audio
INCLUDEPATH += $$WPN114_AUDIO_REPOSITORY
LIBS += -L$$[QT_INSTALL_QML]/WPN114/Audio -lWPN114-audio

HEADERS += $$PWD/source/ashes/ashes.hpp
SOURCES += $$PWD/source/ashes/ashes.cpp

SOURCES += $$PWD/qml_plugin.cpp
HEADERS += $$PWD/qml_plugin.hpp
