#include "batterymonitor.h"
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QTextStream>
BatteryMonitor::BatteryMonitor(QObject *parent) : QObject(parent) {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BatteryMonitor::update);
    timer->start(2000);
    update();
}
void BatteryMonitor::update() {
    QString sysPath = "/sys/class/power_supply";
    QDir dir(sysPath);
    QStringList batts = dir.entryList(QStringList("BAT*"), QDir::Dirs | QDir::NoDotAndDotDot);
    if (batts.isEmpty()) return;
    QString batPath = sysPath + "/" + batts.first();
    auto readFile = [](const QString &path) -> QString {
        QFile f(path);
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&f);
            QString line = in.readLine();
            f.close();
            return line;
        }
        return "";
    };
    bool ok;
    int now = readFile(batPath + "/energy_now").toInt(&ok);
    int full = readFile(batPath + "/energy_full").toInt(&ok);
    if (full > 0) m_percentage = (now * 100) / full;
    QString status = readFile(batPath + "/status").trimmed();
    m_charging = (status == "Charging");
    m_status = status;
    emit changed();
}
