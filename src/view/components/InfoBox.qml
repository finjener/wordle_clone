import QtQuick 2.12

Rectangle {
    id: infoBox
    width: parent.width * 0.8
    height: parent.height * 0.08
    color: "#333333"
    visible: message.length > 0
    radius: 5
    
    property string message: ""
    property real messageFontSize: 14
    
    Text {
        text: message
        anchors.centerIn: parent
        color: "white"
        font.pixelSize: messageFontSize
        wrapMode: Text.WordWrap
        width: parent.width - 20
        horizontalAlignment: Text.AlignHCenter
    }
} 