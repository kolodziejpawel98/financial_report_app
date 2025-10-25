import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt5Compat.GraphicalEffects

Rectangle {
    width: 1266
    height: 668

    Component.onCompleted: {
        backend.initDefineCategoriesForUndefinedOperations_screen()
    }

    Rectangle {
        id: background_color
        anchors.fill: parent
        color: "#f8f9fc"

        Text {
            id: text1
            x: 266
            y: 38
            width: 282
            height: 14
            text: qsTr("Undefined operations")
            font.pixelSize: 30
            font.styleName: "Bold"
            font.family: "Lato"
        }
    }

    ListView {
        id: undefinedOperations_table
        anchors.fill: parent
        anchors.margins: 20
        anchors.leftMargin: 267
        anchors.topMargin: 93
        // model: tableModel
        model: backend.operationButtonList_operationsSelfDefined.operationButtons
        clip: true

        delegate: Rectangle {
            width: undefinedOperations_table.width
            height: 40
            color: isHeader ? "#e0e0e0" : (index % 2 === 0 ? "#ffffff" : "#f1f2f6")

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 20

                Text {
                    text: buttonText
                    font.bold: isHeader
                    verticalAlignment: Text.AlignVCenter
                    color: "#222"
                    font.pixelSize: 14
                    Layout.preferredWidth: 200
                    Layout.alignment: Qt.AlignVCenter
                }

                // Text {
                //     text: description
                //     font.bold: isHeader
                //     verticalAlignment: Text.AlignVCenter
                //     color: "#555"
                //     font.pixelSize: 14
                //     Layout.preferredWidth: 100
                //     Layout.alignment: Qt.AlignVCenter
                // }

                // RowLayout {
                //     spacing: 10
                //     Layout.preferredWidth: 200
                //     Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                //     Button {
                //         text: "B1"
                //         width: 40
                //         height: 28
                //         visible: !isHeader
                //         background: Rectangle { color: "#FCCF66"; radius: 4 }
                //         onClicked: console.log("Button 1 clicked:", date)
                //     }

                //     Text {
                //         text: category
                //         font.bold: isHeader
                //         verticalAlignment: Text.AlignVCenter
                //         color: "#555"
                //         font.pixelSize: 14
                //         horizontalAlignment: Text.AlignHCenter
                //     }

                //     Button {
                //         text: "B2"
                //         width: 40
                //         height: 28
                //         visible: !isHeader
                //         background: Rectangle { color: "#FCCF66"; radius: 4 }
                //         onClicked: console.log("Button 2 clicked:", date)
                //     }
                // }
            }
        }

        ListModel {
            id: tableModel
            ListElement { date: "Date"; description: "Description"; category: "Category"; isHeader: true }
            ListElement { date: "Coffee"; description: "10.99"; category: "Eating"; isHeader: false }
            ListElement { date: "Tea"; description: "7.50"; category: "Eating"; isHeader: false }
            ListElement { date: "Juice"; description: "12.30"; category: "Groceries"; isHeader: false }
        }
    }

    // Connections {
    //     target: backend.operationButtonList_operationsSelfDefined
    //     function onOperationButtonsChanged() {
    //         undefinedOperations_table.model = backend.operationButtonList_operationsSelfDefined.operationButtons
    //         console.log("Liczba przycisków:", backend.operationButtonList_operationsSelfDefined.getSize())
    //     }
    // }


    Rectangle {
        id: menu_sidebar
        x: 29
        y: 15
        width: 219
        height: 638
        color: "#ffffff"
        radius: 7
        border.color: "#949494"
        border.width: 0
        topLeftRadius: 7

        layer.enabled: true
        layer.effect: DropShadow {
            color: '#27393987'
            radius: 24
            samples: 32
            horizontalOffset: 3
            verticalOffset: 3
            spread: 0
        }

        Text {
            id: logo_text
            x: 83
            y: 30
            text: qsTr("Text")
            color: "#000000"
            font.family: "Lato"
            font.pixelSize: 24
            font.weight: Font.Black
        }

        Button {
            id: sidebarButton_report
            x: 85
            y: 124
            font.family: "Lato"
            font.pixelSize: 16
            font.weight: Font.Normal
            contentItem: Text {
                anchors.centerIn: parent
                color: "#D1D3DA"
                text: "Report"
            }
            background: Rectangle { color: "transparent"; radius: 6 }
        }

        Button {
            id: sidebarButton_allOperations
            x: 65
            y: 191
            font.family: "Lato"
            font.pixelSize: 16
            font.weight: Font.Normal
            contentItem: Text {
                anchors.centerIn: parent
                color: "#D1D3DA"
                text: "All operations"
            }
            background: Rectangle { color: "transparent"; radius: 6 }
        }

        Button {
            id: sidebarButton_statistics
            x: 77
            y: 260
            font.family: "Lato"
            font.pixelSize: 16
            font.weight: Font.Normal
            contentItem: Text {
                anchors.centerIn: parent
                color: "#D1D3DA"
                text: "Statistics"
            }
            background: Rectangle { color: "transparent"; radius: 6 }
        }

        Button {
            id: button_loadNewXML
            x: 32
            y: 579
            width: 155
            height: 36
            font.family: "Lato"
            font.pixelSize: 16
            font.weight: Font.Medium
            text: "Load new XML"
            background: Rectangle {
                id: button_ignoreThem_background
                color: "#FFFFFF"
                border.color: "#D1D3DA"
                border.width: 2
                radius: 4
            }
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onEntered: {
                    button_ignoreThem_background.color = '#ececec'
                    button_ignoreThem_background.border.color = '#bbbdc4'
                }
                onExited: {
                    button_ignoreThem_background.color = "#FFFFFF"
                    button_ignoreThem_background.border.color = "#D1D3DA"
                }
            }
        }
    }
}
