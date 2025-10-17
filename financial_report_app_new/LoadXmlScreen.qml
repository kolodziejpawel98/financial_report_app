import QtQuick
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects

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
            color: "#00000033"
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
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            if (backend.loadXmlButtonClicked())
                stackView.push("DescribeUndefinedTagsScreen.qml")
            else
                console.log("Błąd: nie wybrano pliku XML")
        }
        onEntered: buttonDottedLine.opacity = 1.0   // pełna widoczność przy hover
    onExited: buttonDottedLine.opacity = 0.65
        // onEntered: parent.background.color = '#d5d8e0'
        // onExited: parent.background.color = "#f8f9fc" //?????
    }

    background: Item {
        id: backgroundItem
        anchors.fill: parent

        Image {
            id: buttonDottedLine
            anchors.fill: parent
            source: "file:../images/loadXml_button-01.svg"
            fillMode: Image.PreserveAspectFit
            anchors.margins: 12
            opacity: 0.65
        }
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
