import QtQuick
import QtQuick.Controls
Rectangle { color:"transparent";anchors.fill:parent
 Column{anchors.fill:parent;anchors.margins:24;spacing:14;Text{text:"Clipboard History";color:"#e8edf5";font.pixelSize:22};TextField{width:parent.width;placeholderText:"Search clipboard…"};Repeater{model:["No clipboard entries yet","Clipboard integration is ready for the next backend"];delegate:Rectangle{width:parent.width;height:48;color:"#202c3d";radius:10;Text{anchors.centerIn:parent;text:modelData;color:"#a9b6c8"}}}}
}
