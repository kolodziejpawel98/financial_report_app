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
    }

    Rectangle {
        id: warning_background
        x: 476
        y: 131
        width: 425
        height: 407
        color: "#ffffff"
        radius: 15
        opacity: 0
        scale: 0.8
        // opacity: 1
        // scale: 1
        visible: false

        layer.enabled: true
        layer.effect: DropShadow {
            color: '#27393987'
            radius: 24
            samples: 32
            horizontalOffset: 3
            verticalOffset: 3
            spread: 0
        }

        Behavior on opacity { NumberAnimation { duration: 400 } }
        Behavior on scale { NumberAnimation { duration: 400; easing.type: Easing.OutBack } }

        function showPopup()
        {
            visible = true
            opacity = 1
            scale = 1
        }

        function hidePopup()
        {
            opacity = 0
            scale = 0.5
            Qt.callLater(() => visible = false)
        }

        Component.onCompleted: {
            showPopup()
        }

        Rectangle {
            id: orangeIconWarning_background
            x: 34
            y: 25
            width: 56
            height: 56
            color: "#ffefc8"
            radius: 11

            Image {
                id: orangeIconWarning_icon
                width: 32.48
                height: 29.12
                anchors.centerIn: parent
                source: "file:../images/warning_icon.svg"
                fillMode: Image.PreserveAspectFit
                smooth: true
            }
        }

        Text {
            id: title_undefinedOperations
            x: 34
            y: 114
            width: 339
            height: 42
            color: "#222636"
            text: qsTr("Undefined operations")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignLeft
            font.styleName: "Bold"
            font.family: "Lato"
        }

        Text {
            id: text_inYourXmlFileThereAre
            x: 34
            y: 162
            width: 288
            height: 142
            color: "#adaeb5"
            font.pixelSize: 13
            font.family: "Lato"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            wrapMode: Text.Wrap
            textFormat: Text.RichText
            text: qsTr("In your XML file, there are some undefined operations. You can match them to the categories manually, or ignore them and put all of them into the \"<b>Others</b>\" category.")
        }

        Button {
            id: button_matchManually
            x: 34
            y: 265
            width: 339
            height: 36
            font.family: "Lato"
            font.pixelSize: 16
            font.weight: Font.Medium
            text: "Match manually"

            contentItem: Text {
                id: button_matchManually_text
                text: button_matchManually.text
                color: "#FFFFFF"
                font: button_matchManually.font
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                id: button_matchManually_background
                color: "#FCCF66"
                radius: 4
                border.color: "#FCCF66"
                border.width: 2

                Behavior on color { ColorAnimation { duration: 150 } }
                Behavior on border.color { ColorAnimation { duration: 150 } }
            }

            layer.enabled: true
            layer.effect: DropShadow {
                color: '#F8E2AE'
                radius: 20
                samples: 32
                horizontalOffset: 3
                verticalOffset: 3
                spread: 0
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor



                //  Here are 3 simple actions to show the button has hover states:
                //     adding shadows on button or
                //     changing the button backgorund color or
                //     making the text become bold



                onEntered: {
                    button_matchManually_background.color = '#f0bb3f'
                    button_matchManually_background.border.color = '#f9c64e'
                    button_matchManually_text.color = '#ffebbb'

                }
                onExited: {
                    button_matchManually_background.color = "#FCCF66"
                    button_matchManually_background.border.color = "#FCCF66"
                    button_matchManually_text.color = '#FFFFFF'

                }
            }
        }

        Button {
            id: button_ignoreThem
            x: 34
            y: 327
            width: 339
            height: 36
            font.family: "Lato"
            font.pixelSize: 16
            font.weight: Font.Medium
            text: "Ignore them"

            contentItem: Text {
                id: button_ignoreThem_text
                text: button_ignoreThem.text
                color: "#ADAEB5"
                font: button_ignoreThem.font
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

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
    }
}
