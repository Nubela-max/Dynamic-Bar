import QtQuick
import QtQuick.Controls
Rectangle {
    id: notif
    property string appName: ""
    property string title: ""
    property string body: ""
    signal dismissed()
    width: 340
    height: Math.max(bodyText.implicitHeight + 24, 60)
    radius: 12
    color: "#202c3d"
    border.color: "#3b4d66"
    border.width: 1
    Column {
        anchors { fill: parent; margins: 12 }
        spacing: 4
        Text {
            text: appName
            color: "#8bd5ca"
            font.pixelSize: 12
        }
        Text {
            text: title
            color: "#e8edf5"
            font.pixelSize: 14
            font.bold: true
        }
        Text {
            id: bodyText
            text: body
            color: "#a9b6c8"
            font.pixelSize: 12
            wrapMode: Text.Wrap
            width: parent.width
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: dismissed()
    }
    Timer {
        running: true
        interval: 5000
        onTriggered: dismissed()
    }
}
