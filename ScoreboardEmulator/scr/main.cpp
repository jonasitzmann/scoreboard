#include <QGuiApplication>
#include <QtCore>
#include <iostream>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QTSerialPort/qserialport.h>
#include <QStringList>
#include <QTextStream>
#include <QQmlContext>
#include "serialportrrader.h"
//#include "errorhandler.h"

int main(int argc, char *argv[]){
  //  qInstallMessageHandler(ErrorHandler);
    QGuiApplication app(argc,argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    QObject* root = engine.rootObjects()[0];
    QQmlContext *context = engine.rootContext();

    QSerialPort serialPort;
    serialPort.setPortName("COM9");
    serialPort.setBaudRate(115200);

    if (!serialPort.open(QIODevice::ReadWrite)) {
        qDebug() << ("Failed to open");
        return 1;
    }

    SerialPortReader serialPortReader(&serialPort, root);
    context->setContextProperty("serialPort", &serialPortReader);


    return app.exec();
} // end main
