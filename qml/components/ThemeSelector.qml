import QtQuick
import QtQuick.Controls
Rectangle {
    id: root
    color: "transparent"
    Column {
        anchors { fill: parent; margins: 16 }
        spacing: 12
        Text {
            text: "Select Theme"
            color: "#e8edf5"
            font.pixelSize: 18
            font.bold: true
        }
        Flow {
            width: parent.width
            spacing: 10
            Repeater {
                model: ["Midnight", "Twilight", "Dracula", "Nord"]
                delegate: Rectangle {
                    width: 100
                    height: 100
                    radius: 8
                    border.color: modelData === "Midnight" ? "#8bd5ca" : "#3b4d66"
                    border.width: 2
                    color: modelData === "Midnight" ? "#101824" : "#202c3d"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: shell.notify("Theme", modelData + " selected")
                    }
                    Text {
                        anchors.centerIn: parent
                        text: modelData
                        color: "#e8edf5"
                        font.pixelSize: 11
                    }
                }
            }
        }
    }
}
