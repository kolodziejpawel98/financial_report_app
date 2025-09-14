import QtQuick
import QtQuick.Controls 2.15

Window {
    width: 1266
    height: 668
    visible: true
    title: qsTr("Hello World")


    Rectangle {
        id: sidebar
        x: 0
        y: 0
        width: 186
        height: 668
        color: "#353535"
        radius: 0
        border.color: "#949494"
        border.width: 0
    }
    Rectangle {
        id: topbar
        x: 0
        y: 0
        width: 1266
        height: 80
        color: "#292929"
        radius: 0

        Text {
            id: text2
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

    Button {
        id: loadXmlButtonBackground
        x: 500
        y: 254
        width: 350
        height: 250
        flat: true

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                backend.loadXmlButtonClicked()
            }
            onEntered: parent.background.color = "#b073fa"
            onExited: parent.background.color = "#BB86FC"

        Rectangle {
            id: rectangle
            x: 121
            y: 168
            width: 107
            height: 23
            color: "#742fa4"
            radius: 3
        }

        Text {
            id: text1
            x: 123
            y: 173
            width: 105
            height: 14
            color: "#ffffff"
            text: qsTr("Load XML file")
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
        }
    }

        background: Rectangle {
            color: "#BB86FC"
            radius: 8
            opacity: 0.4
        }

        Image {
            id: image
            x: 125
            y: 61
            width: 100
            height: 100
            source: "file:/home/pablo/Desktop/financial_report_app/icons/icon_upload-removebg-preview.png"
            fillMode: Image.PreserveAspectFit
        }

    }
}
