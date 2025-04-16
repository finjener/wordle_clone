import QtQuick 2.12

Rectangle {
    id: gridItem
    width: size
    height: size
    color: "white"
    border.color: "black"
    border.width: 2
    radius: 5
    
    property real size: 50
    property real fontSize: size * 0.48
    property int itemIndex: 0
    
    Text {
        id: letterText
        text: ""
        anchors.centerIn: parent
        font.pixelSize: fontSize
    }
    
    function updateItem(letter, color) {
        letterText.text = letter;
        gridItem.color = color;
    }
} 