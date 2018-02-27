#include "serialportrrader.h"
#include <QDebug>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QStringlist>
SerialPortReader::SerialPortReader(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort)
{
    msgFormat = QRegularExpression(
           "setPixel:\\s+(?<index>\\d+)\\s+(?<red>\\d+)\\s+(?<green>\\d+)\\s+(?<blue>\\d+)");
    m_root = parent;
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);
   // connect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortReader::handleError);
}

void SerialPortReader::handleReadyRead()
{
    auto newData = m_serialPort->read(50); // read not more than 50 bytes
    m_readData.append(newData);
    QString last60Bytes = m_readData.mid(m_readData.size()-59, 60);
    if(last60Bytes.contains("show")){
        QString fullMsg(m_readData);
        QStringList splitted = fullMsg.split("show");
        processMessage(splitted[0]); // process everython before "show"
        m_readData.clear();
        m_readData.append(splitted[1]);// save everything after "show"
    }
}

void SerialPortReader::handleError()
{
    qWarning() << m_serialPort->errorString();
}

void SerialPortReader::processMessage(QString message)
{
    auto lines = message.split("\n");
    for(auto it  = lines.begin(); it != lines.end(); ++it) {
        QString line = *it;
        auto match = msgFormat.match(line);
        if(!match.hasMatch()){
            continue;
        }
        int index = match.captured("index").toInt();
        int red = match.captured("red").toInt();
        int green = match.captured("green").toInt();
        int blue = match.captured("blue").toInt();
        if(index < 0 || index >= 70){
            continue;
        }
        QMetaObject::invokeMethod(m_root, "setPixel",
                                      Q_ARG(QVariant, index),
                                      Q_ARG(QVariant, red),
                                      Q_ARG(QVariant, green),
                                      Q_ARG(QVariant, blue)
                                      );
    }
}
