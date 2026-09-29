#include "keybindmanager.h"
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
KeybindManager::KeybindManager(QObject *parent) : QObject(parent) {
    loadKeybinds();
}
QString KeybindManager::getKeybind(const QString &action) const {
    return m_binds.value(action, "");
}
void KeybindManager::setKeybind(const QString &action, const QString &keybind) {
    m_binds[action] = keybind;
    emit changed();
}
void KeybindManager::loadDefaults() {
    m_binds = {
        {"main_pill", "Meta+Space"},
        {"launcher", "Meta+A"},
        {"clipboard", "Meta+V"},
        {"control_center", "Meta+C"},
        {"dashboard", "Meta+D"},
        {"theme_picker", "Meta+T"},
        {"wallpaper", "Meta+W"},
        {"power_menu", "Meta+P"},
        {"notifications", "Meta+N"},
        {"calendar", "Meta+K"},
        {"weather", "Meta+Y"},
        {"settings", "Meta+S"},
        {"media", "Meta+M"},
        {"bluetooth", "Meta+B"},
        {"wifi", "Meta+I"},
        {"dnd", "Meta+Shift+N"},
        {"timer", "Meta+Shift+T"},
        {"volume_osd", "Meta+Shift+V"},
        {"brightness_osd", "Meta+Shift+B"},
        {"perf_monitor", "Meta+Shift+P"}
    };
    emit changed();
}
void KeybindManager::loadKeybinds() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/keybinds.json";
    QFile f(path);
    if (f.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
        QJsonObject obj = doc.object();
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            m_binds[it.key()] = it.value().toString();
        }
        f.close();
    } else {
        loadDefaults();
    }
}
void KeybindManager::saveKeybinds() {
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(dir);
    QFile f(dir + "/keybinds.json");
    if (f.open(QIODevice::WriteOnly)) {
        QJsonObject obj;
        for (auto it = m_binds.begin(); it != m_binds.end(); ++it) {
            obj[it.key()] = it.value();
        }
        f.write(QJsonDocument(obj).toJson());
        f.close();
    }
}
