#pragma once
#include <QObject>
#include <QStringList>
class WallpaperManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList available READ available NOTIFY changed)
    Q_PROPERTY(QString current READ current NOTIFY changed)
public:
    explicit WallpaperManager(QObject *parent = nullptr);
    QStringList available() const { return m_available; }
    QString current() const { return m_current; }
    Q_INVOKABLE void setWallpaper(const QString &path);
    Q_INVOKABLE void refresh();
signals:
    void changed();
private:
    void loadWallpapers();
    QStringList m_available;
    QString m_current;
};
