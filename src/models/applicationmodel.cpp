#include "applicationmodel.h"
#include <QStandardPaths>
#include <QDir>
#include <QSettings>
#include <QProcess>
ApplicationModel::ApplicationModel(QObject *parent) : QAbstractListModel(parent) {
    loadApps();
}
int ApplicationModel::rowCount(const QModelIndex &) const {
    return m_filtered.size();
}
QVariant ApplicationModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return {};
    const auto &app = m_filtered[index.row()];
    switch (role) {
        case Qt::DisplayRole: return app.name;
        case Qt::DecorationRole: return app.icon;
        default: return {};
    }
}
QHash<int, QByteArray> ApplicationModel::roleNames() const {
    return {{Qt::DisplayRole, "name"}, {Qt::DecorationRole, "icon"}};
}
void ApplicationModel::search(const QString &query) {
    m_filtered.clear();
    for (const auto &app : m_apps) {
        if (app.name.contains(query, Qt::CaseInsensitive) || app.category.contains(query, Qt::CaseInsensitive)) {
            m_filtered.append(app);
        }
    }
    emit changed();
}
void ApplicationModel::loadApps() {
    parseDesktopFiles();
    m_filtered = m_apps;
    emit changed();
}
void ApplicationModel::parseDesktopFiles() {
    m_apps.clear();
    m_categories.clear();
    QStringList appDirs = {
        QStandardPaths::locate(QStandardPaths::GenericDataLocation, "applications", QStandardPaths::LocateDirectory),
        QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/applications"
    };
    for (const auto &appDir : appDirs) {
        QDir dir(appDir);
        QStringList files = dir.entryList({"*.desktop"}, QDir::Files);
        for (const auto &file : files) {
            QSettings desktop(dir.absoluteFilePath(file), QSettings::IniFormat);
            desktop.beginGroup("Desktop Entry");
            if (desktop.value("NoDisplay").toString() == "true") continue;
            Application app;
            app.name = desktop.value("Name").toString();
            app.icon = desktop.value("Icon").toString();
            app.exec = desktop.value("Exec").toString();
            app.category = desktop.value("Categories").toString().split(";").first();
            if (!app.name.isEmpty()) m_apps.append(app);
            if (!app.category.isEmpty() && !m_categories.contains(app.category)) m_categories.append(app.category);
        }
    }
}
void ApplicationModel::launchApp(int index) {
    if (index >= 0 && index < m_filtered.size()) {
        QProcess::startDetached(m_filtered[index].exec);
    }
}
