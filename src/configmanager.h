#pragma once
#include <QObject>
#include <QVariantMap>
#include <QTimer>
class ConfigManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString profile READ profile WRITE setProfile NOTIFY changed)
    Q_PROPERTY(QVariantMap values READ values NOTIFY changed)
public:
    explicit ConfigManager(QObject *parent=nullptr);
    QString profile() const; void setProfile(const QString &value);
    QVariantMap values() const { return m_values; }
    Q_INVOKABLE QVariant value(const QString &key, const QVariant &fallback={}) const;
    Q_INVOKABLE void setValue(const QString &key, const QVariant &value);
    Q_INVOKABLE void save(); Q_INVOKABLE void reset();
signals: void changed();
private: void load(); QString m_profile="default"; QVariantMap m_values;
};
