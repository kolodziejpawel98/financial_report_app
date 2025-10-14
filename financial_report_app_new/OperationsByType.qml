import QtQuick
import QtQuick.Controls 2.15

Rectangle {
    id: main_window
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
        id: work_area
        x: 183
        y: 80
        width: 1083
        height: 588
        color: "#ffffff"
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
                var pos = mapToItem(work_area, mouse.x, mouse.y)
                var rectanglePosition_x = mouse.x - 20
                
                // if(pos.x >= work_area.width/2){
                    // console.log("xd")
                    rectanglePosition_x = mouse.x - pos.x/2
                // }

                operationDescriptionRectangle.x = rectanglePosition_x
                operationDescriptionRectangle.y = mouse.y - 50

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

    Column {
        id: mainColumn
        x: 222
        y: 108
        spacing: section_spacing

        function createSection(title, model)
        {
            return Qt.createQmlObject(`
import QtQuick
import QtQuick.Controls 2.15

Column {
    spacing: 5
    Text { text: "` + title + `"; font.pixelSize: 14; font.bold: true }

    Flow {
        width: 1006
        spacing: 5
        flow: Flow.LeftToRight

        Repeater {
            model: ` + model + `
            delegate: operationButtonDelegate
        }
    }
}
`, mainColumn)
}

Component.onCompleted: {
    createSection("Eating out", "backend.operationButtonList_operationsEatingOut.operationButtons")
    createSection("Non grocery shopping", "backend.operationButtonList_operationsNonGroceryShopping.operationButtons")
    createSection("Grocery shopping", "backend.operationButtonList_operationsGroceryShopping.operationButtons")
    createSection("Transportation shopping", "backend.operationButtonList_operationsTransportation.operationButtons")
    createSection("Regular expenses", "backend.operationButtonList_operationsRegularExpenses.operationButtons")
    createSection("Other expenses", "backend.operationButtonList_operationsOtherExpenses.operationButtons")
    createSection("Photography", "backend.operationButtonList_operationsPhotography.operationButtons")
    createSection("Incoming", "backend.operationButtonList_operationsIncoming.operationButtons")
    createSection("Summary", "backend.operationButtonList_operationsSummary.operationButtons")
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
        width: 60
        height: 27
        flat: true

        background: Rectangle {
            color: previousMonth_area.containsMouse ? "#9763d5" : "#BB86FC"
            radius: 8
            opacity: 0.4
        }

        Text {
            anchors.centerIn: parent
            text: "<"
            color: "white"
            font.pixelSize: 14
        }

        MouseArea {
            id: previousMonth_area
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: backend.previousMonth()
        }
    }

    Text {
        id: currentMonth_text
        y: 3
        text: backend.selectedMonthAsQString
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: 100
        color: "black"
    }

    Button {
        id: nextMonth_button
        width: 60
        height: 27
        flat: true

        background: Rectangle {
            color: nextMonth_area.containsMouse ? '#9763d5' : "#BB86FC"
            radius: 8
            opacity: 0.4
        }

        Text {
            anchors.centerIn: parent
            text: ">"
            color: "white"
            font.pixelSize: 14
        }

        MouseArea {
            id: nextMonth_area
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: backend.nextMonth()
        }
    }
}

}
