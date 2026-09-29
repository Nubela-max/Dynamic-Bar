#include "shellcontroller.h"

#include "configmanager.h"

#include <QDateTime>
#include <QProcess>

ShellController::ShellController(ConfigManager *config, QObject *parent)
    : QObject(parent), m_config(config)
{
    connect(&m_timer, &QTimer::timeout, this, &ShellController::tick);
    m_timer.start(1000);
    tick();
}

int ShellController::battery() const { return m_battery; }
int ShellController::volume() const { return m_volume; }
bool ShellController::muted() const { return m_muted; }
QString ShellController::network() const { return m_network; }
QString ShellController::clock() const { return m_clock; }
QString ShellController::activePanel() const { return m_panel; }
bool ShellController::expanded() const { return m_expanded; }

void ShellController::tick()
{
    m_clock = QDateTime::currentDateTime().toString(QStringLiteral("HH:mm"));
    emit statsChanged();
}

void ShellController::setVolume(int value)
{
    const int bounded = qBound(0, value, 100);
    if (m_volume == bounded) return;
    m_volume = bounded;
    emit statsChanged();
}

void ShellController::setMuted(bool value)
{
    if (m_muted == value) return;
    m_muted = value;
    emit statsChanged();
}

void ShellController::setExpanded(bool value)
{
    if (m_expanded == value) return;
    m_expanded = value;
    emit expandedChanged();
}

void ShellController::openPanel(const QString &panel)
{
    m_panel = panel;
    m_expanded = true;
    emit panelChanged();
    emit expandedChanged();
}

void ShellController::closePanel()
{
    m_panel.clear();
    m_expanded = false;
    emit panelChanged();
    emit expandedChanged();
}

void ShellController::activateProfile(const QString &profile)
{
    if (m_config) m_config->setProfile(profile);
    emit toast(QStringLiteral("Profile: ") + profile);
}

void ShellController::powerAction(const QString &action)
{
    if (action == QStringLiteral("lock")) {
        QProcess::startDetached(QStringLiteral("loginctl"), {QStringLiteral("lock-session")});
    } else if (action == QStringLiteral("sleep")) {
        QProcess::startDetached(QStringLiteral("systemctl"), {QStringLiteral("suspend")});
    } else if (action == QStringLiteral("logout")) {
        QProcess::startDetached(QStringLiteral("loginctl"), {QStringLiteral("terminate-user"), qEnvironmentVariable("USER")});
    } else {
        emit toast(QStringLiteral("Confirm ") + action + QStringLiteral(" in your desktop session"));
    }
}

void ShellController::showToast(const QString &title, const QString &body)
{
    emit toast(title + QStringLiteral(": ") + body);
}
