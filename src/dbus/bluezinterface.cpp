#include "bluezinterface.h"
#include <QDBusConnection>
#include <QDBusReply>
BlueZInterface::BlueZInterface(QObject *parent) : QObject(parent) {
    m_bluezInterface = new QDBusInterface("org.bluez", "/", "org.freedesktop.DBus.ObjectManager",
                                         QDBusConnection::systemBus(), this);
    connect(m_bluezInterface, SIGNAL(InterfacesAdded(QDBusObjectPath, QMap<QString, QMap<QString, QVariant>>)),
            this, SLOT(onPropertiesChanged()));
    connect(m_bluezInterface, SIGNAL(InterfacesRemoved(QDBusObjectPath, QStringList)),
            this, SLOT(onPropertiesChanged()));
    updateState();
}
void BlueZInterface::onPropertiesChanged() {
    updateState();
}
void BlueZInterface::updateState() {
    m_powered = true;
    emit stateChanged();
}
void BlueZInterface::setPowered(bool state) {
    QDBusInterface adapter("org.bluez", "/org/bluez/hci0", "org.freedesktop.DBus.Properties",
                          QDBusConnection::systemBus(), this);
    adapter.call("Set", "org.bluez.Adapter1", "Powered", QVariant(state));
    m_powered = state;
    emit stateChanged();
}
void BlueZInterface::toggleBluetooth() {
    setPowered(!m_powered);
}
