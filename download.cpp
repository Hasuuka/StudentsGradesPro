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

    qDebug()<<"Finished getting url.";


    QByteArray data = reply ->readAll();
    QString str = QString::fromLatin1(data);
    int length =str.count(".csv");
    QString array[length];
    for(int i = 0; i< length;i++){
        if(QThread::currentThread()->isInterruptionRequested()){
            qDebug()<<"Canceled.";
                return;
        }
        array[i] =  str.sliced(0, str.indexOf(".csv")+4);
        str.remove(0,str.indexOf(".csv")+5);
        qDebug()<< "Processed" << i+1 << "of"<< length;
        emit progressUpdated(1,length);
        QThread::sleep(1);
    }
     qDebug() << "Finished processing Url list.";

    for(int i = 0; i < length;i++){
        if(QThread::currentThread()->isInterruptionRequested()){
            qDebug()<<"Canceled.";
                return;
        }
        reply = manager->get(QNetworkRequest(array[i]));

        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        QByteArray data = reply ->readAll();
        QString str = QString::fromLatin1(data);
        qDebug()<< str;
        emit progressUpdated(1,length*2);
        qDebug()<< "Downloaded"<< i+1 << "of "<< length;
        QThread::sleep(1);
    }
    emit downloadFinished();
    qDebug() << "Thread" << QThread::currentThread() << "finished.";
}



