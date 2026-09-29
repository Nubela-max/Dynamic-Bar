#pragma once
#include <QObject>
#include <QString>
class SystemStats : public QObject {
    Q_OBJECT
    Q_PROPERTY(int cpuUsage READ cpuUsage NOTIFY statsChanged)
    Q_PROPERTY(int memoryUsage READ memoryUsage NOTIFY statsChanged)
    Q_PROPERTY(int temperature READ temperature NOTIFY statsChanged)
    Q_PROPERTY(QString uptime READ uptime NOTIFY statsChanged)
public:
    explicit SystemStats(QObject *parent = nullptr);
    int cpuUsage() const { return m_cpuUsage; }
    int memoryUsage() const { return m_memUsage; }
    int temperature() const { return m_temp; }
    QString uptime() const { return m_uptime; }
signals:
    void statsChanged();
private slots:
    void updateStats();
private:
    int m_cpuUsage = 0;
    int m_memUsage = 0;
    int m_temp = 0;
    QString m_uptime;
};
