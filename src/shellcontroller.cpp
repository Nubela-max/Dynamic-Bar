#include "shellcontroller.h"
#include "configmanager.h"
#include <QProcess>
ShellController::ShellController(ConfigManager*c,QObject*p):QObject(p),m_config(c){connect(&m_timer,&QTimer::timeout,this,&ShellController::tick);m_timer.start(1000);tick();}
void ShellController::tick(){m_clock=QDateTime::currentDateTime().toString("HH:mm");emit statsChanged();}
void ShellController::setVolume(int v){m_volume=qBound(0,v,100);emit statsChanged();}
void ShellController::setMuted(bool v){m_muted=v;emit statsChanged();}
void ShellController::setExpanded(bool v){if(m_expanded==v)return;m_expanded=v;emit expandedChanged();}
void ShellController::openPanel(const QString&p){m_panel=p;m_expanded=true;emit panelChanged();emit expandedChanged();}
void ShellController::closePanel(){m_panel.clear();m_expanded=false;emit panelChanged();emit expandedChanged();}
void ShellController::activateProfile(const QString&p){m_config->setProfile(p);emit toast("Profile: "+p);}
void ShellController::powerAction(const QString&a){if(a=="lock")QProcess::startDetached("loginctl",{"lock-session"});else if(a=="sleep")QProcess::startDetached("systemctl",{"suspend"});else if(a=="logout")QProcess::startDetached("loginctl",{"terminate-user",qEnvironmentVariable("USER")});else if(a=="reboot"||a=="shutdown")emit toast("Confirm "+a+" in your desktop session");}
void ShellController::notify(const QString&t,const QString&b){emit toast(t+": "+b);}
