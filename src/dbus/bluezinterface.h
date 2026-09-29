#pragma once
#include <QObject>
#include <QString>
#include <QDBusInterface>
class BlueZInterface : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool powered READ isPowered WRITE setPowered NOTIFY stateChanged)
    Q_PROPERTY(QStringList connectedDevices READ connectedDevices NOTIFY devicesChanged)
public:
    explicit BlueZInterface(QObject *parent = nullptr);
    bool isPowered() const { return m_powered; }
    QStringList connectedDevices() const { return m_devices; }
    void setPowered(bool state);
    Q_INVOKABLE void toggleBluetooth();
signals:
    void stateChanged();
    void devicesChanged();
private slots:
    void onPropertiesChanged();
private:
    void updateState();
    QDBusInterface *m_bluezInterface = nullptr;
    bool m_powered = false;
    QStringList m_devices;
};
