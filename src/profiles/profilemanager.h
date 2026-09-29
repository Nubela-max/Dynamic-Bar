#pragma once
#include <QObject>
class ConfigManager;
class ProfileManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString activeProfile READ activeProfile NOTIFY profileChanged)
    Q_PROPERTY(QStringList availableProfiles READ availableProfiles NOTIFY profileChanged)
public:
    explicit ProfileManager(ConfigManager *config, QObject *parent = nullptr);
    QString activeProfile() const { return m_active; }
    QStringList availableProfiles() const { return {"normal", "gaming", "performance", "minimal"}; }
    Q_INVOKABLE void switchProfile(const QString &name);
    Q_INVOKABLE QVariantMap getProfileSettings(const QString &name) const;
signals:
    void profileChanged();
private:
    void applyProfile(const QString &name);
    ConfigManager *m_config = nullptr;
    QString m_active = "normal";
};
