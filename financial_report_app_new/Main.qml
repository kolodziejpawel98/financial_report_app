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
        initialItem: "LoadXmlScreen.qml"
    }
}
