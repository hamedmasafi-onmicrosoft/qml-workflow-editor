import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import WorkFlowEditor

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Component {
        id: blockComponent
        SampleBlock { }
    }
    Component {
        id: inputDataBlockComponent
        InputDataBlock { }
    }
    Component {
        id: outputBlockComponent
        OutputBlock { }
    }

    Component.onCompleted: {
        var input = area.addBlock(inputDataBlockComponent, {x: 50, y: 30, width: 160})
        var middle = area.addBlock(blockComponent, {x: 350, y: 30, width: 160, height: 100})
        var output = area.addBlock(outputBlockComponent, {x: 650, y: 30, width: 160, height: 100})

        area.addRelation(input, middle)
        area.addRelation(middle, output)
    }

    header: ToolBar {
        RowLayout {
            Button {
                text: "Add block"
                onClicked: area.addBlock(blockComponent, {x: 50, y: 30, width: 160, height: 100})
            }
            ToolSeparator {}

            Button {
                text: "Select tool"
                checked: area.selectedTool == WorkFlowEditorArea.Select
                onClicked: area.selectedTool = WorkFlowEditorArea.Select
            }
            Button {
                text: "Relation tool"
                checked: area.selectedTool == WorkFlowEditorArea.Relation
                onClicked: area.selectedTool = WorkFlowEditorArea.Relation
            }
        }        
    }

    WorkFlowEditorArea {
        id: area
        anchors.fill: parent

        relationComponent: SimpleRelation {
            onAddClicked: {
                console.log("Add clicked")
                area.addMiddleBlock(blockComponent, this, {width: 200, height: 200});
            }
        }
        highlightComponent: Rectangle {
            color: 'yellow'
            border.color: 'blue'
        }
    }

}
