#include "qml_plugin.hpp"

#include <source/pinknoise/pinknoise.hpp>
#include <QQmlEngine>
#include <qqml.h>

//-------------------------------------------------------------------------------------------------
void
qml_plugin::registerTypes(const char *uri)
//-------------------------------------------------------------------------------------------------
{
    Q_UNUSED(uri)

    qmlRegisterType<Ashes, 1>
    ("WPN114.Audio.Synthesis", 1, 1, "PinkNoise" );
}
