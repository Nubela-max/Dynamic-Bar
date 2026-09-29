#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "configmanager.h"
#include "shellcontroller.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    app.setApplicationName("Dynamic Bar");
    app.setOrganizationName("DynamicBar");
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL, false);
    ConfigManager config;
    ShellController shell(&config);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("config", &config);
    engine.rootContext()->setContextProperty("shell", &shell);
    engine.loadFromModule("DynamicBar", "Main");
    if (engine.rootObjects().isEmpty()) return 1;
    return app.exec();
}
