#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{

}
void Server::initSocket()
{
    udpsocket = new QUdpSocket(this);

    if(udpsocket->bind(QHostAddress(m_ip), m_port))
    {
        connect(udpsocket, &QUdpSocket::readyRead,this, &Server::readPendingDatagrams);
        connect(udpsocket,&QUdpSocket::connected,this,&Server::connected);
        connect(udpsocket,&QUdpSocket::disconnected,this,&Server::disconnected);
        connect(udpsocket,&QUdpSocket::hostFound,this,&Server::hostFound);
        connect(udpsocket,&QUdpSocket::aboutToClose,this,&Server::closed);
        connect(udpsocket,&QUdpSocket::hostFound,this,&Server::onNewConnection);

        qDebug() << "server started...";
        connectToTurnstile();

        std::thread sendThread(&Server::process,this);
        sendThread.detach();
    }
    else
    {
        qDebug() << "Error";
    }
}

void Server::connected()
{
    qDebug() << "connected";
}
void Server::disconnected()
{
    qDebug() << "disconnected";
}

void Server::hostFound()
{
    qDebug() << "hostFound";
}

void Server::closed()
{
    qDebug() << "closed";
}

void Server::sendAutoMessageToClient()
{
    QByteArray Data;
    Data.append("Serverdan gelen mesaj");

    udpsocket->writeDatagram(Data, QHostAddress(m_ip), m_port);
}

void Server::readPendingDatagrams()
{
    while (udpsocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpsocket->receiveDatagram();
        QByteArray replyData = processThePayload(datagram.data());
        //udpsocket->writeDatagram(datagram.makeReply(replyData));
    }
}

void Server::sendMessage(QString message)
{
    QByteArray Data;
    Data.append(message.toUtf8());

    udpsocket->writeDatagram(Data, QHostAddress(m_ip), m_port);
}

void Server::process()
{
    string message;

    cout << "Enter message to client: " << endl;
    while(getline(cin,message))
    {
        sendMessage(QString::fromStdString(message));
    }
}

QByteArray Server::processThePayload(QByteArray data)
{
    qDebug() << "data: " << data;
    return QByteArray("OK!");
}

void Server::onNewConnection()
{
    qDebug() << "onNewConnection";
}
void Server::setPort(quint16 port)
{
    m_port = port;
}
quint16 Server::getPort()
{
    return m_port;
}

void Server::setIp(QString ip)
{
    m_ip = ip;
}
QString Server::getIp()
{
    return m_ip;
}

void Server::connectToTurnstile()
{

    //sendMessage("aa70c305021e7298e73a6a01");
}
