#include "downloadthread.h"
#include <QDebug>
#include "shareddata.h"
#include <QNetworkAccessManager>

DownloadThread::DownloadThread(QObject *parent) : QThread(parent)
{


}

void DownloadThread::run()
{
    qDebug() << "Running thread" << QThread::currentThreadId();
    QNetworkAccessManager *manager = new QNetworkAccessManager(nullptr);
    connect(manager, &QNetworkAccessManager::finished, this , [&](QNetworkReply *reply){
        QByteArray data = reply ->readAll();
         QString str = QString::fromLatin1(data);
         qDebug() << str;
    });
    manager->get(QNetworkRequest(QUrl("https://codingprof.hs-rw.de/files/exercise-files/filelist.txt")));



}

void DownloadThread::replyFinished(QNetworkReply *reply)
{
    QByteArray data = reply ->readAll();
     QString str = QString::fromLatin1(data);
     qDebug() << str;
}


