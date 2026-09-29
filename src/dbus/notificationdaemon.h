#pragma once
#include <QObject>
#include <QDBusContext>
#include <QList>
#include <QMap>
#include <QImage>
#include <QDBusUnixFileDescriptor>
struct Notification {
    uint id;
    QString appName;
    QString summary;
    QString body;
    QStringList actions;
    QMap<QString, QVariant> hints;
    int expireTimeout;
    QImage icon;
};
class NotificationDaemon : public QObject, protected QDBusContext {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")
public:
    explicit NotificationDaemon(QObject *parent = nullptr);
    ~NotificationDaemon();
    Q_SCRIPTABLE QString GetServerInformation(QString &vendor, QString &version, QString &spec_version);
    Q_SCRIPTABLE QStringList GetCapabilities();
    Q_SCRIPTABLE uint Notify(const QString &app_name, uint replaces_id, const QString &app_icon,
                              const QString &summary, const QString &body, const QStringList &actions,
                              const QMap<QString, QVariant> &hints, int expire_timeout);
    Q_SCRIPTABLE void CloseNotification(uint id);
signals:
    void NotificationClosed(uint id, uint reason);
    void ActionInvoked(uint id, const QString &action_key);
    void notificationReceived(const Notification &notif);
private:
    uint m_nextId = 1;
    QMap<uint, Notification> m_notifications;
};
