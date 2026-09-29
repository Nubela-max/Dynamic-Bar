#include "configmanager.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
ConfigManager::ConfigManager(QObject *p):QObject(p){ load(); }
QString ConfigManager::profile() const { return m_profile; }
void ConfigManager::setProfile(const QString &v){ if(v==m_profile)return; m_profile=v; m_values["profile"]=v; emit changed(); save(); }
QVariant ConfigManager::value(const QString &k,const QVariant &f) const{return m_values.value(k,f);}
void ConfigManager::setValue(const QString &k,const QVariant &v){m_values[k]=v;emit changed();save();}
void ConfigManager::load(){
    const auto path=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+"/config.json";
    QFile f(path); if(f.open(QIODevice::ReadOnly)){m_values=QJsonDocument::fromJson(f.readAll()).object().toVariantMap();m_profile=m_values.value("profile","default").toString();}
    if(m_values.isEmpty()) reset();
}
void ConfigManager::save(){const auto dir=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);QDir().mkpath(dir);QFile f(dir+"/config.json");if(f.open(QIODevice::WriteOnly))f.write(QJsonDocument::fromVariant(m_values).toJson(QJsonDocument::Indented));}
void ConfigManager::reset(){m_values={{"profile","default"},{"theme","Midnight"},{"accent","#8bd5ca"},{"compactWidth",520},{"showBattery",true},{"showVolume",true},{"showNetwork",true},{"showWorkspaces",true},{"animations",true},{"opacity",0.96}};emit changed();save();}
