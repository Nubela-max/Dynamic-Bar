#pragma once
#include <QAbstractListModel>
#include <QList>
struct NotificationItem {
    uint id;
    QString app;
    QString title;
    QString body;
    QStringList actions;
};
class NotificationModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY changed)
public:
    explicit NotificationModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    int count() const { return m_notifications.size(); }
    Q_INVOKABLE void addNotification(uint id, const QString &app, const QString &title, const QString &body);
    Q_INVOKABLE void dismissNotification(uint id);
    Q_INVOKABLE void dismissAll();
signals:
    void changed();
private:
    QList<NotificationItem> m_notifications;
};
