import QtQuick
import WorkFlowEditor

RelationHandle {
    width: 30
    height: 30

    // Rectangle {
    //     anchors.fill: parent
    //     color: 'red'
    // }

    Rectangle {
        width: 2
        height: 10

        color: 'gray'
        anchors.centerIn: parent
        visible: parent.state == RelationHandle.Connected
    }
}
