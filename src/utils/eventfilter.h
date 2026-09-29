#pragma once
#include <QObject>
#include <QAbstractNativeEventFilter>
class EventFilter : public QObject, public QAbstractNativeEventFilter {
    Q_OBJECT
public:
    explicit EventFilter(QObject *parent = nullptr);
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;
signals:
    void hotkeyPressed(const QString &action);
private:
    void registerHotkeys();
};
