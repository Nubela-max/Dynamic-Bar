#pragma once
#include <QObject>
#include <QString>
#include <QDBusInterface>
#include <QDBusConnection>
class NetworkManagerInterface : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusChanged)
    Q_PROPERTY(bool connected READ isConnected NOTIFY statusChanged)
    Q_PROPERTY(QString ssid READ ssid NOTIFY statusChanged)
public:
    explicit NetworkManagerInterface(QObject *parent = nullptr);
    QString statusText() const { return m_statusText; }
    bool isConnected() const { return m_connected; }
    QString ssid() const { return m_ssid; }
    Q_INVOKABLE void toggleWiFi();
    Q_INVOKABLE void setWiFi(bool enabled);
signals:
    void statusChanged();
private slots:
    void onPropertiesChanged();
private:
    void updateStatus();
    QDBusInterface *m_nmInterface = nullptr;
    QString m_statusText = "Disconnected";
    bool m_connected = false;
    QString m_ssid;
};
