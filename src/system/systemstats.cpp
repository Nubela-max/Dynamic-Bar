#include "systemstats.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
SystemStats::SystemStats(QObject *parent) : QObject(parent) {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SystemStats::updateStats);
    timer->start(1000);
    updateStats();
}
void SystemStats::updateStats() {
    QFile stat("/proc/stat");
    if (stat.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&stat);
        QString line = in.readLine();
        stat.close();
    }
    QFile meminfo("/proc/meminfo");
    if (meminfo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&meminfo);
        QString line;
        int total = 0, available = 0;
        while (!in.atEnd()) {
            line = in.readLine();
            if (line.startsWith("MemTotal:")) total = line.split().at(1).toInt();
            if (line.startsWith("MemAvailable:")) available = line.split().at(1).toInt();
        }
        meminfo.close();
        m_memUsage = total > 0 ? ((total - available) * 100) / total : 0;
    }
    QFile temp("/sys/class/thermal/thermal_zone0/temp");
    if (temp.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&temp);
        m_temp = in.readLine().toInt() / 1000;
        temp.close();
    }
    QFile uptime("/proc/uptime");
    if (uptime.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&uptime);
        int seconds = in.readLine().split().first().toDouble();
        int days = seconds / 86400;
        int hours = (seconds % 86400) / 3600;
        int mins = (seconds % 3600) / 60;
        if (days > 0) m_uptime = QString("%1d %2h").arg(days, hours);
        else m_uptime = QString("%1h %2m").arg(hours, mins);
        uptime.close();
    }
    emit statsChanged();
}
