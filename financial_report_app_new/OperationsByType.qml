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
            hoverEnabled: true

            width: contentItem.implicitWidth
            height: contentItem.implicitHeight

            padding: 0
            contentItem: Text {
                id: textItemButton
                text: btn.text
                // font.pixelSize: btn.hovered ? 11 : 10
                font.bold: btn.hovered
                color: btn.hovered ? '#aa74d2' : "#000000"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                Behavior on font.pixelSize {
                    NumberAnimation { duration: 120; easing.type: Easing.OutQuad }
                }
            }

            background: Rectangle {
                color: btn.hovered ? '#f8efff' : "#ffffff"
                radius: 3
                width: btn.width
                height: btn.height
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

            Rectangle {
                id: operationDescriptionRectangle
                visible: false
                width: textDescription.implicitWidth + 120
                height: textDescription.implicitHeight + 20
                color: "white"
                radius: 3
                border.color: "#c2c2c2"

                Text {
                    id: textDescription
                    anchors.centerIn: parent
                    text: modelData.buttonDescriptionRectangleText
                    textFormat: Text.RichText
                    color: "black"
                    font.pixelSize: 12
                }
            }
        }
    }



    property int section_spacing: 15

    Text {
        id: text1
        x: 225
        y: 108
        // width: 285
        // height: 14
        text: qsTr("Eating out")
        font.pixelSize: 14
        font.styleName: "Bold"
    }

    Rectangle {
        id: buttonContainer_operationsEatingOut_background
        x: 222
        y: 128
        width: 1006
        height: 42
        // color: '#f4f4f4'
    }

    Flow {
        id: buttonContainer_operationsEatingOut
        spacing: 5
        x: buttonContainer_operationsEatingOut_background.x
        y: buttonContainer_operationsEatingOut_background.y
        width: 1006
        height: 42

        Repeater {
            model: backend.operationButtonList_operationsEatingOut.operationButtons
            delegate: operationButtonDelegate
        }
    }




    Text {
        id: buttonContainer_operationsNonGroceryShopping_title
        x: text1.x
        y: text1.y + buttonContainer_operationsEatingOut_background.height + section_spacing
        // width: 285
        // height: 14
        text: qsTr("Non grocery shopping")
        font.pixelSize: text1.font.pixelSize
        font.styleName: "Bold"
    }

    Rectangle {
        id: buttonContainer_operationsNonGroceryShopping_background
        x: 222
        y: buttonContainer_operationsEatingOut_background.y + buttonContainer_operationsEatingOut_background.height + section_spacing
        width: 1006
        height: 42
        // color: '#f4f4f4'
    }

    Flow {
        id: buttonContainer_operationsNonGroceryShopping_container
        spacing: buttonContainer_operationsEatingOut.spacing
        x: 222
        y: buttonContainer_operationsNonGroceryShopping_background.y
        width: 1006
        height: 42

        Repeater {
            model: backend.operationButtonList_operationsNonGroceryShopping.operationButtons
            delegate: operationButtonDelegate
        }
    }


    Text {
        id: buttonContainer_operationsGroceryShopping_title
        x: text1.x
        y: buttonContainer_operationsNonGroceryShopping_title.y + buttonContainer_operationsNonGroceryShopping_background.height + section_spacing
        // width: 285
        // height: 14
        text: qsTr("Grocery shopping")
        font.pixelSize: text1.font.pixelSize
        font.styleName: "Bold"
    }

    Rectangle {
        id: buttonContainer_operationsGroceryShopping_background
        x: 222
        y: buttonContainer_operationsNonGroceryShopping_background.y + buttonContainer_operationsNonGroceryShopping_background.height + section_spacing
        width: 1006
        height: 42
        // color: '#f4f4f4'
    }

    Flow {
        id: buttonContainer_operationsGroceryShopping_container
        spacing: buttonContainer_operationsEatingOut.spacing
        x: 222
        y: buttonContainer_operationsGroceryShopping_background.y
        width: 1006
        height: 42

        Repeater {
            model: backend.operationButtonList_operationsGroceryShopping.operationButtons
            delegate: operationButtonDelegate
        }
    }




    Text {
        id: buttonContainer_operationsTransportation_title
        x: text1.x
        y: buttonContainer_operationsGroceryShopping_title.y + buttonContainer_operationsGroceryShopping_background.height + section_spacing
        // width: 285
        // height: 14
        text: qsTr("Transportation shopping")
        font.pixelSize: text1.font.pixelSize
        font.styleName: "Bold"
    }

    Rectangle {
        id: buttonContainer_operationsTransportation_background
        x: 222
        y: buttonContainer_operationsGroceryShopping_background.y + buttonContainer_operationsGroceryShopping_background.height + section_spacing
        width: 1006
        height: 42
        // color: '#f4f4f4'
    }

    Flow {
        id: buttonContainer_operationsTransportation_container
        spacing: buttonContainer_operationsEatingOut.spacing
        x: 222
        y: buttonContainer_operationsTransportation_background.y
        width: 1006
        height: 42

        Repeater {
            model: backend.operationButtonList_operationsTransportation.operationButtons
            delegate: operationButtonDelegate
        }
    }


    Text {
        id: buttonContainer_operationsRegularExpenses_title
        x: text1.x
        y: buttonContainer_operationsTransportation_title.y + buttonContainer_operationsTransportation_background.height + section_spacing
        // width: 285
        // height: 14
        text: qsTr("Regular expenses")
        font.pixelSize: text1.font.pixelSize
        font.styleName: "Bold"
    }

    Rectangle {
        id: buttonContainer_operationsRegularExpenses_background
        x: 222
        y: buttonContainer_operationsTransportation_background.y + buttonContainer_operationsTransportation_background.height + section_spacing
        width: 1006
        height: 42
        //color: '#f4f4f4'
    }

    Flow {
        id: buttonContainer_operationsRegularExpenses_container
        spacing: buttonContainer_operationsEatingOut.spacing
        x: 222
        y: buttonContainer_operationsRegularExpenses_background.y
        width: 1006
        height: 42

        Repeater {
            model: backend.operationButtonList_operationsRegularExpenses.operationButtons
            delegate: operationButtonDelegate
        }
    }

    Text {
        id: buttonContainer_operationsOtherExpenses_title
        x: text1.x
        y: buttonContainer_operationsRegularExpenses_title.y + buttonContainer_operationsRegularExpenses_background.height + section_spacing
        // width: 285
        // height: 14
        text: qsTr("Other expenses")
        font.pixelSize: text1.font.pixelSize
        font.styleName: "Bold"
    }

    Rectangle {
        id: buttonContainer_operationsOtherExpenses_background
        x: 222
        y: buttonContainer_operationsRegularExpenses_background.y + buttonContainer_operationsRegularExpenses_background.height + section_spacing
        width: 1006
        height: 42
        //color: '#f4f4f4'
    }

    Flow {
        id: buttonContainer_operationsOtherExpenses_container
        spacing: buttonContainer_operationsEatingOut.spacing
        x: 222
        y: buttonContainer_operationsOtherExpenses_background.y
        width: 1006
        height: 42

        Repeater {
            model: backend.operationButtonList_operationsOtherExpenses.operationButtons
            delegate: operationButtonDelegate
        }
    }

    Text {
        id: buttonContainer_operationsPhotography_title
        x: text1.x
        y: buttonContainer_operationsOtherExpenses_title.y + buttonContainer_operationsOtherExpenses_background.height + section_spacing
        // width: 285
        // height: 14
        text: qsTr("Photography")
        font.pixelSize: text1.font.pixelSize
        font.styleName: "Bold"
    }

    Rectangle {
        id: buttonContainer_operationsPhotography_background
        x: 222
        y: buttonContainer_operationsOtherExpenses_background.y + buttonContainer_operationsOtherExpenses_background.height + section_spacing
        width: 1006
        height: 42
        //color: '#f4f4f4'
    }

    Flow {
        id: buttonContainer_operationsPhotography_container
        spacing: buttonContainer_operationsEatingOut.spacing
        x: 222
        y: buttonContainer_operationsPhotography_background.y
        width: 1006
        height: 42

        Repeater {
            model: backend.operationButtonList_operationsPhotography.operationButtons
            delegate: operationButtonDelegate
        }
    }

    Text {
        id: buttonContainer_operationsIncoming_title
        x: text1.x
        y: buttonContainer_operationsPhotography_title.y + buttonContainer_operationsPhotography_background.height + section_spacing
        // width: 285
        // height: 14
        text: qsTr("Incoming")
        font.pixelSize: text1.font.pixelSize
        font.styleName: "Bold"
    }

    Rectangle {
        id: buttonContainer_operationsIncoming_background
        x: 222
        y: buttonContainer_operationsPhotography_background.y + buttonContainer_operationsPhotography_background.height + section_spacing
        width: 1006
        height: 42
        //color: '#f4f4f4'
    }

    Flow {
        id: buttonContainer_operationsIncoming_container
        spacing: buttonContainer_operationsEatingOut.spacing
        x: 222
        y: buttonContainer_operationsIncoming_background.y
        width: 1006
        height: 42

        Repeater {
            model: backend.operationButtonList_operationsIncoming.operationButtons
            delegate: operationButtonDelegate
        }
    }

    Text {
        id: buttonContainer_operationsSummary_title
        x: text1.x
        y: buttonContainer_operationsIncoming_title.y + buttonContainer_operationsIncoming_background.height + section_spacing
        // width: 285
        // height: 14
        text: qsTr("Summary")
        font.pixelSize: text1.font.pixelSize
        font.styleName: "Bold"
    }

    Rectangle {
        id: buttonContainer_operationsSummary_background
        x: 222
        y: buttonContainer_operationsIncoming_background.y + buttonContainer_operationsIncoming_background.height + section_spacing
        width: 1006
        height: 42
        //color: '#f4f4f4'
    }

    Flow {
        id: buttonContainer_operationsSummary_container
        spacing: buttonContainer_operationsEatingOut.spacing
        x: 222
        y: buttonContainer_operationsSummary_background.y
        width: 1006
        height: 42

        Repeater {
            model: backend.operationButtonList_operationsSummary.operationButtons
            delegate: operationButtonDelegate
        }
    }

    Row {
        id: monthsSelection_container
        x: 902
        y: 86
        width: 312
        height: 27
        spacing: 26
        layoutDirection: Qt.LeftToRight
        padding: 0
        leftPadding: 27

        Button {
            id: previousMonth_button
            text: qsTr("<")
            onClicked: backend.previousMonth()
        }

        Text {
            id: currentMonth_text
            y: 3
            text: backend.selectedMonthAsQString
            font.letterSpacing: 0
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.wordSpacing: 0
            width: 100
        }

        Button {
            id: nextMonth_button
            text: qsTr(">")
            onClicked: backend.nextMonth() 
        }

    }
}
