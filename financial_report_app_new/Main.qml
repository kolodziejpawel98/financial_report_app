import QtQuick
import QtQuick.Controls 2.15

ApplicationWindow {
    id: appWindow
    width: 1266
    height: 668
    visible: true
    title: qsTr("Financial report app")

    StackView {
        id: stackView
        anchors.fill: parent
        // initialItem: "LoadXmlScreen.qml"
        initialItem: "UndefinedOperationsMainContent.qml"

        pushEnter: Transition {}
        pushExit: Transition {}
        popEnter: Transition {}
        popExit: Transition {}

        // pushEnter: Transition {
        //     ParallelAnimation {
        //         NumberAnimation {
        //             property: "opacity"; from: 0; to: 1; duration: 300; easing.type: Easing.InOutQuad
        //         }
        //     }
        // }

        // pushExit: Transition {
        //     ParallelAnimation {
        //         NumberAnimation {
        //             property: "opacity"; from: 1; to: 0; duration: 300; easing.type: Easing.InOutQuad
        //         }
        //     }
        // }

        // popEnter: Transition {
        //     ParallelAnimation {
        //         NumberAnimation {
        //             property: "opacity"; from: 0; to: 1; duration: 300; easing.type: Easing.InOutQuad
        //         }
        //     }
        // }

        // popExit: Transition {
        //     ParallelAnimation {
        //         NumberAnimation {
        //             property: "opacity"; from: 1; to: 0; duration: 300; easing.type: Easing.InOutQuad
        //         }
        //     }
        // }
    }
}