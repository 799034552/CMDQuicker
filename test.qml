import QtQuick 2.15

Rectangle {
    width: 30
    height: 30
    color: "red"
//    Rectangle {
//        x:0
//        y:0
//        width: 20
//        height: 20
//        color: "blue"
//    }
    Rectangle {
        x:0
        y:0
        width: 20
        height: 20
        color: "blue"
        Image {
    //        x:0
    //        y:0
            width: 20
            height: 20
            visible: true
    //        color: "blue"
            source: "https://pics5.baidu.com/feed/a8014c086e061d9592acc071b97c0eda63d9ca21.jpeg@f_auto?token=f4cbb040cee16a3557eee07d5b02a016"
        }
    }
//    Image {
////        x:0
////        y:0
//        width: 20
//        height: 20
//        visible: true
////        color: "blue"
//        source: "https://pics5.baidu.com/feed/a8014c086e061d9592acc071b97c0eda63d9ca21.jpeg@f_auto?token=f4cbb040cee16a3557eee07d5b02a016"
//    }
}
