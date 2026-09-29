#include "clipboardmanager.h"
#include <QApplication>
#include <QGuiApplication>
ClipboardManager::ClipboardManager(QObject *parent) : QObject(parent) {
    m_clipboard = QGuiApplication::clipboard();
    connect(m_clipboard, &QClipboard::changed, this, &ClipboardManager::onClipboardChanged);
    onClipboardChanged();
}
void ClipboardManager::onClipboardChanged() {
    QString text = m_clipboard->text();
    if (!text.isEmpty() && text != m_lastText) {
        m_lastText = text;
        m_entries.prepend({text, QDateTime::currentDateTime()});
        if (m_entries.size() > 50) m_entries.removeLast();
        emit historyChanged();
    }
}
QStringList ClipboardManager::history() const {
    QStringList result;
    for (const auto &entry : m_entries) {
        QString preview = entry.text.length() > 50 ? entry.text.left(47) + "..." : entry.text;
        result << preview.replace("\n", " ");
    }
    return result;
}
void ClipboardManager::clear() {
    m_entries.clear();
    m_lastText.clear();
    emit historyChanged();
}
void ClipboardManager::deleteEntry(int index) {
    if (index >= 0 && index < m_entries.size()) {
        m_entries.removeAt(index);
        emit historyChanged();
    }
}
QString ClipboardManager::getEntry(int index) const {
    if (index >= 0 && index < m_entries.size()) return m_entries[index].text;
    return "";
}
void ClipboardManager::pasteEntry(int index) {
    QString text = getEntry(index);
    if (!text.isEmpty()) {
        m_clipboard->setText(text);
    }
}
