import QtQuick
import QtQuick.Controls 2.15

Window {
    width: 1266
    height: 668
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        id: rectangle
        x: 53
        y: 43
        width: 919
        height: 303
        color: "#fbe18f"
        radius: 9
    }

Button {
    id: button
    x: 475
    y: 407
    width: 515
    height: 162
    text: "Hover me bro"
    font.bold: true
    font.pointSize: 14
    hoverEnabled: true
    onClicked: backend.printTestString()

    background: Rectangle {
        id: bg
        radius: 8
        color: button.containsMouse ? "darkred" : "red"
        Behavior on color { ColorAnimation { duration: 200 } }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onClicked: {
                backend.printTestString()
            }
        }
    }
}

}
