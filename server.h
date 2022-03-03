#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QString>
#include <QNetworkDatagram>

#include <iostream>
#include <string>
#include <QTimer>

#include <iostream>
#include <thread>
#include <vector>
#include <QTime>
#include <QCoreApplication>
#include <chrono>

#include "threadobject.h"


using namespace std;


class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void initSocket();
    void readPendingDatagrams();
    void sendMessage(QString message);


    //void threadProcess(QString message);

    void process();

    void setPort(quint16 port);
    quint16 getPort();

    void setIp(QString ip);
    QString getIp();


    void Delay(int secs)
    {
        QTime dieTime = QTime::currentTime().addSecs(secs);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    void mDelay(int msecs)
    {
        QTime dieTime = QTime::currentTime().addMSecs(msecs);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }


    ThreadObject* findThreadObject(QString ip, quint64 port);

    QVector<ThreadObject*> m_threadObjectVector;

public slots:
    QByteArray processThePayload(QByteArray data);
    void onNewConnection();
    void connected();
    void disconnected();
    void hostFound();
    void closed();

    void sendAutoMessageToClient();

private slots:
    //void changeThreadState();

private:
    //QTimer *threadTimer = new QTimer();

    QUdpSocket *udpsocket;
    quint16 m_port;
    QString m_ip;
    QTimer *sendTimer = new QTimer();


    bool threadState = true;
signals:

};

#endif // SERVER_H
