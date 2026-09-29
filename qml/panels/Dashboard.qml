import QtQuick
import QtQuick.Controls
Rectangle {
    color: "transparent"
    anchors.fill: parent
    Column {
        anchors { fill: parent; margins: 24 }
        spacing: 18
        Text {
            text: "Dashboard"
            color: "#e8edf5"
            font.pixelSize: 22
        }
        Grid {
            columns: 3
            spacing: 12
            width: parent.width
            PillButton { text: "Battery: " + shell.battery + "%"; icon: "🔋" }
            PillButton { text: "Volume: " + shell.volume + "%"; icon: "🔊" }
            PillButton { text: "Network: " + shell.network; icon: "📡" }
            PillButton { text: "Time: " + shell.clock; icon: "⏰" }
            PillButton { text: "Uptime: N/A"; icon: "⏱" }
            PillButton { text: "Users: 1"; icon: "👤" }
        }
    }
}
