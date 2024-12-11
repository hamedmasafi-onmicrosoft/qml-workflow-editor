import QtQuick
import WorkFlowEditor

RelationHandle {
    width: 30
    height: 30

    Rectangle {
        width: 2
        height: 10

        color: 'gray'
        anchors.centerIn: parent
        visible: parent.state == RelationHandle.Connected
    }


    Rectangle {
        width: 2
        height: 10

        color: 'white'
        border.color: 'gray'
        anchors.centerIn: parent
        visible: parent.state == RelationHandle.UnConnected
    }
}
