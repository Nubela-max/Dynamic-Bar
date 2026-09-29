#pragma once

#include <QObject>
#include <QTimer>
#include <QString>

class ConfigManager;

class ShellController final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int battery READ battery NOTIFY statsChanged)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY statsChanged)
    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY statsChanged)
    Q_PROPERTY(QString network READ network NOTIFY statsChanged)
    Q_PROPERTY(QString clock READ clock NOTIFY statsChanged)
    Q_PROPERTY(QString activePanel READ activePanel NOTIFY panelChanged)
    Q_PROPERTY(bool expanded READ expanded WRITE setExpanded NOTIFY expandedChanged)

public:
    explicit ShellController(ConfigManager *config, QObject *parent = nullptr);

    int battery() const;
    int volume() const;
    bool muted() const;
    QString network() const;
    QString clock() const;
    QString activePanel() const;
    bool expanded() const;

    void setVolume(int value);
    void setMuted(bool value);
    void setExpanded(bool value);

    Q_INVOKABLE void openPanel(const QString &panel);
    Q_INVOKABLE void closePanel();
    Q_INVOKABLE void activateProfile(const QString &profile);
    Q_INVOKABLE void powerAction(const QString &action);
    Q_INVOKABLE void showToast(const QString &title, const QString &body);

signals:
    void statsChanged();
    void panelChanged();
    void expandedChanged();
    void toast(const QString &message);

private slots:
    void tick();

private:
    ConfigManager *m_config = nullptr;
    QTimer m_timer;
    int m_battery = 100;
    int m_volume = 42;
    bool m_muted = false;
    bool m_expanded = false;
    QString m_network = QStringLiteral("Connected");
    QString m_clock;
    QString m_panel;
};
