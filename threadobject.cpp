#include "threadobject.h"

ThreadObject::ThreadObject(QObject *parent) : QObject(parent)
{
    setIsActive(false);
    setState(true);
    setisNew(true);
}

void ThreadObject::threadProcess(QString message)
{
    qDebug() << "process starting...";
    startUp();
    while(1)
    {
        counter++;
        qDebug() << QString::number(counter) << ": " << message << " isnew: " << getisNew();
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if(getState() == false)
            return;
    }
}

void ThreadObject::startUp()
{
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,[=](){setState(false);timer->stop();});
    timer->start(20000);
}

void ThreadObject::setIp(QString ip)
{
    m_ip = ip;
}
QString ThreadObject::getIp()
{
    return m_ip;
}

void ThreadObject::setPort(quint64 port)
{
    m_port = port;
}
quint64 ThreadObject::getPort()
{
    return m_port;
}

void ThreadObject::setisNew(bool isnew)
{
    m_isNew = isnew;
}
bool ThreadObject::getisNew()
{
    return m_isNew;
}

void ThreadObject::setState(bool state)
{
    m_state = state;
}
bool ThreadObject::getState()
{
    return m_state;
}

void ThreadObject::setIsActive(bool isactive)
{
    m_isActive = isactive;
}
bool ThreadObject::getIsActive()
{
    return m_isActive;
}
