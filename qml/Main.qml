import QtQuick
import QtQuick.Controls
import DynamicBar
ApplicationWindow { id: window; visible:true; width:620; height:96; x:(Screen.width-width)/2; y:18; color:"transparent"; flags:Qt.FramelessWindowHint|Qt.WindowStaysOnTopHint|Qt.Tool
 property color surface:"#101824"; property color accent:config.value("accent","#8bd5ca")
 Rectangle { id:pill; anchors.centerIn:parent;width: shell.expanded ? 590 : 500;height:shell.expanded ? 470 : 68;radius:34;color:surface;opacity:config.value("opacity",.96);border.color:"#2c3b50";border.width:1;Behavior on width{NumberAnimation{duration:180}};Behavior on height{NumberAnimation{duration:180}}
 Row { id:bar; visible:!shell.expanded;anchors.centerIn:parent;spacing:8; ModuleChip{label:"Battery";value:shell.battery+"%"};ModuleChip{label:"Volume";value:shell.muted?"Muted":shell.volume+"%"};ModuleChip{label:"Network";value:shell.network};ModuleChip{label:"Clock";value:shell.clock};PillButton{icon:"⌄";text:"Menu";onClicked:shell.setExpanded(true)} }
 Loader{id:content;anchors.fill:parent;anchors.margins:8;active:shell.expanded;source:shell.activePanel==="launcher"?"panels/Launcher.qml":shell.activePanel==="control"?"panels/ControlCenter.qml":shell.activePanel==="clipboard"?"panels/Clipboard.qml":shell.activePanel==="settings"?"panels/Settings.qml":"panels/ControlCenter.qml"}
 Row{visible:shell.expanded;anchors.bottom:parent.bottom;anchors.horizontalCenter:parent.horizontalCenter;anchors.bottomMargin:10;spacing:6;PillButton{text:"Launcher";onClicked:shell.openPanel("launcher")};PillButton{text:"Clipboard";onClicked:shell.openPanel("clipboard")};PillButton{text:"Controls";onClicked:shell.openPanel("control")};PillButton{text:"Settings";onClicked:shell.openPanel("settings")};PillButton{text:"Close";onClicked:shell.closePanel()} }
 }
 Shortcut{sequence:"Ctrl+1";onActivated:shell.openPanel("launcher")};Shortcut{sequence:"Ctrl+2";onActivated:shell.openPanel("clipboard")};Shortcut{sequence:"Escape";onActivated:shell.closePanel()};Shortcut{sequence:"Ctrl+3";onActivated:shell.openPanel("control")};Shortcut{sequence:"Ctrl+4";onActivated:shell.openPanel("settings")}
 Connections{target:shell;function onToast(message){toast.text=message;toast.visible=true;hide.start()}}
 Text{id:toast;visible:false;anchors.top:parent.bottom;anchors.horizontalCenter:parent.horizontalCenter;anchors.topMargin:8;color:"white";Timer{id:hide;interval:1800;onTriggered:toast.visible=false}}
}
