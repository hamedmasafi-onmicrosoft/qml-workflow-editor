import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import WorkFlowEditor

Block {
    id: block
    title: "Simple"

    padding: 20
    // height: implicitHeight

    header :BlockHeader {
        title: "Simple" + block.height
    }

    background: Rectangle {
        anchors.fill: parent
        border.color: 'gray'
        radius: 15
    }

    contentItem: ColumnLayout {
        Label {
            text: qsTr("Provider")
        }
        ComboBox {
            model: [qsTr("Chat GPT")]
            Layout.fillWidth: true
        }
    }

    SimpleRelationHandle {
        type: RelationHandle.Output

        anchors {
            right: parent.right
            rightMargin: -15
            top: parent.top
            topMargin: 25
        }
    }

    SimpleRelationHandle {
        type: RelationHandle.Input
        anchors {
            left: parent.left
            leftMargin: -15
            top: parent.top
            topMargin: 25
        }
    }
}
