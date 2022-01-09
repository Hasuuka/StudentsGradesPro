#include "download.h"
#include <QThread>
#include <QEventLoop>
#include <string.h>
#include <iostream>
 using namespace std;

Download::Download(QObject *parent) : QObject(parent)
{

}

void Download::startCalculation()
{
    qDebug() << "Running thread" << QThread::currentThread();
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://codingprof.hs-rw.de/files/exercise-files/filelist.txt")));

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    emit progressUpdated(1,1);
    qDebug()<<"Finished getting url.";
    QThread::sleep(1);

    QByteArray data = reply ->readAll();
    QString str = QString::fromLatin1(data);

    int size = str.count(".csv");
    emit progressUpdated(1,size+1);

    string buffer = str.toStdString();
    string urlArray[size];
    for(int i = 0;i<size;i++ ){
        if(QThread::currentThread()->isInterruptionRequested()){
            qDebug()<<"Canceled.";
                return;
        }
        urlArray[i] = buffer.substr(0,buffer.find(".csv")+4);
        buffer.erase(0,buffer.find(".csv")+4);

        qDebug()<< "Processed" << i+1 << "of"<< size;
        emit progressUpdated(1,size+2);
        QThread::sleep(1);
    }

    qDebug() << "Finished processing Url list.";

    for(unsigned int i = 0; i< sizeof(urlArray)/sizeof(urlArray[0]);i++){
        if(QThread::currentThread()->isInterruptionRequested()){
            qDebug()<<"Canceled.";
                return;
        }
        reply = manager->get(QNetworkRequest(QUrl(QString::fromStdString(urlArray[i]))));
        data = reply ->readAll();
        str = QString::fromLatin1(data);
        qDebug() << str;

        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        emit progressUpdated(1,size+size+2);
        qDebug()<< "Downloaded"<< i+1 << "of "<< sizeof(urlArray)/sizeof(urlArray[0]);
        QThread::sleep(1);
    }
    emit downloadFinished();
    qDebug() << "Thread" << QThread::currentThread() << "finished.";
}



