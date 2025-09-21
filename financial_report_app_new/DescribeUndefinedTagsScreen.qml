import QtQuick
import QtQuick.Controls 2.15

Rectangle {
    width: 1266
    height: 668
    color: "#ffffff"

    Rectangle {
        id: menu_sidebar
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
        id: menu_topbar
        x: 0
        y: 0
        width: 1266
        height: 80
        color: "#292929"
        radius: 0
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

    Rectangle {
        id: blurredBackground
        x: 0
        y: 0
        width: 1266
        height: 668
        color: "#b0282828"
    }

    Rectangle {
        id: mainContent_whiteBackgroundRectangle
        x: 290
        y: 150
        width: 812
        height: 440
        color: "#ffffff"
        radius: 10
    }

    Button {
        id: mainContent_button_acceptUserInput
        width: 91
        height: 33
        anchors.centerIn: parent
        text: "OK"
        anchors.verticalCenterOffset: 155
        anchors.horizontalCenterOffset: 112
        onClicked: backend.nextOperation();
        // onClicked: stackView.pop()
    }

    TextArea {
        id: mainContent_textArea_userOperationDescription
        x: 391
        y: 312
        width: 399
        height: 110
        placeholderTextColor: "#006cc65b"
        placeholderText: qsTr("Text Area")
        wrapMode: Text.Wrap

        background: Rectangle {
            color: "#292929"
            radius: 5
            border.color: "#555555"
            border.width: 1
        }

        color: "white"
        onTextChanged: backend.userDescription.userOperationDescriptionText = text
        text: backend.userDescription.userOperationDescriptionText
    }

    Button {
        id: mainContent_button_saveChangesAndGoToNextScreen
        objectName: "mainContent_button_saveChangesAndGoToNextScreen"
        width: 153
        height: 33
        text: "Save changes"
        anchors.verticalCenterOffset: 220
        anchors.horizontalCenterOffset: 366
        anchors.centerIn: parent
        onClicked: stackView.push("OperationsByType.qml")

    }

    Text {
        id: mainContent_staticText_operation
        x: 391
        y: 206
        width: 64
        height: 14
        text: qsTr("Operation:")
        font.pixelSize: 12
        font.weight: Font.DemiBold
    }

    Text {
        id: mainContent_staticText_operationName
        x: 465
        y: 206
        width: 325
        height: 89
        font.pixelSize: 12
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignTop
        font.weight: Font.Normal
        wrapMode: Text.WordWrap
        onTextChanged: backend.operationDescription.operationDescriptionText = mainContent_staticText_operationName.text
        text: backend.operationDescription.operationDescriptionText
    }

    ComboBox {
        id: mainContent_comboBox_operationTag
        objectName: "mainContent_comboBox_operationTag"
        x: 626
        y: 435
        width: 164
        height: 24
        onCurrentIndexChanged: backend.tagIndex.userDescriptionCurrentTagIndex = currentIndex
    }

    Component.onCompleted: {
        backend.initDescribeUndefinedTagsScreen()
        mainContent_comboBox_operationTag.model = backend.getComboBoxItems()
    }
}

/*##^##
Designer {
    D{i:0}D{i:1;locked:true}D{i:2;locked:true}D{i:3;locked:true}D{i:4;locked:true}D{i:5;locked:true}
}
##^##*/
