import QtQuick
import QtQuick.Controls 2.15

Rectangle {
    width: 1266
    height: 668
    color: "#ffffff"

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



    Rectangle {
        id: mainScreenBackgroundRectangle
        x: 0
        y: 0
        width: 1266
        height: 668
        color: "#b0282828"
    }




    Rectangle {
        id: rectangle
        x: 290
        y: 150
        width: 812
        height: 440
        color: "#ffffff"
        radius: 10
    }


    Button {
        width: 91
        height: 33
        anchors.centerIn: parent
        text: "OK"
        anchors.verticalCenterOffset: 81
        anchors.horizontalCenterOffset: 112
        onClicked: stackView.pop()
    }

    Button {
        width: 153
        height: 33
        text: "Save changes"
        anchors.verticalCenterOffset: 220
        anchors.horizontalCenterOffset: 366
        anchors.centerIn: parent
    }

    Text {
        id: text1
        x: 406
        y: 263
        width: 64
        height: 14
        text: qsTr("Operation:")
        font.pixelSize: 12
        font.weight: Font.DemiBold
    }

    Text {
        id: text3
        x: 476
        y: 263
        width: 486
        height: 42
        text: qsTr("sampletext sampletext sampletext sampletextsampletext sampletextsampletext sampletext")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignTop
        font.weight: Font.Normal
    }

    TextField {
        id: textField
        x: 406
        y: 311
        width: 384
        height: 24
        placeholderText: qsTr("Text Field")
    }

    ComboBox {
        id: comboBox
        x: 626
        y: 354
        width: 164
        height: 24
    }


}
