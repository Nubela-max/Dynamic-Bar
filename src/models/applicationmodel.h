#pragma once
#include <QAbstractListModel>
#include <QList>
struct Application {
    QString name;
    QString icon;
    QString exec;
    QString category;
    bool isFavorite = false;
};
class ApplicationModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QStringList categories READ categories NOTIFY changed)
public:
    explicit ApplicationModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    QStringList categories() const { return m_categories; }
    Q_INVOKABLE void search(const QString &query);
    Q_INVOKABLE void loadApps();
    Q_INVOKABLE void launchApp(int index);
signals:
    void changed();
private:
    void parseDesktopFiles();
    QList<Application> m_apps;
    QList<Application> m_filtered;
    QStringList m_categories;
};
