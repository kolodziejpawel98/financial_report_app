import QtQuick
import QtQuick.Controls 2.15

Rectangle {
    width: 1266
    height: 668

    Component.onCompleted: {
        backend.initOperationsByType()
    }

    Rectangle {
        id: menu_sidebar
        x: 0
        y: 0
        width: 186
        height: 668
        color: "#353535"
        border.width: 0
    }

    Rectangle {
        id: menu_topbar
        x: 0
        y: 0
        width: 1266
        height: 80
        color: "#292929"

        Text {
            id: menu_appName
            x: 28
            y: 27
            width: 265
            height: 26
            color: "#ffffff"
            text: qsTr("Financial report app")
            font.pixelSize: 21
            font.weight: Font.Medium
        }
    }

    Flow {
        id: buttonContainer
        spacing: 10
        x: 222
        y: 128
        width: 1006
        height: 58

        Repeater {
            model: backend.operationButtonList.operationButtons

            delegate: Button {
                id: btn
                text: modelData.buttonText
                width: modelData.buttonWidth
                height: 20
                font.pixelSize: 10
                hoverEnabled: true

                contentItem: Text {
                    text: btn.text
                    font: btn.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    implicitWidth: 120
                    implicitHeight: 40
                    color: btn.hovered ? '#8a4abb' : '#9a5fc7'
                    radius: 3
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: btn.clicked()

                    onPositionChanged: {
                        tooltip.x = mouse.x + 20
                        tooltip.y = mouse.y - 10
                    }
                    onEntered: tooltip.visible = true
                    onExited: tooltip.visible = false

                }

                onHoveredChanged: {
                    if (hovered)
                    {
                        console.log("hover", text)
                    }
                }

                onClicked: {
                    console.log("clicked", text)
                }


                Rectangle {
                    id: tooltip
                    visible: false
                    width: textItem.implicitWidth + 20
                    height: textItem.implicitHeight + 10
                    color: "white"
                    radius: 6
                    border.color: "#888"

                    Text {
                        id: textItem
                        anchors.centerIn: parent
                        text: "To jest tooltip"
                        color: "black"
                        font.pixelSize: 14
                    }
                }


            }
        }
    }
}
