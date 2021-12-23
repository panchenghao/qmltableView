import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")

    CellView{
        anchors.fill: parent
//        leftMargin: 1
//        topMargin: 1
//        rightMargin: 1
//        bottomMargin: 1
    }
    Button{
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 20
        height: 20
        onClicked: {
            Tabmodel.selectData();
        }
    }
}
