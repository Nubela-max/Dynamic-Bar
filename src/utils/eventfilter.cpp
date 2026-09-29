#include "eventfilter.h"
#include <QGuiApplication>
EventFilter::EventFilter(QObject *parent) : QObject(parent) {
    qApp->installNativeEventFilter(this);
}
bool EventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result) {
    return false;
}
void EventFilter::registerHotkeys() {
}
