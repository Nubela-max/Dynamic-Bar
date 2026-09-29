import QtQuick
import QtQuick.Controls
Rectangle {
    color: "transparent"
    anchors.fill: parent
    Column {
        anchors { fill: parent; margins: 24 }
        spacing: 16
        Text {
            text: "Power Menu"
            color: "#e8edf5"
            font.pixelSize: 22
        }
        Column {
            spacing: 8
            width: parent.width
            PillButton { text: "🔒 Lock"; onClicked: shell.powerAction("lock") }
            PillButton { text: "😴 Sleep"; onClicked: shell.powerAction("sleep") }
            PillButton { text: "🚪 Logout"; onClicked: shell.powerAction("logout") }
            PillButton { text: "♻️  Reboot"; onClicked: shell.powerAction("reboot") }
            PillButton { text: "⏻  Shutdown"; onClicked: shell.powerAction("shutdown") }
        }
    }
}
