import QtQuick
import QtQuick.Controls
import WorkFlowEditor

Block {
    background: Rectangle {
        border.color: 'gray'
        radius: 15
    }

    contentItem:    Label {
        text: 'Output'
        verticalAlignment: Label.AlignVCenter
        horizontalAlignment: Label.AlignHCenter
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
