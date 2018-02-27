import QtQuick 2.8
import QtQuick.Window 2.2

Window {
    visible: true
    width: 210
    height: 150
    color: "#000000"
    title: qsTr("Scoreboard Emulator")
    property var pixels: [r00, r01, r02, r03, r04, r05, r06, r07, r08, r09, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31, r32, r33, r34, r35, r36, r37, r38, r39, r40, r41, r42, r43, r44, r45, r46, r47, r48, r49, r50, r51, r52, r53, r54, r55, r56, r57, r58, r59, r60, r61, r62, r63, r64, r65, r66, r67, r68, r69]

    function componentToHex(c) {
        var hex = c.toString(16);
        return hex.length == 1 ? "0" + hex : hex;
    }
    function rgbToHex(r, g, b) {
        return "#" + componentToHex(r) + componentToHex(g) + componentToHex(b)
    }
    function setPixel(index, r, g, b) {
        if (index < 0 || index >= 70) {
            return;
        }
        pixels[index].color = rgbToHex(r, g, b)
    }

    Grid {
        id: grid1
        x: 10
        y: 10
        width: 190
        height: 130
        rows: 2
        columns: 2
        spacing: 50

        Grid {
            id: grid
            x: 0
            y: 0
            width: 70
            height: 130
            columns: 3
            rows: 10
            Rectangle {
                id: rectangle5
                width: 10
                height: 10
                color: "#000000"
            }

            Row {
                id: row
                width: 50
                height: 10
                Rectangle {
                    id: r25
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r26
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r27
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r28
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r29
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle6
                width: 10
                height: 10
                color: "#000000"
            }

            Column {
                id: column
                width: 10
                height: 50
                Rectangle {
                    id: r24
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r23
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r22
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r21
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r20
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle12
                width: 50
                height: 50
                color: "#000000"
            }

            Column {
                id: column1
                width: 10
                height: 50
                Rectangle {
                    id: r30
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r31
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r32
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r33
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r34
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle18
                width: 10
                height: 10
                color: "#000000"
            }

            Row {
                id: row1
                width: 50
                height: 10
                Rectangle {
                    id: r19
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r18
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r17
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r16
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r15
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle24
                width: 10
                height: 10
                color: "#000000"
            }

            Column {
                id: column2
                width: 10
                height: 50
                Rectangle {
                    id: r00
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r01
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r02
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r03
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r04
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle30
                width: 50
                height: 50
                color: "#000000"
            }

            Column {
                id: column3
                width: 10
                height: 50
                Rectangle {
                    id: r14
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r13
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r12
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r11
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r10
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle36
                width: 10
                height: 10
                color: "#000000"
            }

            Row {
                id: row2
                width: 50
                height: 10
                Rectangle {
                    id: r05
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r06
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r07
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r08
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r09
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle42
                width: 10
                height: 10
                color: "#000000"
            }
        }

        Grid {
            id: grid2
            x: 0
            y: 0
            width: 70
            height: 130
            columns: 3
            rows: 10
            Rectangle {
                id: rectangle43
                width: 10
                height: 10
                color: "#000000"
            }

            Row {
                id: row3
                width: 50
                height: 10
                Rectangle {
                    id: r60
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r61
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r62
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r63
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r64
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle49
                width: 10
                height: 10
                color: "#000000"
            }

            Column {
                id: column4
                width: 10
                height: 50
                Rectangle {
                    id: r59
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r58
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r57
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r56
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r55
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle55
                width: 50
                height: 50
                color: "#000000"
            }

            Column {
                id: column5
                width: 10
                height: 50
                Rectangle {
                    id: r65
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r66
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r67
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r68
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r69
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle61
                width: 10
                height: 10
                color: "#000000"
            }

            Row {
                id: row4
                width: 50
                height: 10
                Rectangle {
                    id: r54
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r53
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r52
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r51
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r50
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle67
                width: 10
                height: 10
                color: "#000000"
            }

            Column {
                id: column6
                width: 10
                height: 50
                Rectangle {
                    id: r35
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r36
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r37
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r38
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r39
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle73
                width: 50
                height: 50
                color: "#000000"
            }

            Column {
                id: column7
                width: 10
                height: 50
                Rectangle {
                    id: r49
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r48
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r47
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r46
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r45
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle79
                width: 10
                height: 10
                color: "#000000"
            }

            Row {
                id: row5
                width: 50
                height: 10
                Rectangle {
                    id: r40
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r41
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r42
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r43
                    width: 10
                    height: 10
                    color: "#333333"
                }

                Rectangle {
                    id: r44
                    width: 10
                    height: 10
                    color: "#333333"
                }
            }

            Rectangle {
                id: rectangle85
                width: 10
                height: 10
                color: "#000000"
            }
        }
    }
}
