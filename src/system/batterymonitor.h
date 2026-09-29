#pragma once
#include <QObject>
#include <QString>
class BatteryMonitor : public QObject {
    Q_OBJECT
    Q_PROPERTY(int percentage READ percentage NOTIFY changed)
    Q_PROPERTY(QString status READ status NOTIFY changed)
    Q_PROPERTY(bool charging READ isCharging NOTIFY changed)
    Q_PROPERTY(int timeRemaining READ timeRemaining NOTIFY changed)
public:
    explicit BatteryMonitor(QObject *parent = nullptr);
    int percentage() const { return m_percentage; }
    QString status() const { return m_status; }
    bool isCharging() const { return m_charging; }
    int timeRemaining() const { return m_timeRemaining; }
signals:
    void changed();
private slots:
    void update();
private:
    int m_percentage = 100;
    QString m_status = "Full";
    bool m_charging = false;
    int m_timeRemaining = 0;
};
