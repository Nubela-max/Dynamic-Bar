import QtQuick

Rectangle {
    id: root
    property string label: ""
    property string value: ""

    implicitWidth: 94
    implicitHeight: 48
    radius: 14
    color: "#202c3d"

    Column {
        anchors.centerIn: parent
        spacing: 2

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.label
            color: "#8593a8"
            font.pixelSize: 11
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.value
            color: "#e8edf5"
            font.pixelSize: 14
        }
    }
}
