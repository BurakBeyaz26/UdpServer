#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    QString port,ip;

    qDebug() << "UDP SERVER!\nIf you use with argument --> <port> <ip>";

    if(argc>2)
    {
        qDebug() << "with arguments...";

        port = argv[1];
        ip = argv[2];

        server.setPort(port.toInt());
        server.setIp(ip);
        server.initSocket();
    }
    else
    {
        qDebug() << "without argument...";

        server.setPort(7001);
        server.setIp("192.168.0.35");
        server.initSocket();
    }

    return a.exec();
}
