import QtQuick
import QtQuick.Controls
Rectangle { color:"transparent";anchors.fill:parent
 Column{anchors.fill:parent;anchors.margins:24;spacing:14;Text{text:"Shell Settings";color:"#e8edf5";font.pixelSize:22};Text{text:"Profile";color:"#a9b6c8"};Row{spacing:8;Repeater{model:["default","minimal","gaming","performance","productivity"];delegate:PillButton{text:modelData;onClicked:config.profile=modelData}}};CheckBox{text:"Animated transitions";checked:config.value("animations",true);onToggled:config.setValue("animations",checked)};Text{text:"Accent color";color:"#a9b6c8"};TextField{width:220;text:config.value("accent","#8bd5ca");onEditingFinished:config.setValue("accent",text)};Text{text:"Settings persist in ~/.config/dynamic-bar/config.json";color:"#66758b";font.pixelSize:12}}
}
