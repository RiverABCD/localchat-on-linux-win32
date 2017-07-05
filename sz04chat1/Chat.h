#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>
#include <QDebug>

#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#ifdef WIN32
#include <winsock2.h>
#define socklen_t int
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QNetworkAddressEntry>
#include <QNetworkInterface>
#include <QProcessEnvironment>

#include "chatdef.h"

typedef struct User
{
    QString name;
    QString ip;
}User;

class Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject *parent = 0);
    QMap<QString,User*> others;
    QString name;
    QStringList ips;

    int udp_fd;
    pthread_t tid;
    static void* recv_thread(void* ptr);
    void run();

    void init();
    void handleMsg(const QJsonObject& obj,QString ip);

    QString getSysName();
    QStringList getSysIps();
    void send(const QJsonObject &obj,QString ip);
    void sendMsg(QString content,QString ip,bool broadcast);
    void addUser(QString ip,QString name);
signals:
    void sigNewUser(QString name,QString ip);
    void sigNewContent(QString name,QString content,bool broadcast);
public slots:
};

#endif // CHAT_H
