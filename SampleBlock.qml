import QtQuick
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

    RelationHandle {
        width: 30
        height: 30

        type: RelationHandle.Output

        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
            rightMargin: -15
        }

        Rectangle {
            anchors.fill: parent
            color: 'red'
        }
    }

    RelationHandle {
        width: 30
        height: 30

        type: RelationHandle.Input
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            leftMargin: -15
        }

        Rectangle {
            anchors.fill: parent
            color: 'red'
        }
    }
}
