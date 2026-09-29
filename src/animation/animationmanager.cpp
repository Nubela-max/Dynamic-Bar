#include "animationmanager.h"
AnimationManager::AnimationManager(QObject *parent) : QObject(parent) {}
int AnimationManager::getDuration(const QString &type) const {
    return m_enabled ? m_durations.value(type, 150) : 0;
}
QString AnimationManager::getEasing(const QString &type) const {
    if (type.contains("expand") || type.contains("collapse")) return "Easing.InOutQuad";
    if (type.contains("hover")) return "Easing.OutQuad";
    return "Easing.InOutQuad";
}
void AnimationManager::setAnimationsEnabled(bool enabled) {
    m_enabled = enabled;
}
