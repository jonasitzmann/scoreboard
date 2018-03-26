#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include <QByteArray>
#include <QTSerialPort/qserialport.h>
#include <QTextStream>
#include <QTimer>
#include <QQmlEngine>
#include <QRegularExpression>


class SerialPortReader : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void write(QString msg);
    explicit SerialPortReader(QSerialPort *serialPort, QObject *parent = nullptr);
signals:
    int messageRead(int Message);
private slots:
    void handleReadyRead();
    void handleError();

private:
    void processMessage(QString message);
    QSerialPort *m_serialPort = nullptr;
    QByteArray m_readData;
    QObject* m_root;
    QRegularExpression msgFormat;
};

#endif // SERIALPORTREADER_H
