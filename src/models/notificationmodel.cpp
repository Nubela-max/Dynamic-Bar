#include "notificationmodel.h"
NotificationModel::NotificationModel(QObject *parent) : QAbstractListModel(parent) {}
int NotificationModel::rowCount(const QModelIndex &) const {
    return m_notifications.size();
}
QVariant NotificationModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return {};
    const auto &notif = m_notifications[index.row()];
    switch (role) {
        case Qt::DisplayRole: return notif.title;
        case Qt::UserRole: return notif.body;
        case Qt::UserRole + 1: return notif.app;
        default: return {};
    }
}
QHash<int, QByteArray> NotificationModel::roleNames() const {
    return {{Qt::DisplayRole, "title"}, {Qt::UserRole, "body"}, {Qt::UserRole + 1, "app"}};
}
void NotificationModel::addNotification(uint id, const QString &app, const QString &title, const QString &body) {
    beginInsertRows(QModelIndex(), 0, 0);
    m_notifications.prepend({id, app, title, body, {}});
    endInsertRows();
    emit changed();
}
void NotificationModel::dismissNotification(uint id) {
    for (int i = 0; i < m_notifications.size(); ++i) {
        if (m_notifications[i].id == id) {
            beginRemoveRows(QModelIndex(), i, i);
            m_notifications.removeAt(i);
            endRemoveRows();
            emit changed();
            return;
        }
    }
}
void NotificationModel::dismissAll() {
    beginRemoveRows(QModelIndex(), 0, m_notifications.size() - 1);
    m_notifications.clear();
    endRemoveRows();
    emit changed();
}
