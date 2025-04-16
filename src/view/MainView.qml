import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import Wordle 1.0
import "components"

ApplicationWindow {
    id: appWindow
    title: "Wordle Game"
    visible: true
    width: 380
    height: 600
    minimumWidth: 300
    minimumHeight: 500

    property real responsiveWidth: Math.min(appWindow.width, appWindow.height * 0.7)
    property real gridItemSize: Math.min(50, responsiveWidth / 6)
    property real fontSize: gridItemSize * 0.48
    property real buttonFontSize: fontSize * 0.9
    property real messageFontSize: fontSize * 0.7

    GameController {
        id: gameController
    }

    FocusScope {
        anchors.fill: parent
        focus: true

        Header {
            id: header
            anchors.top: parent.top
            fontSize: appWindow.fontSize * 1.5
        }

        Item {
            id: contentArea
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: appWindow.width * 0.02

            GameGrid {
                id: gameGrid
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: appWindow.height * 0.05
                
                gridItemSize: appWindow.gridItemSize
                responsiveWidth: appWindow.responsiveWidth
            }

            InfoBox {
                id: infoBox
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: gameGrid.bottom
                anchors.topMargin: appWindow.height * 0.02
                
                message: gameController.gameModel.message
                messageFontSize: appWindow.messageFontSize
            }

            PlayAgainButton {
                id: playAgainButton
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: infoBox.bottom
                anchors.topMargin: appWindow.height * 0.03
                
                buttonWidth: responsiveWidth * 0.4
                buttonHeight: appWindow.height * 0.08
                buttonFontSize: appWindow.buttonFontSize
                isVisible: gameController.gameModel.gameOver
                
                onPlayAgainClicked: {
                    gameController.newGame()
                }
            }
        }

        Keys.onPressed: function(event) {
            if (!gameController.gameModel.gameOver) {
                if (event.key >= Qt.Key_A && event.key <= Qt.Key_Z) {
                    gameController.addLetter(event.text.toUpperCase());
                } else if (event.key === Qt.Key_Backspace) {
                    gameController.deleteLetter();
                } else if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                    gameController.submitGuess();
                    updateGameGrid();
                }
                event.accepted = true;
            }
        }
    }

    Connections {
        target: gameController.gameModel
        
        function onAttemptsChanged() {
            updateGameGrid();
        }
        
        function onGameOverChanged() {
            updateGameGrid();
        }
        
        function onCurrentRowChanged() {
            updateGameGrid();
        }
    }
    
    function updateGameGrid() {
        var attempts = gameController.gameModel.attempts;
        
        for (var row = 0; row < attempts.length; row++) {
            var attempt = attempts[row];
            
            if (attempt.length === 5) {
                if (row < gameController.gameModel.currentRow || gameController.gameModel.gameOver) {
                    var evaluation = gameController.evaluateAttempt(attempt);
                    
                    for (var i = 0; i < 5; i++) {
                        var letter = attempt[i];
                        var color = getColorForEvaluation(evaluation[i], letter);
                        gameGrid.updateGridItem(row, i, letter, color);
                    }
                } else {
                    for (var j = 0; j < 5; j++) {
                        gameGrid.updateGridItem(row, j, attempt[j], "white");
                    }
                }
            } else {
                for (var k = 0; k < attempt.length; k++) {
                    gameGrid.updateGridItem(row, k, attempt[k], "white");
                }
                for (var l = attempt.length; l < 5; l++) {
                    gameGrid.updateGridItem(row, l, "", "white");
                }
            }
        }
        
        for (var emptyRow = attempts.length; emptyRow < 6; emptyRow++) {
            for (var emptyCol = 0; emptyCol < 5; emptyCol++) {
                gameGrid.updateGridItem(emptyRow, emptyCol, "", "white");
            }
        }
    }
    
    function getColorForEvaluation(code, letter) {
        if (code === '2') {
            return "green";  // Correct letter, correct position
        } else if (code === '1') {
            return "yellow"; // Correct letter, wrong position
        } else {
            return "grey";   // Letter not in word
        }
    }
    
    Component.onCompleted: {
        updateGameGrid();
    }
} 