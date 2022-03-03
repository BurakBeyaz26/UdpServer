#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{

}
void Server::initSocket()
{
    //connect(threadTimer,&QTimer::timeout,this,&Server::changeThreadState);

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

//void Server::changeThreadState()
//{
//    threadState = false;
//    threadTimer->stop();
//}

void Server::readPendingDatagrams()
{
    QNetworkDatagram datagram;
    ThreadObject* threadobj;
    while (udpsocket->hasPendingDatagrams()) {
        datagram = udpsocket->receiveDatagram();
        QByteArray replyData = processThePayload(datagram.data());
        //udpsocket->writeDatagram(datagram.makeReply(replyData));
    }

    QString message = "hey! "+datagram.destinationAddress().toString()+":"+QString::number(datagram.senderPort());


    threadobj = findThreadObject(datagram.destinationAddress().toString(),datagram.senderPort());
    if(threadobj == nullptr)
    {
        threadobj = new ThreadObject;
        threadobj->setIp(datagram.destinationAddress().toString());
        threadobj->setPort(datagram.senderPort());
        m_threadObjectVector.push_back(threadobj);

        std::thread abc(&ThreadObject::threadProcess,threadobj,message);
        abc.detach();
    }
    else
    {
        std::thread abc(&ThreadObject::threadProcess,threadobj,message);
        abc.detach();
    }

//    std::thread abc(&Server::threadProcess,this,message);
//    abc.detach();
    //threadTimer->start(10000);

}


ThreadObject* Server::findThreadObject(QString ip,quint64 port)
{
    auto iter = m_threadObjectVector.begin();
    while(iter != m_threadObjectVector.end())
    {
        ThreadObject *obj = *iter;
        if(obj->getIp() == ip && obj->getPort() == port)
        {   obj->setisNew(false);
            obj->setState(true);
            return obj;
        }
        *iter++;
    }

    return nullptr;
}

//void Server::threadProcess(QString message)
//{

//    //udpsocket->writeDatagram(message.toUtf8(), QHostAddress(m_ip), m_port);
//    while(1)
//    {
//        qDebug() << message;
//        std::this_thread::sleep_for(std::chrono::seconds(1));

//        if(threadState == false)
//            return;
//    }
//}

void Server::sendMessage(QString message)
{
    QByteArray Data;
    Data.append(message.toUtf8());

    udpsocket->writeDatagram(Data, QHostAddress(m_ip), m_port);
}

void Server::process()
{
    string message;

    cout << "Enter message: " << endl;
    cin >> message;
    sendMessage(QString::fromStdString(message));
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

