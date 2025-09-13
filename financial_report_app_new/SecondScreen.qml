import QtQuick
import QtQuick.Controls 2.15

Rectangle {
    width: 1266
    height: 668
    color: "#a0d3f5"

    signal requestPop()

    Button {
        anchors.centerIn: parent
        width: 200
        height: 50
        text: "go back"
        onClicked: requestPop()
    }
}
