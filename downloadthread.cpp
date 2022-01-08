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
    emit hello();


}

void DownloadThread::replyFinished(QNetworkReply *reply)
{
    qDebug() << reply->readAll();
}


