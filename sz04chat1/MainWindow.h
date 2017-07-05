#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QTextBrowser>
#include <QTextEdit>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include "Chat.h"


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    QListWidget* list;
    QTextBrowser* msgshow;
    QTextEdit* msginput;
    QPushButton* setup;
    QPushButton* send;
    QPushButton* sendfile;

    Chat chat;
signals:

public slots:
    void onNewUser(QString name,QString ip);
    void onNewContent(QString name,QString content);
    void onSend();
};

#endif // MAINWINDOW_H
