import QtQuick
import QtQuick.Controls.Basic

import "UI/Windows"

ApplicationWindow {
    id: _app
    width: 600
    height: 600
    minimumWidth: 600
    minimumHeight: 600
    maximumWidth: 600
    maximumHeight: 600
    visible: true
    title: qsTr("TRANSFERS")

    StackView {
        id: _stackView
        anchors.fill: parent
        initialItem: _authWindowComponent
    }

    Component {
        id: _authWindowComponent
        Item {
            anchors.fill: parent
            Label {
                x: parent.width / 2 - width / 2
                y: 100
                font {
                    pixelSize: 26
                    weight: Font.DemiBold
                }
                color: "#404040"
                text: "TRANSFERS MUSIC"
            }

            AuthWindow {
                x: parent.width / 2 - width / 2
                y: 350
                onLog: () => _stackView.replace(_operationsWindowComponent)
            }
        }
    }

    Component {
        id: _operationsWindowComponent
        OperationsWindow {}
    }
}
