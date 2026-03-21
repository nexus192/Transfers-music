import QtQuick
import QtQuick.Controls

import "../Widgets"

Page {
    id: _page

    function run() {
        if (_id.text == "") {
            _id.isError = true
            return
        }
        if (_secret.text == "") {
            _secret.isError = true
            return
        }
        _page.log()
    }

    signal log

    background: Rectangle {
        width: parent.width
        height: parent.height
        color: "#FFFFFF"
    }

    Rectangle {
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2
        width: 500
        height: 300
        border.width: 3
        border.color: "#31AC31"
        radius: 12

        Column {
            y: 20
            width: parent.width
            spacing: 20

            Column {
                x: parent.width / 2 - width / 2
                spacing: 4
                Label {
                    x: parent.width / 2 - width / 2
                    font {
                        pixelSize: 14
                        weight: Font.DemiBold
                    }
                    color: "#404040"
                    text: "Client ID: *"
                }
                TMTextField {
                    id: _id
                    width: 400
                }
            }

            Column {
                x: parent.width / 2 - width / 2
                spacing: 4
                Label {
                    x: parent.width / 2 - width / 2
                    font {
                        pixelSize: 14
                        weight: Font.DemiBold
                    }
                    color: "#404040"
                    text: "Client Secret: *"
                }
                TMTextField {
                    id: _secret
                    width: 400
                }
            }
        }

        TMTextButton {
            x: parent.width / 2 - width / 2
            y: parent.height - height - 20
            width: 75
            height: 35
            text: "LogIn"
            onClicked: () => _page.run()
        }
    }
}
