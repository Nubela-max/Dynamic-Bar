#pragma once
#include <QObject>
#include <QStringList>
#include <QClipboard>
#include <QDateTime>
struct ClipboardEntry {
    QString text;
    QDateTime timestamp;
};
class ClipboardManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList history READ history NOTIFY historyChanged)
    Q_PROPERTY(int count READ count NOTIFY historyChanged)
public:
    explicit ClipboardManager(QObject *parent = nullptr);
    QStringList history() const;
    int count() const { return m_entries.size(); }
    Q_INVOKABLE void clear();
    Q_INVOKABLE void deleteEntry(int index);
    Q_INVOKABLE QString getEntry(int index) const;
    Q_INVOKABLE void pasteEntry(int index);
signals:
    void historyChanged();
private slots:
    void onClipboardChanged();
private:
    QList<ClipboardEntry> m_entries;
    QClipboard *m_clipboard = nullptr;
    QString m_lastText;
};
