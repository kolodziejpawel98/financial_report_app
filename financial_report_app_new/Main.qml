import QtQuick
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 1266
    height: 668

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: mainScreenComponent
    }

    Component {
        id: mainScreenComponent
        Rectangle {
            width: stackView.width
            height: stackView.height
            color: "#fbe18f"

            Button {
                id: myButton
                anchors.centerIn: parent
                width: 250
                height: 60
                text: "Next screen"

                onClicked: {
                    backend.printTestString()
                    stackView.push(secondScreenComponent)
                }

                background: Rectangle {
                    radius: 8
                    color: myButton.containsMouse ? "darkred" : "red"
                    Behavior on color { ColorAnimation { duration: 200 } }
                }
            }
        }
    }

    Component {
        id: secondScreenComponent
        Loader {
            source: "SecondScreen.qml"
            onLoaded: {
                item.requestPop.connect(function() { stackView.pop() })
            }
        }
    }
}
