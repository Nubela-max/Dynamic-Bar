import QtQuick
import QtQuick.Controls

Rectangle {
    color: "transparent"
    anchors.fill: parent

    Column {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 16

        Text {
            text: "Launch application"
            color: "#e8edf5"
            font.pixelSize: 22
        }

        TextField {
            id: search
            width: parent.width
            focus: true
            placeholderText: "Search apps…"
            onAccepted: shell.showToast("Launcher", text)
        }

        Text { text: "Favorites"; color: "#8bd5ca"; font.bold: true }

        Row {
            spacing: 10
            Repeater {
                model: ["Firefox", "Dolphin", "Konsole", "Code"]
                delegate: PillButton {
                    text: modelData
                    icon: "●"
                    onClicked: shell.showToast("Launcher", text + " requested")
                }
            }
        }
    }
}
