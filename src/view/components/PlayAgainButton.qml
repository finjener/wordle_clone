import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
    id: buttonContainer
    width: buttonWidth
    height: buttonHeight
    color: "transparent"
    visible: isVisible
    
    property real buttonWidth: 150
    property real buttonHeight: 50
    property real buttonFontSize: 16
    property bool isVisible: false
    signal playAgainClicked()
    
    Button {
        id: restartGameButton
        text: "Play Again"
        anchors.fill: parent
        
        background: Rectangle {
            color: "#2e7d32"
            radius: 8
            border.width: 2
            border.color: "#1b5e20"
        }
        
        contentItem: Text {
            text: restartGameButton.text
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: buttonFontSize
            font.bold: true
        }
        
        onClicked: {
            playAgainClicked()
        }
    }
} 