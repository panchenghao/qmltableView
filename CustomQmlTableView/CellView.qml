import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import Qt.labs.qmlmodels 1.0
import App.Class 0.1 as Class
Flickable {
    id:root
    property int defauleHeight: 50
    implicitHeight: 500
    implicitWidth: 800
    interactive: true
    contentWidth: table.contentWidth+5
    contentHeight: re.height+topre.height+4
    Rectangle{
        id:topre
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 4  //是他的contentItem 所以这里跟他的content边界锚定！！！！
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.leftMargin: 4
        height: 30
        color: "#bfbfbf"
        Flickable{
            id:headflick
            //height: 30
            anchors.fill: parent
//            anchors.leftMargin: 1
//            anchors.rightMargin: 1
//            topMargin: 1
            leftMargin: 1
            topMargin: 2
            rightMargin: 1
            bottomMargin: 1
            interactive: false
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            //contentX: table.contentX
            //contentWidth: header.width
            ResizableColumnHeader{
                id:header
                anchors.fill: parent
                defaultWidth: 150
                spacing: 1
                model: Tabmodel.headRoles
                interactive: false
                onColumnWidthChanged: {
                    if(width<=root.width) root.contentX=0;
                    table.forceLayout()
                }
            }
        }
    }


    Rectangle{
        id:re
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.top: topre.bottom
        anchors.bottomMargin: 2
        anchors.leftMargin: 4
        //anchors.topMargin: 1
        height: Tabmodel.rows*(defauleHeight+1)
//            let maxheight=root.height-headflick.height-1-2;
//            if(Tabmodel.rowCount()*(defauleHeight+1)>root.height-headflick.height-1-2){
//                return maxheight
//            }else{
//                return Tabmodel.rowCount()*(defauleHeight+1)
//            }

//        }
        color: "#bfbfbf"
        TableView{
            id:table
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 1
            anchors.rightMargin: 1
            anchors.bottomMargin: 2
            clip: true
            columnWidthProvider: header.columnWidthProvider
            rowHeightProvider: function(columns){return defauleHeight}
            model:Tabmodel
            interactive: false
            rowSpacing:1
            columnSpacing:1

            //每个cellEditor角色就是item的editortype  在rolevalue取到哪个editortype就显示哪个角色
            delegate: DelegateChooser{
                role: "cellType"
                DelegateChoice{
                    roleValue: Class.WheatItem.TextEditor
                    Rectangle{
                        Text {
                            elide: Text.ElideRight
                            text: model.cellData
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                        }
                        color: "#ffffff"
                    }
                }
                DelegateChoice{
                    roleValue: Class.WheatItem.CheckboxEditor
                    Rectangle {
                        Image {
                            source: model.cellData==="true"?"qrc:/selected.png":"qrc:/unselected.png"
                            anchors.centerIn: parent
                            width: sourceSize.width
                            height: sourceSize.height
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    if(model.cellData==="true"){
                                        model.cellData="false"
                                    }else{
                                        model.cellData="true"
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }


    ScrollBar.horizontal:   ScrollBar {
        orientation: Qt.Horizontal
        //policy:ScrollBar.AlwaysOn
    }
    ScrollBar.vertical:     ScrollBar {
        onPositionChanged: {
            if(size+position>=0.99){
                Tabmodel.updateData();
            }
        }
    }

    //    }
//    Connections{
//        target: Tabmodel
//        function onRowsChanged(){
//            re.height=Tabmodel.rowCount()*(defauleHeight+1)
//        }
//    }
}
