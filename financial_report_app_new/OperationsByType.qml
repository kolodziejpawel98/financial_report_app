import QtQuick
import QtQuick.Controls 2.15

Rectangle {
    width: 1266
    height: 668

    Component.onCompleted: {
        backend.initOperationsByTypeScreen()
    }

    Rectangle {
        id: menu_sidebar
        x: 0
        y: 0
        width: 186
        height: parent.height
        color: "#353535"
        border.width: 0
    }

    Rectangle {
        id: menu_topbar
        x: 0
        y: 0
        width: parent.width
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

    Component {
        id: operationButtonDelegate
        Button {
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
                color: btn.hovered ? "#8a4abb" : "#9a5fc7"
                radius: 3
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: btn.clicked()

                onPositionChanged: {
                    operationDescriptionRectangle.x = mouse.x - 20
                    operationDescriptionRectangle.y = mouse.y - 60
                }
                onEntered: operationDescriptionRectangle.visible = true
                onExited: operationDescriptionRectangle.visible = false
            }

            onHoveredChanged: if (hovered) console.log("hover", text)
            onClicked: console.log("clicked", text)

            Rectangle {
                id: operationDescriptionRectangle
                visible: false
                width: textItem.implicitWidth + 120
                height: textItem.implicitHeight + 20
                color: "white"
                radius: 3
                border.color: "#c2c2c2"

                Text {
                    id: textItem
                    anchors.centerIn: parent
                    text: modelData.buttonDescriptionRectangleText
                    textFormat: Text.RichText
                    color: "black"
                    font.pixelSize: 14
                }
            }
        }
    }


    Rectangle {
        id: buttonContainer_operationsEatingOut_background
        x: 222
        y: 128
        width: 1006
        height: 58
        color: "#ededed"
    }

    Flow {
        id: buttonContainer_operationsEatingOut
        spacing: 10
        x: 222
        y: 128
        width: 1006
        height: 58

        Repeater {
            model: backend.operationButtonList_operationsEatingOut.operationButtons
            delegate: operationButtonDelegate
        }
    }


    Rectangle {
        id: buttonContainer_operationsNonGroceryShopping_background
        x: 222
        y: 206
        width: 1006
        height: 58
        color: "#ededed"
    }

    
    Flow {
        id: buttonContainer_operationsNonGroceryShopping
        spacing: 10
        x: 222
        y: buttonContainer_operationsEatingOut.y + buttonContainer_operationsEatingOut.height + 20
        width: 1006
        height: 58

        Repeater {
            model: backend.operationButtonList_operationsNonGroceryShopping.operationButtons
            delegate: operationButtonDelegate
        }
    }

    Text {
        id: text1
        x: 222
        y: 114
        width: 285
        height: 14
        text: qsTr("Eating out")
        font.pixelSize: 12
    }

    Text {
        id: text2
        x: 222
        y: 192
        width: 285
        height: 14
        text: qsTr("Non grocery shopping")
        font.pixelSize: 12
    }


}
