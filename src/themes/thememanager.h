#pragma once
#include <QObject>
#include <QVariantMap>
#include <QStringList>
class ThemeManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString activeTheme READ activeTheme WRITE setActiveTheme NOTIFY themeChanged)
    Q_PROPERTY(QStringList availableThemes READ availableThemes NOTIFY themeChanged)
public:
    explicit ThemeManager(QObject *parent = nullptr);
    QString activeTheme() const { return m_active; }
    void setActiveTheme(const QString &name);
    QStringList availableThemes() const { return m_themes.keys(); }
    Q_INVOKABLE QVariantMap getTheme(const QString &name) const;
    Q_INVOKABLE void saveCustomTheme(const QString &name, const QVariantMap &theme);
    Q_INVOKABLE void deleteTheme(const QString &name);
signals:
    void themeChanged();
private:
    void loadThemes();
    QMap<QString, QVariantMap> m_themes;
    QString m_active = "Midnight";
};
