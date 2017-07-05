#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QTextBrowser>
#include <QTextEdit>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QVariant>

#include "Chat.h"


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    void initUserList();
    Chat chat;

    QListWidget* list;
    QTextBrowser* msgshow;
    QTextEdit* msginput;
    QPushButton* setup;
    QPushButton* send;
    QPushButton* sendfile;

    QString getSelectIp();

signals:

public slots:
    void onSend();
    void onSetup();
    void onNewUser(QString name,QString ip);
    void onNewContent(QString name,QString content,bool broadcast);

};

#endif // MAINWINDOW_H
