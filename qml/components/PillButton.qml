import QtQuick
import QtQuick.Controls
Rectangle { id: root; property string text: ""; property string icon: ""; signal clicked(); implicitWidth: row.implicitWidth+24; implicitHeight: 38; radius: 19; color: mouse.containsMouse ? Qt.lighter("#273449",1.2) : "#273449"; border.color: "#3b4d66"
 Row { id: row; anchors.centerIn: parent; spacing: 7; Text { text: root.icon; color: "#8bd5ca"; font.pixelSize: 16 } Text { text: root.text; color: "#e8edf5"; font.pixelSize: 13 } }
 MouseArea { id: mouse; anchors.fill: parent; hoverEnabled: true; onClicked: root.clicked() }
}
