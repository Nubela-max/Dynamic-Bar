import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    color: "transparent"
    anchors.fill: parent

    Column {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 16

        Text {
            text: "Control Center"
            color: "#e8edf5"
            font.pixelSize: 22
        }

        Row {
            spacing: 10
            PillButton { text: "Wi-Fi Connected"; icon: "⌁" }
            PillButton { text: "Bluetooth"; icon: "♢" }
            PillButton { text: "Do Not Disturb"; icon: "◐" }
        }

        Text { text: "Volume"; color: "#a9b6c8" }
        Slider {
            width: parent.width
            value: shell.volume / 100
            onMoved: shell.volume = value * 100
        }

        Text { text: "Brightness"; color: "#a9b6c8" }
        Slider { width: parent.width; value: 0.75 }
        Text { text: "Media  Nothing playing"; color: "#a9b6c8" }
    }
}
