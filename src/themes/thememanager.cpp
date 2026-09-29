#include "thememanager.h"
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QDir>
ThemeManager::ThemeManager(QObject *parent) : QObject(parent) {
    loadThemes();
}
void ThemeManager::loadThemes() {
    m_themes.clear();
    m_themes["Midnight"] = {{
        {"bg", "#101824"}, {"surface", "#202c3d"}, {"accent", "#8bd5ca"},
        {"text", "#e8edf5"}, {"textSecondary", "#a9b6c8"}, {"border", "#2c3b50"}
    }};
    m_themes["Twilight"] = {{
        {"bg", "#1a1a2e"}, {"surface", "#16213e"}, {"accent", "#d4af37"},
        {"text", "#eaeaea"}, {"textSecondary", "#b0b0b0"}, {"border", "#2d3561"}
    }};
    m_themes["Dracula"] = {{
        {"bg", "#282a36"}, {"surface", "#44475a"}, {"accent", "#ff79c6"},
        {"text", "#f8f8f2"}, {"textSecondary", "#bd93f9"}, {"border", "#6272a4"}
    }};
    m_themes["Nord"] = {{
        {"bg", "#2e3440"}, {"surface", "#3b4252"}, {"accent", "#88c0d0"},
        {"text", "#eceff4"}, {"textSecondary", "#d8dee9"}, {"border", "#434c5e"}
    }};
    QString customPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/themes";
    QDir dir(customPath);
    if (dir.exists()) {
        QStringList files = dir.entryList({"*.json"}, QDir::Files);
        for (const auto &file : files) {
            QFile f(dir.absoluteFilePath(file));
            if (f.open(QIODevice::ReadOnly)) {
                auto obj = QJsonDocument::fromJson(f.readAll()).object().toVariantMap();
                m_themes[file.replace(".json", "")] = obj;
                f.close();
            }
        }
    }
}
void ThemeManager::setActiveTheme(const QString &name) {
    if (m_active == name) return;
    if (!m_themes.contains(name)) return;
    m_active = name;
    emit themeChanged();
}
QVariantMap ThemeManager::getTheme(const QString &name) const {
    return m_themes.value(name, {});
}
void ThemeManager::saveCustomTheme(const QString &name, const QVariantMap &theme) {
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/themes";
    QDir().mkpath(dir);
    QFile f(dir + "/" + name + ".json");
    if (f.open(QIODevice::WriteOnly)) {
        f.write(QJsonDocument::fromVariant(theme).toJson());
        f.close();
        m_themes[name] = theme;
        emit themeChanged();
    }
}
void ThemeManager::deleteTheme(const QString &name) {
    if (m_themes.contains(name) && name != "Midnight") {
        m_themes.remove(name);
        QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/themes/" + name + ".json";
        QFile::remove(path);
        emit themeChanged();
    }
}
