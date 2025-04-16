import QtQuick 2.12

Rectangle {
    id: headerRect
    width: parent.width
    height: parent.height * 0.1
    color: "#121213"
    
    property real fontSize: 24
    
    Text {
        text: "WORDLE"
        color: "white"
        font.pixelSize: fontSize
        font.bold: true
        anchors.centerIn: parent
    }
} 