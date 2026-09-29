#pragma once
#include <QObject>
#include <QTimer>
#include <QDateTime>
class ConfigManager;
class ShellController : public QObject {
 Q_OBJECT
 Q_PROPERTY(int battery READ battery NOTIFY statsChanged)
 Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY statsChanged)
 Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY statsChanged)
 Q_PROPERTY(QString network READ network NOTIFY statsChanged)
 Q_PROPERTY(QString clock READ clock NOTIFY statsChanged)
 Q_PROPERTY(QString activePanel READ activePanel NOTIFY panelChanged)
 Q_PROPERTY(bool expanded READ expanded WRITE setExpanded NOTIFY expandedChanged)
public: explicit ShellController(ConfigManager*,QObject* p=nullptr);
 int battery()const{return m_battery;} int volume()const{return m_volume;} bool muted()const{return m_muted;}
 QString network()const{return m_network;} QString clock()const{return m_clock;} QString activePanel()const{return m_panel;} bool expanded()const{return m_expanded;}
 void setVolume(int);void setMuted(bool);void setExpanded(bool);
 Q_INVOKABLE void openPanel(const QString&); Q_INVOKABLE void closePanel(); Q_INVOKABLE void activateProfile(const QString&); Q_INVOKABLE void powerAction(const QString&); Q_INVOKABLE void notify(const QString&,const QString&);
signals:void statsChanged();void panelChanged();void expandedChanged();void toast(const QString&);
private slots:void tick();
 ConfigManager*m_config;QTimer m_timer;int m_battery=100,m_volume=42;bool m_muted=false,m_expanded=false;QString m_network="Connected",m_clock,m_panel;
};
