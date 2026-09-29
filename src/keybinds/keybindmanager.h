#pragma once
#include <QObject>
#include <QMap>
#include <QString>
class KeybindManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList keybinds READ keybinds NOTIFY changed)
public:
    explicit KeybindManager(QObject *parent = nullptr);
    QStringList keybinds() const { return m_binds.keys(); }
    Q_INVOKABLE QString getKeybind(const QString &action) const;
    Q_INVOKABLE void setKeybind(const QString &action, const QString &keybind);
    Q_INVOKABLE void loadDefaults();
    Q_INVOKABLE void saveKeybinds();
signals:
    void changed();
    void actionTriggered(const QString &action);
private:
    void loadKeybinds();
    QMap<QString, QString> m_binds;
};
