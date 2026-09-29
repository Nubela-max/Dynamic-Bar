#include "networkmanagerinterface.h"
#include <QDBusReply>
NetworkManagerInterface::NetworkManagerInterface(QObject *parent) : QObject(parent) {
    m_nmInterface = new QDBusInterface("org.freedesktop.NetworkManager",
                                       "/org/freedesktop/NetworkManager",
                                       "org.freedesktop.NetworkManager",
                                       QDBusConnection::systemBus(), this);
    connect(m_nmInterface, SIGNAL(PropertiesChanged(QMap<QString, QVariant>)),
            this, SLOT(onPropertiesChanged()));
    updateStatus();
}
void NetworkManagerInterface::onPropertiesChanged() {
    updateStatus();
}
void NetworkManagerInterface::updateStatus() {
    QDBusReply<uint> state = m_nmInterface->call("Get", "org.freedesktop.DBus.Properties", "ConnectivityState");
    if (state.isValid()) {
        m_connected = state.value() >= 3;
        m_statusText = m_connected ? "Connected" : "Disconnected";
    }
    emit statusChanged();
}
void NetworkManagerInterface::toggleWiFi() {
    QDBusInterface iface("org.freedesktop.NetworkManager", "/org/freedesktop/NetworkManager/Settings",
                        "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
    QDBusReply<QVariant> enabled = iface.call("Get", "org.freedesktop.NetworkManager.Settings", "WirelessEnabled");
    if (enabled.isValid()) {
        setWiFi(!enabled.value().toBool());
    }
}
void NetworkManagerInterface::setWiFi(bool enabled) {
    QDBusInterface iface("org.freedesktop.NetworkManager", "/org/freedesktop/NetworkManager/Settings",
                        "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
    iface.call("Set", "org.freedesktop.NetworkManager.Settings", "WirelessEnabled", QVariant(enabled));
}
