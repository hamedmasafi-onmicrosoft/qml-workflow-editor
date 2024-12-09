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
        text: 'Output'
        anchors.centerIn: parent
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
