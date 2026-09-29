#include "profilemanager.h"
#include "../configmanager.h"
ProfileManager::ProfileManager(ConfigManager *config, QObject *parent)
    : QObject(parent), m_config(config), m_active(config->value("profile", "normal").toString()) {}
void ProfileManager::switchProfile(const QString &name) {
    if (name == m_active) return;
    m_active = name;
    applyProfile(name);
    m_config->setValue("profile", name);
    emit profileChanged();
}
QVariantMap ProfileManager::getProfileSettings(const QString &name) const {
    QVariantMap settings;
    if (name == "normal") {
        settings = {{"animations", true}, {"showBattery", true}, {"showVolume", true}, {"showNetwork", true}, {"showWorkspaces", true}};
    } else if (name == "gaming") {
        settings = {{"animations", false}, {"showBattery", true}, {"showVolume", false}, {"showNetwork", false}, {"showWorkspaces", false}};
    } else if (name == "performance") {
        settings = {{"animations", false}, {"showCPU", true}, {"showRAM", true}, {"showTemp", true}, {"showFreq", true}};
    } else if (name == "minimal") {
        settings = {{"animations", true}, {"showBattery", false}, {"showVolume", false}, {"showNetwork", false}, {"showWorkspaces", false}};
    }
    return settings;
}
void ProfileManager::applyProfile(const QString &name) {
    auto settings = getProfileSettings(name);
    for (auto it = settings.begin(); it != settings.end(); ++it) {
        m_config->setValue(it.key(), it.value());
    }
}
