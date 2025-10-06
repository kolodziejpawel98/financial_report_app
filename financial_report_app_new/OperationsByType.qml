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
            height: 15
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

    property int section_spacing: 57

        Text {
            id: text1
            x: 222
            y: 114
            width: 285
            height: 14
            text: qsTr("Eating out")
            font.pixelSize: 12
        }

        Rectangle {
            id: buttonContainer_operationsEatingOut_background
            x: 222
            y: 128
            width: 1006
            height: 42
            color: '#f4f4f4'
        }

        Flow {
            id: buttonContainer_operationsEatingOut
            spacing: 10
            x: 222
            y: 128
            width: 1006
            height: 42

            Repeater {
                model: backend.operationButtonList_operationsEatingOut.operationButtons
                delegate: operationButtonDelegate
            }
        }




        Text {
            id: buttonContainer_operationsNonGroceryShopping_title
            x: 222
            y: 114 + section_spacing
            width: 285
            height: 14
            text: qsTr("Non grocery shopping")
            font.pixelSize: 12
        }

        Rectangle {
            id: buttonContainer_operationsNonGroceryShopping_background
            x: 222
            y: 128 + section_spacing
            width: 1006
            height: 42
            color: '#f4f4f4'
        }

        Flow {
            id: buttonContainer_operationsNonGroceryShopping_container
            spacing: 10
            x: 222
            y: 128 + section_spacing
            width: 1006
            height: 42

            Repeater {
                model: backend.operationButtonList_operationsNonGroceryShopping.operationButtons
                delegate: operationButtonDelegate
            }
        }


        Text {
            id: buttonContainer_operationsGroceryShopping_title
            x: 222
            y: 114 + 2*section_spacing
            width: 285
            height: 14
            text: qsTr("Grocery shopping")
            font.pixelSize: 12
        }

        Rectangle {
            id: buttonContainer_operationsGroceryShopping_background
            x: 222
            y: 128 + 2*section_spacing
            width: 1006
            height: 42
            color: '#f4f4f4'
        }

        Flow {
            id: buttonContainer_operationsGroceryShopping_container
            spacing: 10
            x: 222
            y: 128 + 2*section_spacing
            width: 1006
            height: 42

            Repeater {
                model: backend.operationButtonList_operationsGroceryShopping.operationButtons
                delegate: operationButtonDelegate
            }
        }




        Text {
            id: buttonContainer_operationsTransportation_title
            x: 222
            y: 114 + 3*section_spacing
            width: 285
            height: 14
            text: qsTr("Transportation shopping")
            font.pixelSize: 12
        }

        Rectangle {
            id: buttonContainer_operationsTransportation_background
            x: 222
            y: 128 + 3*section_spacing
            width: 1006
            height: 42
            color: '#f4f4f4'
        }

        Flow {
            id: buttonContainer_operationsTransportation_container
            spacing: 10
            x: 222
            y: 128 + 3*section_spacing
            width: 1006
            height: 42

            Repeater {
                model: backend.operationButtonList_operationsTransportation.operationButtons
                delegate: operationButtonDelegate
            }
        }



        Text {
            id: buttonContainer_operationsRegularExpenses_title
            x: 222
            y: 114 + 4*section_spacing
            width: 285
            height: 14
            text: qsTr("RegularExpenses shopping")
            font.pixelSize: 12
        }

        Rectangle {
            id: buttonContainer_operationsRegularExpenses_background
            x: 222
            y: 128 + 4*section_spacing
            width: 1006
            height: 42
            color: '#f4f4f4'
        }

        Flow {
            id: buttonContainer_operationsRegularExpenses_container
            spacing: 10
            x: 222
            y: 128 + 4*section_spacing
            width: 1006
            height: 42

            Repeater {
                model: backend.operationButtonList_operationsRegularExpenses.operationButtons
                delegate: operationButtonDelegate
            }
        }


        Text {
            id: buttonContainer_operationsOtherExpenses_title
            x: 222
            y: 114 + 5*section_spacing
            width: 285
            height: 14
            text: qsTr("OtherExpenses shopping")
            font.pixelSize: 12
        }

        Rectangle {
            id: buttonContainer_operationsOtherExpenses_background
            x: 222
            y: 128 + 5*section_spacing
            width: 1006
            height: 42
            color: '#f4f4f4'
        }

        Flow {
            id: buttonContainer_operationsOtherExpenses_container
            spacing: 10
            x: 222
            y: 128 + 5*section_spacing
            width: 1006
            height: 42

            Repeater {
                model: backend.operationButtonList_operationsOtherExpenses.operationButtons
                delegate: operationButtonDelegate
            }
        }



        Text {
            id: buttonContainer_operationsPhotography_title
            x: 222
            y: 114 + 6*section_spacing
            width: 285
            height: 14
            text: qsTr("Photography shopping")
            font.pixelSize: 12
        }

        Rectangle {
            id: buttonContainer_operationsPhotography_background
            x: 222
            y: 128 + 6*section_spacing
            width: 1006
            height: 42
            color: '#f4f4f4'
        }

        Flow {
            id: buttonContainer_operationsPhotography_container
            spacing: 10
            x: 222
            y: 128 + 6*section_spacing
            width: 1006
            height: 42

            Repeater {
                model: backend.operationButtonList_operationsPhotography.operationButtons
                delegate: operationButtonDelegate
            }
        }



        Text {
            id: buttonContainer_operationsIncoming_title
            x: 222
            y: 114 + 7*section_spacing
            width: 285
            height: 14
            text: qsTr("Incoming shopping")
            font.pixelSize: 12
        }

        Rectangle {
            id: buttonContainer_operationsIncoming_background
            x: 222
            y: 128 + 7*section_spacing
            width: 1006
            height: 42
            color: '#f4f4f4'
        }

        Flow {
            id: buttonContainer_operationsIncoming_container
            spacing: 10
            x: 222
            y: 128 + 7*section_spacing
            width: 1006
            height: 42

            Repeater {
                model: backend.operationButtonList_operationsIncoming.operationButtons
                delegate: operationButtonDelegate
            }
        }



        Text {
            id: buttonContainer_operationsSummary_title
            x: 222
            y: 114 + 8*section_spacing
            width: 285
            height: 14
            text: qsTr("Summary shopping")
            font.pixelSize: 12
        }

        Rectangle {
            id: buttonContainer_operationsSummary_background
            x: 222
            y: 128 + 8*section_spacing
            width: 1006
            height: 42
            color: '#f4f4f4'
        }

        Flow {
            id: buttonContainer_operationsSummary_container
            spacing: 10
            x: 222
            y: 128 + 8*section_spacing
            width: 1006
            height: 42

            Repeater {
                model: backend.operationButtonList_operationsSummary.operationButtons
                delegate: operationButtonDelegate
            }
        }






    }
