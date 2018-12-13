#include "qml_plugin.hpp"

#include <source/ashes/ashes.hpp>
#include <QQmlEngine>
#include <qqml.h>

void qml_plugin::registerTypes(const char *uri)
{
    Q_UNUSED    ( uri );

    qmlRegisterType<Ashes, 1> ( "WPN114", 1, 0, "Ashes" );
}
