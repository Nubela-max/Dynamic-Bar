#include "notificationdaemon.h"
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusMetaType>
#include <QApplication>
Q_DECLARE_METATYPE(QImage)
NotificationDaemon::NotificationDaemon(QObject *parent) : QObject(parent) {
    qDBusRegisterMetaType<QImage>();
    QDBusConnection::sessionBus().registerService("org.freedesktop.Notifications");
    QDBusConnection::sessionBus().registerObject("/org/freedesktop/Notifications", this, QDBusConnection::ExportScriptableSlots | QDBusConnection::ExportScriptableSignals);
}
NotificationDaemon::~NotificationDaemon() {
    QDBusConnection::sessionBus().unregisterObject("/org/freedesktop/Notifications");
    QDBusConnection::sessionBus().unregisterService("org.freedesktop.Notifications");
}
QString NotificationDaemon::GetServerInformation(QString &vendor, QString &version, QString &spec_version) {
    vendor = "Nubela";
    version = "0.1.0";
    spec_version = "1.2";
    return "Dynamic Bar";
}
QStringList NotificationDaemon::GetCapabilities() {
    return {"body", "body-markup", "icon-static", "actions", "action-icons"};
}
uint NotificationDaemon::Notify(const QString &app_name, uint replaces_id, const QString &app_icon,
                                 const QString &summary, const QString &body, const QStringList &actions,
                                 const QMap<QString, QVariant> &hints, int expire_timeout) {
    uint id = replaces_id ? replaces_id : m_nextId++;
    Notification notif;
    notif.id = id;
    notif.appName = app_name;
    notif.summary = summary;
    notif.body = body;
    notif.actions = actions;
    notif.hints = hints;
    notif.expireTimeout = expire_timeout > 0 ? expire_timeout : 5000;
    m_notifications[id] = notif;
    emit notificationReceived(notif);
    if (expire_timeout >= 0) {
        QTimer::singleShot(notif.expireTimeout, this, [this, id]() {
            if (m_notifications.contains(id)) {
                m_notifications.remove(id);
                emit NotificationClosed(id, 1);
            }
        });
    }
    return id;
}
void NotificationDaemon::CloseNotification(uint id) {
    if (m_notifications.contains(id)) {
        m_notifications.remove(id);
        emit NotificationClosed(id, 2);
    }
}
