import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import WorkFlowEditor

Block {
    implicitHeight: mainLayout.implicitHeight + 40

    background: BlockBackground {    }

    contentItem: ColumnLayout {
        id: mainLayout
        // anchors{

        //     top: parent.top
        //     left: parent.left
        //     right: parent.right
        //     margins: 20
        // }
        Label {
            text: 'Input'
            font.pixelSize: 20
        }

        Label {
            text: qsTr("Input name")
            Layout.fillWidth: true
        }

        TextField {
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
}
