import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.12
import Wordle 1.0

ApplicationWindow {
    title: "Wordle Game"
    visible: true
    width: 380
    height: 560

    WordleBackend {
        id: wordleBackend
    }

    // Capture key events
    FocusScope {
        anchors.fill: parent
        focus: true

        GridLayout {
            id: gridLayout
            columns: 5
            columnSpacing: 10
            anchors.centerIn: parent

            Repeater {
                model: 30 // 6 rows x 5
                Rectangle {
                    id: gridItem
                    width: 50
                    height: 50
                    color: "white"
                    border.color: "black"
                    border.width: 2
                    radius: 5

                    Text {
                        id: letterText
                        text: ""
                        anchors.centerIn: parent
                        font.pixelSize: 24
                    }

                    Connections {
                        target: wordleBackend
                        onInvalidWord: {
                                //console.log("This is not a valid word.");
                            }

                        onUpdateGrid: {
                            if (index === row * 5 + column) {
                                letterText.text = letter;
                                gridItem.color = color;
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
                id: infoBox
                width: parent.width * 0.8
                height: 50
                color: "#333333"
                visible: wordleBackend.message.length > 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: gridLayout.bottom
                anchors.topMargin: 10

                Text {
                    text: wordleBackend.message
                    anchors.centerIn: parent
                    color: "white"
                }
            }

//        Button {
//                id: restartGameButton
//                text: "Play Again"
//                visible: wordleBackend.gameOver
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 20
//                onClicked: wordleBackend.restartGame()

//            }

        // Get key presses when the FocusScope is focused
        Keys.onPressed: {
            if (!wordleBackend.gameOver) {
                if (event.key >= Qt.Key_A && event.key <= Qt.Key_Z) {
                    wordleBackend.inputLetter(event.text.toUpperCase());
                } else if (event.key === Qt.Key_Backspace) {
                    wordleBackend.deleteLastLetter();
                } else if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                    wordleBackend.checkWord();
                }
                // Close Event
                event.accepted = true;
            }
        }
    }
    //update ui
    Connections {
        target: wordleBackend
        onCurrentAttemptChanged: {
            for (let i = 0; i < wordleBackend.currentAttempt.length; i++) {
                let letter = wordleBackend.currentAttempt[i];
                let itemIndex = i + wordleBackend.currentRow * 5;
            }
        }
    }
}
