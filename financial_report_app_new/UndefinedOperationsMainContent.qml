import QtQuick
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects

Rectangle {
    width: 1266
    height: 668

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
        anchors.leftMargin: 265
        anchors.rightMargin: 27
        anchors.topMargin: 100
        anchors.bottomMargin: 47
        model: tableModel
        clip: true
        spacing: 6

        delegate: Rectangle {
            width: undefinedOperations_table.width
            height: 40
            radius: 6
            color: index % 2 === 0 ? "#ffffff" : "#f1f2f6"

            Row {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 20

                Text {
                    text: name
                    width: 200
                    verticalAlignment: Text.AlignVCenter
                    color: "#222"
                    font.pixelSize: 14
                }

                Text {
                    text: price + " zł"
                    width: 100
                    color: "#555"
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                }

                Button {
                    text: "Edit"
                    width: 80
                    height: 28
                    background: Rectangle {
                        color: "#FCCF66"
                        radius: 4
                    }
                    onClicked: console.log("Editing:", name)
                }
            }
        }


        ListModel {
            id: tableModel
            ListElement { name: "Coffee"; price: "10.99" }
            ListElement { name: "Tea"; price: "7.50" }
            ListElement { name: "Juice"; price: "12.30" }
        }
    }

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

            background: Rectangle {
                color: "transparent"
                radius: 6
            }
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

            background: Rectangle {
                color: "transparent"
                radius: 6
            }
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

            background: Rectangle {
                color: "transparent"
                radius: 6
            }
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

            // contentItem: Text {
            //     id: button_ignoreThem_text
            //     text: button_ignoreThem.text
            //     color: "#ADAEB5"
            //     font: button_ignoreThem.font
            //     anchors.centerIn: parent
            //     horizontalAlignment: Text.AlignHCenter
            //     verticalAlignment: Text.AlignVCenter
            // }

            background: Rectangle {
                id: button_ignoreThem_background
                color: "#FFFFFF"
                border.color: "#D1D3DA"
                border.width: 2
                radius: 4
            }

            MouseArea {
                anchors.fill: parent
                anchors.leftMargin: -22
                anchors.rightMargin: 22
                anchors.topMargin: -7
                anchors.bottomMargin: 7
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor

                onEntered: {
                    button_ignoreThem_background.color = '#ececec'
                    button_ignoreThem_background.border.color = '#bbbdc4'
                    button_ignoreThem_text.color = '#9b9ca5'
                }
                onExited: {
                    button_ignoreThem_background.color = "#FFFFFF"
                    button_ignoreThem_background.border.color = "#D1D3DA"
                    button_ignoreThem_text.color = '#ADAEB5'
                }
            }
        }
    }
}
