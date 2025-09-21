import QtQuick
import QtQuick.Controls 2.15

Rectangle {
    width: 1266
    height: 668


    Component.onCompleted: {
        backend.initOperationsByType()
    }


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



// Flow {
//     id: buttonContainer
//     x: 222
//     y: 128
//     width: 1006
//     height: 58
//     spacing: 10

//     Repeater {
//         model: backend.dynamicButtons

//         Button {
//             text: modelData
//             width: 120
//             height: 40

//             onClicked: {
//                 console.log("button pushed", text)
//             }
//         }
//     }
// }
Flow {
    id: buttonContainer
    spacing: 10
    x: 222
    y: 128
    width: 1006
    height: 58

    Repeater {
        model: backend.operationButtons.operationButtons
        delegate: Button {
            text: modelData.buttonText
            width: modelData.buttonWidth
            height: 40

            hoverEnabled: true
            onHoveredChanged: {
                if (hovered) {
                    cursor: Qt.PointingHandCursor
                    // backend.operationButtons.operationButtons.operationButtonsHovered(text) ??
                    console.log("hover", text)
                }
            }

            onClicked: {
                console.log("clicked", text)
            }
        }
    }
}


}
