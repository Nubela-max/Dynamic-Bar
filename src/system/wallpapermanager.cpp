#include "wallpapermanager.h"
#include <QStandardPaths>
#include <QDir>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QProcess>
WallpaperManager::WallpaperManager(QObject *parent) : QObject(parent) {
    loadWallpapers();
}
void WallpaperManager::loadWallpapers() {
    m_available.clear();
    QString wallpapersPath = QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                                    "backgrounds", QStandardPaths::LocateDirectory);
    if (!wallpapersPath.isEmpty()) {
        QDir dir(wallpapersPath);
        m_available = dir.entryList({"*.jpg", "*.png", "*.jpeg"}, QDir::Files);
    }
}
void WallpaperManager::setWallpaper(const QString &path) {
    QProcess::startDetached("cp", {path, QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/dynamic-bar/wallpaper.jpg"});
    QDBusInterface iface("org.kde.plasmashell", "/org/kde/PlasmaShell", "org.kde.PlasmaShell",
                        QDBusConnection::sessionBus());
    iface.call("evaluateScript", "desktop.wallpaperForScreen(0).wallpaperPath = '" + path + "'");
    m_current = path;
    emit changed();
}
void WallpaperManager::refresh() {
    loadWallpapers();
    emit changed();
}
