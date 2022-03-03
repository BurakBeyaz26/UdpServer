#ifndef THREADOBJECT_H
#define THREADOBJECT_H

#include <QObject>
#include <iostream>
#include <string>
#include <QTimer>

#include <iostream>
#include <thread>

#include <QTime>
#include <QCoreApplication>
#include <chrono>
#include <QDebug>


using namespace std;

class ThreadObject : public QObject
{
    Q_OBJECT
public:
    explicit ThreadObject(QObject *parent = nullptr);

    void threadProcess(QString message);
    void startUp();

    void setIsActive(bool isactive);
    bool getIsActive();

    void setState(bool state);
    bool getState();

    void setisNew(bool isnew);
    bool getisNew();

    void setIp(QString ip);
    QString getIp();

    void setPort(quint64 port);
    quint64 getPort();


    int counter = 0;

private:

    QTimer *timer;

    bool m_isActive;
    bool m_state;
    bool m_isNew;
    QString m_ip;
    quint64 m_port;


signals:

};

#endif // THREADOBJECT_H
