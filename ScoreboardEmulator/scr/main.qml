import QtQuick 2.8
import QtQuick.Window 2.2

Window {
    visible: true
    width: 430
    height: 170
    color: "#000000"
    title: qsTr("Scoreboard Emulator")
    Component.onCompleted:{
        pixels = digit1.pixels.concat(digit2.pixels, digit3.pixels, digit4.pixels);
    }

    property var pixels: []

    function componentToHex(c) {
        var hex = c.toString(16)
        return hex.length == 1 ? "0" + hex : hex
    }
    function rgbToHex(r, g, b) {
        return "#" + componentToHex(r) + componentToHex(g) + componentToHex(b)
    }
    function setPixel(index, r, g, b) {
        console.log("setPixel: " + index)
        if (index < 0 || index >= pixels.length) {
            console.log("invalid index");
            return;
        }
        pixels[index].color = rgbToHex(r, g, b)
    }

    Grid {
        id: grid3
        anchors.fill: parent
        spacing: 10
        rows: 2
        columns: 1

        Row {
            id: row
            width: 420
            height: 130
            spacing: 20

            Digit {
                id: digit1

            }

            Digit{
                id: digit2
            }

            Item {
                id: item1
                width: 70
                height: 130

                Column {
                    id: column
                    width: 10
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 20

                    Rectangle {
                        id: rectangle5
                        width: 10
                        height: 10
                        color: "#ffffff"
                    }

                    Rectangle {
                        id: rectangle6
                        width: 10
                        height: 10
                        color: "#ffffff"
                    }
                }
            }
            Digit {
                id: digit3

            }

            Digit{
                id: digit4
            }



        }

        Row {
            id: row6
            width: 420
            height: 20
            spacing: 10

            Rectangle {
                id: rectangle2
                width: 40
                height: 20
                color: "#00000000"
            }

            Rectangle {
                id: rectangle
                width: 20
                height: 20
                color: "#ffffff"

                Text {
                    id: text1
                    width: 20
                    height: 20
                    text: qsTr("+")
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.top: parent.top
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Times New Roman"
                    renderType: Text.NativeRendering
                    font.pixelSize: 22
                }

                MouseArea {
                    id: lPlus
                    anchors.fill: parent
                    onClicked:{
                        serialPort.write("lPlus()");
                    }
                }
            }

            Rectangle {
                id: rectangle1
                width: 20
                height: 20
                color: "#ffffff"
                Text {
                    id: text2
                    width: 20
                    height: 20
                    text: qsTr("-")
                    font.bold: true
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 22
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Times New Roman"
                }

                MouseArea {
                    id: lMinus
                    anchors.fill: parent
                    onClicked:{
                        serialPort.write("lMinus()");
                    }
                }
            }

            Rectangle {
                id: rectangle3
                width: 50
                height: 20
                color: "#00000000"
            }

            Rectangle {
                id: rectangle4
                width: 40
                height: 20
                color: "#ffffff"
                Text {
                    id: text3
                    width: 20
                    height: 20
                    text: qsTr("Reset")
                    font.bold: true
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.top: parent.top
                    font.family: "Times New Roman"
                }

                MouseArea {
                    id: reset
                    anchors.fill: parent
                    onClicked:{
                        serialPort.write("reset()");
                    }
                }
            }

            Rectangle {
                id: rectangle7
                width: 40
                height: 20
                color: "#ffffff"
                Text {
                    id: text4
                    width: 20
                    height: 20
                    text: qsTr("End")
                    font.bold: true
                    style: Text.Normal
                    font.capitalization: Font.MixedCase
                    fontSizeMode: Text.VerticalFit
                    anchors.bottom: parent.bottom
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.left: parent.left
                    font.family: "Times New Roman"
                }

                MouseArea {
                    id: end
                    anchors.fill: parent
                    onClicked:{
                        serialPort.write("end()");
                    }
                }
            }

            Rectangle {
                id: rectangle10
                width: 50
                height: 20
                color: "#00000000"
            }

            Rectangle {
                id: rectangle8
                width: 20
                height: 20
                color: "#ffffff"
                Text {
                    id: text5
                    width: 20
                    height: 20
                    text: qsTr("+")
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    font.pixelSize: 22
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.top: parent.top
                    font.family: "Times New Roman"
                }

                MouseArea {
                    id: rPlus
                    anchors.fill: parent
                    onClicked:{
                        serialPort.write("rPlus()");
                    }
                }
            }

            Rectangle {
                id: rectangle9
                width: 20
                height: 20
                color: "#ffffff"
                Text {
                    id: text6
                    width: 20
                    height: 20
                    text: qsTr("-")
                    anchors.bottom: parent.bottom
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    font.pixelSize: 22
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.left: parent.left
                    font.family: "Times New Roman"
                }

                MouseArea {
                    id: rMinus
                    anchors.fill: parent
                    onClicked:{
                        serialPort.write("rMinus()");
                    }
                }
            }

        }


    }
}
