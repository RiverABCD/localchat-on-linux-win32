#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>
#include <QDebug>
#include <QThread>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QNetworkAddressEntry>
#include <QNetworkInterface>
#include <QProcessEnvironment>

#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#ifdef WIN32
#include <winsock2.h>
#define socklen_t int
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

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
    QString account;
    QStringList ips;


    int udp_fd;
    //thread
    pthread_t tid;
    static void* recv_thread(void* ptr);
    void run();
    void handleMsg(const QJsonObject& obj,QString ip);
    void addUser(QString ip,QString name);

    //initialize
    void init();
    QString getSysName();
    QStringList getSysIps();

    //send data
    void create_socket(QString ip);
    QString broadcast_ip;
    void send(const QJsonObject &obj,QString ip);
    void sendMsg(QString content,QString ip,bool broadcast);
    void sendOnline();

signals:
    void sigNewUser(QString name,QString ip);
    void sigNewContent(QString name,QString content,bool broadcast);
public slots:
};

#endif // CHAT_H
