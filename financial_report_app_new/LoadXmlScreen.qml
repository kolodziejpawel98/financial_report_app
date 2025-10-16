import QtQuick
import QtQuick.Controls 2.15
// import QtGraphicalEffects 1.15
import QtGraphicalEffects 1.15

Rectangle {
    width: 1266
    height: 668

    Rectangle {
        id: background_color
        x: 0
        y: 0
        width: 1266
        height: 668
        color: "#f8f9fc"
    }

    Rectangle {
        id: menu_sidebar
        x: 18
        y: 15
        width: 219
        height: 638
        color: "#ffffff"
        radius: 7
        border.color: "#949494"
        border.width: 0
        topLeftRadius: 7

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
                // font.family: control.font.family
                // font.pixelSize: control.font.pixelSize
                // font.weight: control.font.weight
            }

            background: Rectangle {
                color: "transparent"
                radius: 6
            }
        }

        // DropShadow {
        //     anchors.fill: myRect
        //     source: myRect
        //     horizontalOffset: 2
        //     verticalOffset: 2
        //     blurRadius: 28
        //     color: "#E6EAF5"
        //     opacity: 0.99
        // }

// DropShadow {
//         anchors.fill: butterfly
//         horizontalOffset: 3
//         verticalOffset: 3
//         radius: 8.0
//         color: "#80000000"
//         source: butterfly
//     }

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
                // font.family: control.font.family
                // font.pixelSize: control.font.pixelSize
                // font.weight: control.font.weight
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
                // font.family: control.font.family
                // font.pixelSize: control.font.pixelSize
                // font.weight: control.font.weight
            }

            background: Rectangle {
                color: "transparent"
                radius: 6
            }
        }

        // DesignEffect {
        //     effects: [
        //         DesignDropShadow {
        //             color: "#9c2a2a"
        //             spread: 9
        //             offsetX: 5
        //         }
        //     ]
        // }

    }

    Button {
        id: button_loadXmlBig
        x: 556
        y: 204
        width: 334
        height: 231
        flat: true

        MouseArea {
            anchors.fill: parent
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if (backend.loadXmlButtonClicked())
                {
                    stackView.push("DescribeUndefinedTagsScreen.qml")
                } else {
                console.log("Błąd: nie wybrano pliku XML")
            }
        }
        onEntered: parent.background.color = "#b073fa"
        onExited: parent.background.color = "#BB86FC"

        // Rectangle {
        //     id: smallButtonRectangle
        //     x: -66
        //     y: -57
        //     width: 107
        //     height: 23
        //     color: "#742fa4"
        //     radius: 3
        // }

        // Text {
        //     id: buttonLoadXmlSmallText
        //     x: -74
        //     y: -53
        //     width: 105
        //     height: 14
        //     color: "#ffffff"
        //     text: qsTr("Load XML file")
        //     font.pixelSize: 12
        //     horizontalAlignment: Text.AlignHCenter
        // }
    }

    background: Rectangle {
        radius: 3
        color: "transparent"
        border.width: 3
        border.color: "#BB86FC"
        opacity: 0.5
    }
    Image {
        id: button_icon
        x: 131
        y: 56
        width: 73
        height: 64
        source: "file:/home/pablo/Desktop/financial_report_app/icons/icon_upload-removebg-preview.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: text_importYourXmlFile
        x: 66
        y: 126
        width: 204
        height: 20
        color: "#bb86fc"
        text: qsTr("Import your XML file")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        font.weight: Font.Normal
        font.family: "Lato"
    }

    Text {
        id: text_dragOrClickToUpload
        x: 66
        y: 152
        width: 204
        height: 20
        color: "#a8aab3"
        text: qsTr("Drag or click to upload")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        font.weight: Font.Normal
        font.family: "Lato"
    }

}

}
