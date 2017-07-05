#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    connect(&chat,SIGNAL(sigNewUser(QString,QString)),
            this,SLOT(onNewUser(QString,QString)));
    connect(&chat,SIGNAL(sigNewContent(QString,QString,bool)),
            this,SLOT(onNewContent(QString,QString,bool)));

    chat.init();

    QVBoxLayout* m = new QVBoxLayout(this);

    QSplitter* splitter = new QSplitter(this);
    m->addWidget(splitter);
    splitter->addWidget(list = new QListWidget);

    QWidget* container;
    splitter->addWidget(container = new QWidget);

    QVBoxLayout* vbox = new QVBoxLayout(container);
    vbox->addWidget(msgshow = new QTextBrowser,3);
    vbox->addWidget(msginput = new QTextEdit,1);

    QHBoxLayout* hbox;
    vbox->addLayout(hbox = new QHBoxLayout);
    //hbox->addStretch(1);
    hbox->addWidget(setup = new QPushButton("设置"));
    hbox->addWidget(send = new QPushButton("发送"));
    hbox->addWidget(sendfile = new QPushButton("发送文件"));

    vbox->setMargin(0);
    hbox->setMargin(0);

    connect(send,SIGNAL(clicked()),this,SLOT(onSend()));
    connect(setup,SIGNAL(clicked()),this,SLOT(onSetup()));
}

void MainWindow::onNewUser(QString name, QString ip)
{
    qDebug()<<"onNewUser"<<name<<ip;
    int count = this->list->count();
    for(int i = 0;i < count; ++i)
    {
        QListWidgetItem* item = list->item(i);
        if(item->text().indexOf(ip) != -1)
        {
            qDebug()<<"remove same user4";
            list->removeItemWidget(item);
            break;
        }
    }
    this->list->addItem(name + "@" + ip);
}

void MainWindow::onNewContent(QString name, QString content)
{
    msgshow->append(name+" say:"+content);
}

void MainWindow::onSend()
{

    //得到ip
    QString text = list->currentItem()->text();
    qDebug() << "item text is:" << text;//name@ip

    QStringList stringList = text.split('@');
    if(stringList.length() != 2)
    {
        qDebug()<<stringList;
        return;
    }
    QString ip = stringList.at(1);
    //内容
    QString content = msginput->toPlainText();
    if(content.length() == 0)
    {
        return;
    }
    chat.sendMsg(content,ip,false);
    //整理界面
    msginput->clear();
    msgshow->append("i say:"+content);
}

void MainWindow::onSetup()
{
    QDialog dlg;
    QComboBox* combo;
    QHBoxLayout* lay = new QHBoxLayout(&dlg);
    lay->addWidget(new QLabel("选择网卡"));
    lay->addWidget(combo = new QComboBox());

    QList<QNetworkAddressEntry> entrys;
    QList<QNetworkInterface> infs = QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface inf,infs)
    {
        entrys.append(inf.addressEntries());
    }
    foreach(QNetworkAddressEntry entry,entrys)
    {
        if(entry.broadcast().toString().isEmpty())
            continue;
        combo->addItem(entry.ip().toString());
        combo->setItemData(combo->count()-1,entry.broadcast().toString());
    }

    dlg.exec();
    //得到当前用户的选择,并赋值给chat对象
    chat.broadcast_ip = combo->itemData(combo->currentIndex()).toString();
    chat.create_socket(combo->currentText());
    //重新发送上线通知
    chat.sendOnline();
}
