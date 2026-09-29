#pragma once
#include <QObject>
#include <QMap>
#include <QString>
class AnimationManager : public QObject {
    Q_OBJECT
public:
    explicit AnimationManager(QObject *parent = nullptr);
    Q_INVOKABLE int getDuration(const QString &type) const;
    Q_INVOKABLE QString getEasing(const QString &type) const;
    Q_INVOKABLE void setAnimationsEnabled(bool enabled);
private:
    QMap<QString, int> m_durations = {
        {"pill_expand", 180}, {"pill_collapse", 180}, {"module_appear", 120},
        {"module_disappear", 120}, {"button_hover", 100}, {"scroll", 150}
    };
    bool m_enabled = true;
};
