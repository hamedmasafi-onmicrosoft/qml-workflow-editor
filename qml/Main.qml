import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import WorkFlowEditor
import Qt.labs.qmlmodels

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

    Component {
        id: chatInputBlockComponent
        ChatInputBlock { }
    }

    Component.onCompleted: {
        // var input = area.addBlock(chatInputBlockComponent, {x: 50, y: 30, width: 160})
        // var middle = area.addBlock(blockComponent, {x: 350, y: 30, width: 160, height: 100})
        // var output = area.addBlock(outputBlockComponent, {x: 650, y: 30, width: 160, height: 100})

        // area.addRelation(input, middle)
        // area.addRelation(middle, output)
    }

    ListModel {
        id: blocksModel

        ListElement {
            title: "Note"
            uri: "blocks/NoteBlock.qml"
            icon: 'qrc:/res/icons/note.svg'
        }

        ListElement {
            title: "Astra DB"
            uri: "blocks/AstraDBBlock.qml"
            icon: 'qrc:/res/icons/ds.svg'
        }

        ListElement {
            title: "Chat input"
            uri: "blocks/ChatInputBlock.qml"
            icon: 'qrc:/res/icons/chat.svg'
        }

        ListElement {
            title: "Parse data"
            uri: "blocks/ParseDataBlock.qml"
            icon: 'qrc:/res/icons/code.svg'
        }

        ListElement {
            title: "Prompt"
            uri: "blocks/PromptBlock.qml"
            icon: 'qrc:/res/icons/prompt.svg'
        }

        ListElement {
            title: "Chat output"
            uri: "blocks/ChatOutputBlock.qml"
            icon: 'qrc:/res/icons/chat.svg'
        }
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

    Item {
        id: root
        anchors.fill: parent

        SplitView {
            id: splitview
            property bool dragging: false
            property string currentUri

            anchors.fill: parent

            Rectangle {
                SplitView.fillHeight: true
                SplitView.preferredWidth: 200

                ListView {
                    anchors.fill: parent
                    model: blocksModel

                    delegate: ItemDelegate {
                        width: ListView.view.width

                        display: AbstractButton.TextBesideIcon
                        icon.source: model.icon
                        text: model.title
                        property string uri

                        MouseArea {
                            anchors.fill: parent
                            drag.target: dragItem

                            // Drag Item (Visual Representation during Drag)


                            // When drag starts
                            onPressed: {
                                var p = parent.mapToItem(root, Qt.point(0, 0))
                                dragItem.x = p.x
                                dragItem.y = p.y
                                dragItem.width = parent.width
                                dragItem.height = parent.height
                                splitview.currentUri = model.uri
                                splitview.dragging = true
                                dragItem.visible = true
                                dragItem.Drag.start()
                            }

                            // When drag ends
                            onReleased: {
                                splitview.dragging = false
                                dragItem.Drag.drop()
                                dragItem.visible = false
                            }
                        }
                    }
                }
            }

            WorkFlowEditorArea {
                id: area
                clip: true
                SplitView.fillWidth: true
                SplitView.fillHeight: true
                gridSize: 25
                backgroundColor: '#F4F4F5'

                relationComponent: SimpleRelation {
                    onAddClicked: {
                        console.log("Add clicked")
                        area.addMiddleBlock(blockComponent, this, {width: 200, height: 200});
                    }
                }
                highlightComponent: Rectangle {
                    color: 'transparent'
                    border.color: 'blue'
                    radius: width / 2
                }

                // Rectangle {
                //     anchors.fill: parent
                // }

                DropArea {
                    anchors.fill: parent
                    visible: splitview.dragging
                    onDropped: (drop) => {
                                   console.log("Creating", splitview.currentUri, drop.x, drag.x)
                                   var component = Qt.createComponent(splitview.currentUri)
                                   var pos = dragItem.mapToItem(area, Qt.point(0, 0))
                                   const props = {
                                       x: pos.x,
                                       y: pos.y
                                   }
                                   if (component.status === Component.Ready) {
                                       area.addBlock(component, props);
                                   } else if (component.status === Component.Error) {
                                       console.error("Component error:", component.errorString())
                                   } else {
                                       component.statusChanged.connect(function() {
                                           if (component.status === Component.Ready) {
                                               area.addBlock(component, props);
                                           }
                                       })
                                   }
                                   drop.accept()
                               }
                }


            }



        }
        Rectangle {
            id: dragItem
            width: parent.width
            height: 50
            color: "blue"
            opacity: 0.5
            visible: false
            z: 99

            // Drag.active: drag.active
            Drag.source: parent.uri
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2
        }
    }
}
