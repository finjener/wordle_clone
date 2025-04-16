import QtQuick 2.12
import QtQuick.Layouts 1.3

GridLayout {
    id: gridLayout
    columns: 5
    columnSpacing: gridItemSize * 0.2
    rowSpacing: gridItemSize * 0.2
    
    property real gridItemSize: 50
    property real responsiveWidth: 300
    
    width: responsiveWidth * 0.9
    
    Repeater {
        id: gridRepeater
        model: 30
        
        delegate: Loader {
            source: "GridItem.qml"
            onLoaded: {
                item.size = gridItemSize;
                item.itemIndex = index;
            }
        }
    }
    
    function updateGridItem(row, column, letter, color) {
        const index = row * 5 + column;
        if (index >= 0 && index < gridRepeater.count) {
            gridRepeater.itemAt(index).item.updateItem(letter, color);
        }
    }
    
    function resetGrid() {
        for (let i = 0; i < gridRepeater.count; i++) {
            gridRepeater.itemAt(i).item.updateItem("", "white");
        }
    }
} 