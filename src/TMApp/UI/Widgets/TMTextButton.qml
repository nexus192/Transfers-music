import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

Rectangle {
    id: _button

    property string text: "Button"
    property int fontWeight: 700

    property color enabledColor: "#31AC31"
    property color pressedColor: "#64CC64"
    property color disabledColor: "#252525"

    property color disabledBorderColor: "#717171"

    property color enabledTextColor: "#FFFFFF"
    property color pressedTextColor: "#FFFFFF"
    property color disabledTextColor: "#9DA4AE"

    property int pixelSize: 14
    property int margin: 24

    readonly property real contentWidth: 2 * margin + _buttonText.width

    signal clicked

    width: contentWidth
    activeFocusOnTab: true
    radius: 12
    color: {
        if (enabled && !_mouseArea.containsPress) {
            return enabledColor
        } else if (enabled && _mouseArea.containsPress) {
            return pressedColor
        } else {
            return disabledColor
        }
    }

    Label {
        id: _buttonText
        x: _button.width / 2 - width / 2
        y: parent.height / 2 - height / 2
        font.pixelSize: _button.pixelSize
        color: {
            if (enabled && !_mouseArea.containsPress) {
                return _button.enabledTextColor
            } else if (enabled && _mouseArea.containsPress) {
                return _button.pressedTextColor
            } else {
                return _button.disabledTextColor
            }
        }
        text: _button.text
    }

    MouseArea {
        id: _mouseArea
        width: parent.width
        height: parent.height
        cursorShape: Qt.PointingHandCursor
        onClicked: () => {
                       _button.forceActiveFocus()
                       _button.clicked()
                   }
    }
}
