import QtQuick
import QtQuick.Controls

TextField {
    id: _field

    property bool isError: false
    property double fieldHeight: 50
    property color backgroundColor: "#EBEDF4"

    property alias text: _field.text

    width: 100
    leftPadding: 12
    rightPadding: 12
    verticalAlignment: Text.AlignVCenter
    font.pixelSize: 16
    color: "#404040"
    placeholderText: _field.placeholderText
    placeholderTextColor: "#404040"
    horizontalAlignment: Text.Center
    text: _field.text

    background: Rectangle {
        width: _field.width
        radius: 8
        border.width: _field.isError || _field.activeFocus ? 1 : 0
        border.color: _field.isError ? "#B6002D" : "#31AC31"
        color: _field.backgroundColor
    }

    onTextEdited: () => _field.isError = false
}
