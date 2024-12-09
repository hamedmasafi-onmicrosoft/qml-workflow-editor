import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import WorkFlowEditor

Block {
    Rectangle {
        anchors.fill: parent
        border.color: 'gray'
        radius: 15
    }

    Label {
        text: 'sample text'
        anchors.centerIn: parent
    }

    ColumnLayout {
        anchors{

            top: parent.top
            left: parent.left
            right: parent.right
            margins: 20
        }

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
            verticalCenter: parent.verticalCenter
            rightMargin: -15
        }
    }

    SimpleRelationHandle {
        type: RelationHandle.Input
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            leftMargin: -15
        }
    }
}
