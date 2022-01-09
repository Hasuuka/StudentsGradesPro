#include "download.h"
#include <QThread>

Download::Download(QObject *parent) : QObject(parent)
{

}

void Download::startCalculation()
{
    qDebug() << "Running thread" << QThread::currentThread();
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this , [&](QNetworkReply *reply){
        QByteArray data = reply ->readAll();
         QString str = QString::fromLatin1(data);
         qDebug() << str;
         qDebug() << "Thread" << QThread::currentThread() << "finished";

    });
    manager->get(QNetworkRequest(QUrl("https://codingprof.hs-rw.de/files/exercise-files/filelist.txt")));
}


