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

    //     Rectangle {
    //     id: undefinedOperationsContainer
    //     anchors.fill: parent
    //     anchors.margins: 20
    //     anchors.leftMargin: 267
    //     anchors.topMargin: 93
    //     anchors.bottomMargin: 96
    //     color: "#00f8f9fc"
    //     radius: 8
    //     border.color: "#eff0f2"
    //     border.width: 2

    //     ColumnLayout {
    //         anchors.fill: parent
    //         anchors.bottomMargin: 63
    //         spacing: 0

    //         Rectangle {
    //             id: headerBar
    //             height: 40
    //             color: "#f8f9fc"
    //             radius: 8
    //             border.color: "#eff0f2"
    //             border.width: 2
    //             bottomRightRadius: 0
    //             bottomLeftRadius: 0
    //             Layout.fillWidth: true

    //             RowLayout {
    //                 anchors.fill: parent
    //                 anchors.margins: 10
    //                 spacing: 20
    //                 Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

    //                 Text {
    //                     text: "Button Text"
    //                     font.bold: true
    //                     color: "#adaeb5"
    //                     font.pixelSize: 16
    //                     font.styleName: "Bold"
    //                     font.family: "Lato"
    //                     Layout.preferredWidth: 50
    //                     // Layout.alignment: Qt.AlignVCenter
    //                 }

    //                 Text {
    //                     text: "Description"
    //                     font.bold: true
    //                     color: "#adaeb5"
    //                     font.pixelSize: 16
    //                     font.styleName: "Bold"
    //                     font.family: "Lato"
    //                     Layout.preferredWidth: 300
    //                     // Layout.alignment: Qt.AlignVCenter
    //                 }

    //                 Text {
    //                     text: "Width"
    //                     font.bold: true
    //                     color: "#adaeb5"
    //                     font.pixelSize: 16
    //                     font.styleName: "Bold"
    //                     Layout.preferredWidth: 150
    //                     // Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    //                 }
    //             }
    //         }

    //         ListView {
    //             id: undefinedOperations_table
    //             Layout.fillWidth: true
    //             Layout.fillHeight: true
    //             clip: true
    //             // model: tableModel
    //             model: backend.operationButtonList_operationsSelfDefined.operationButtons

    //             delegate: Rectangle {
    //                 width: undefinedOperations_table.width
    //                 height: 40
    //                 color: index % 2 === 0 ? "#ffffff" : "#f8f9fc"

    //                 RowLayout {
    //                     anchors.fill: parent
    //                     anchors.margins: 10
    //                     spacing: 20

    //                     Text {
    //                         text: buttonText
    //                         font.pixelSize: 14
    //                         color: "#222"
    //                         Layout.preferredWidth: 50
    //                     }

    //                     Text {
    //                         text: buttonDescriptionRectangleText
    //                         font.pixelSize: 14
    //                         color: "#555"
    //                         Layout.preferredWidth: 400
    //                         elide: Text.ElideRight
    //                     }

    //                     RowLayout {
    //                         spacing: 10
    //                         Layout.preferredWidth: 100
    //                         // Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

    //                         Button {
    //                             text: "<"
    //                             width: 40
    //                             height: 28
    //                             background: Rectangle { color: "#FCCF66"; radius: 4 }
    //                             onClicked: console.log("Button 1 clicked:", buttonText)
    //                         }

    //                         Text {
    //                             text: buttonWidth
    //                             verticalAlignment: Text.AlignVCenter
    //                             color: "#555"
    //                             font.pixelSize: 14
    //                             Layout.preferredWidth: 50
    //                             elide: Text.ElideRight
    //                             horizontalAlignment: Text.AlignHCenter
    //                         }

    //                         Button {
    //                             text: ">"
    //                             width: 40
    //                             height: 28
    //                             background: Rectangle { color: "#FCCF66"; radius: 4 }
    //                             onClicked: console.log("Button 2 clicked:", buttonText)
    //                         }
    //                     }
    //                 }
    //             }
    //         }

    //         //         ListModel {
    //         //     id: tableModel
    //         //     ListElement { date: "Date"; description: "Description"; category: "Category"; isHeader: true }
    //         //     ListElement { date: "Coffee"; description: "10.99"; category: "Eating"; isHeader: false }
    //         //     ListElement { date: "Tea"; description: "7.50"; category: "Eating"; isHeader: false }
    //         //     ListElement { date: "Juice"; description: "12.30"; category: "Eating"; isHeader: false }
    //         // }

    //     }
    // }



    Rectangle {
        id: undefinedOperationsContainer
        anchors.fill: parent
        anchors.margins: 20
        anchors.leftMargin: 267
        anchors.topMargin: 93
        anchors.bottomMargin: 96
        color: "#00f8f9fc"
        radius: 8
        border.color: "#eff0f2"
        border.width: 2

        ColumnLayout {
            anchors.fill: parent
            anchors.bottomMargin: 0
            spacing: 0

            Rectangle {
                id: headerBar
                height: 40
                color: "#f8f9fc"
                radius: 8
                border.color: "#eff0f2"
                border.width: 2
                bottomRightRadius: 0
                bottomLeftRadius: 0
                Layout.fillWidth: true

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 20
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    Text {
                        text: "Date"
                        font.bold: true
                        color: "#adaeb5"
                        font.pixelSize: 16
                        font.styleName: "Bold"
                        font.family: "Lato"
                        Layout.preferredWidth: 50
                        // Layout.alignment: Qt.AlignVCenter
                    }

                    Text {
                        text: "Description"
                        font.bold: true
                        color: "#adaeb5"
                        font.pixelSize: 16
                        font.styleName: "Bold"
                        font.family: "Lato"
                        Layout.preferredWidth: 500
                        // Layout.alignment: Qt.AlignVCenter
                    }

                    Text {
                        text: "Category"
                        font.bold: true
                        color: "#adaeb5"
                        font.pixelSize: 16
                        font.styleName: "Bold"
                        Layout.preferredWidth: 175
                        // Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                }
            }

            ListView {
                id: undefinedOperations_table
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                model: tableModel
                property int visibleRows: 12
                    property int heightOfOneRow: 40
                        height: visibleRows * heightOfOneRow
                        // model: backend.operationButtonList_operationsSelfDefined.operationButtons

                        delegate: Rectangle {
                            width: undefinedOperations_table.width
                            height: 40
                            // color: index % 2 === 0 ? "#f8f9fc" : '#ffffff'
                            color: "#f8f9fc"

                            Rectangle {
                                visible: index > 0
                                anchors.top: parent.top
                                anchors.left: parent.left
                                anchors.right: parent.right
                                height: 2
                                color: '#eff0f2'
                            }

                            Rectangle {
                                anchors.left: parent.left
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                width: 2
                                color: '#eff0f2'
                            }

                            Rectangle {
                                anchors.right: parent.right
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                width: 2
                                color: "#eff0f2"
                            }

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 10
                                spacing: 20

                                Text {
                                    text: date
                                    font.pixelSize: 14
                                    color: "#222"
                                    Layout.preferredWidth: 50
                                }

                                Text {
                                    text: description
                                    font.pixelSize: 14
                                    color: "#555"
                                    Layout.preferredWidth: 400
                                    elide: Text.ElideRight
                                }

                                RowLayout {
                                    spacing: 10
                                    Layout.preferredWidth: 100

                                    Button {
                                        id: rightArrowButton
                                        text: "<"
                                        Layout.preferredWidth: 25
                                        width: 25
                                        height: 25
                                        hoverEnabled: true

                                        background: Rectangle {
                                            radius: 4
                                            color: leftArrowButton.hovered ? '#000000' : "#222636"
                                            Behavior on color { ColorAnimation { duration: 150 } }
                                        }

                                        contentItem: Text {
                                            text: rightArrowButton.text
                                            font.family: "Lato"
                                            font.weight: Font.Black
                                            color: "white"
                                            horizontalAlignment: Text.AlignHCenter
                                            verticalAlignment: Text.AlignVCenter
                                            anchors.fill: parent
                                        }

                                        onClicked: console.log("Button clicked:", text)

                                        MouseArea {
                                            anchors.fill: parent
                                            hoverEnabled: true
                                            cursorShape: Qt.PointingHandCursor
                                            acceptedButtons: Qt.NoButton
                                        }

                                        layer.enabled: rightArrowButton.hovered
                                        layer.effect: DropShadow {
                                            color: '#40393987'
                                            radius: 20
                                            samples: 32
                                            horizontalOffset: 2
                                            verticalOffset: 2
                                        }

                                        Behavior on layer.enabled {
                                        NumberAnimation { duration: 150 }
                                    }
                                }

                                Text {
                                    text: category
                                    verticalAlignment: Text.AlignVCenter
                                    font.pixelSize: 14
                                    Layout.preferredWidth: 150
                                    elide: Text.ElideRight
                                    horizontalAlignment: Text.AlignHCenter
                                    color: category === "Eating" ? "#d63031"
                                    : category === "Groceries" ? "#00b894"
                                    : "#555"

                                }

                                Button {
                                    id: leftArrowButton
                                    text: ">"
                                    Layout.preferredWidth: 25
                                    width: 25
                                    height: 25
                                    hoverEnabled: true

                                    background: Rectangle {
                                        radius: 4
                                        color: leftArrowButton.hovered ? '#000000' : "#222636"
                                        Behavior on color { ColorAnimation { duration: 150 } }
                                    }

                                    contentItem: Text {
                                        text: leftArrowButton.text
                                        font.family: "Lato"
                                        font.weight: Font.Black
                                        color: "white"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        anchors.fill: parent
                                    }

                                    onClicked: console.log("Button clicked:", text)

                                    MouseArea {
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                        acceptedButtons: Qt.NoButton
                                    }

                                    layer.enabled: leftArrowButton.hovered
                                    layer.effect: DropShadow {
                                        color: '#40393987'
                                        radius: 20
                                        samples: 32
                                        horizontalOffset: 2
                                        verticalOffset: 2
                                    }

                                    Behavior on layer.enabled {
                                    NumberAnimation { duration: 150 }
                                }
                            }
                        }
                    }
                }
            }

            ListModel {
                id: tableModel
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Category"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Eating"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Groceries"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Non-grocery shopping"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Category"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Eating"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Groceries"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Non-grocery shopping"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Category"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Eating"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Groceries"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Non-grocery shopping"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Category"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Eating"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Groceries"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Non-grocery shopping"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Category"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Eating"}
                ListElement { date: "01/04/43"; description: "Description fs fds fd  fdsfdsfDescription"; category: "Groceries"}
                ListElement { date: "01/04/43"; description: "xdddd fs fds fd  fdsfdsfDescription"; category: "Non-grocery shopping"}
            }

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
