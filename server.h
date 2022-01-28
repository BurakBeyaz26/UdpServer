#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QString>
#include <QNetworkDatagram>

#include <iostream>
#include <string>
#include <QTimer>

#include <thread>

using namespace std;


class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void initSocket();
    void readPendingDatagrams();
    void sendMessage(QString message);

    void process();

    void setPort(quint16 port);
    quint16 getPort();

    void setIp(QString ip);
    QString getIp();


    void connectToTurnstile();


public slots:
    QByteArray processThePayload(QByteArray data);
    void onNewConnection();
    void connected();
    void disconnected();
    void hostFound();
    void closed();

    void sendAutoMessageToClient();
private:
    QUdpSocket *udpsocket;
    quint16 m_port;
    QString m_ip;
    QTimer *sendTimer = new QTimer();

signals:

};

#endif // SERVER_H
