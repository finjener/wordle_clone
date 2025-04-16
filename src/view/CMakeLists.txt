set(VIEW_QML_FILES
    MainView.qml
    components/Header.qml
    components/GridItem.qml
    components/GameGrid.qml
    components/InfoBox.qml
    components/PlayAgainButton.qml
)

add_custom_target(view_qml_files SOURCES ${VIEW_QML_FILES}) 