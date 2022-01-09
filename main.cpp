#include "mainwindow.h"
#include "QDebug"

#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QObject>
#include <string>
#include <iostream>
using namespace std;

#ifndef TEST_H
#define TEST_H
class test : public QObject{
    Q_OBJECT;
public:
    explicit test(QObject *parent = nullptr): QObject(parent){
    }
    ~test(){};

    void startDownload(){
        qDebug() << "Running thread" << QThread::currentThread();
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("http://codingprof.hs-rw.de/files/exercise-files/filelist_http.txt")));

        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        qDebug()<<"Finished getting url.";


        QByteArray data = reply ->readAll();
        QString str = QString::fromLatin1(data);
        int length =str.count(".csv");
        qDebug()<< length;
        QString array[length];
        for(int i = 0; i< length;i++){
            if(QThread::currentThread()->isInterruptionRequested()){
                qDebug()<<"Canceled.";
                    return;
            }
            array[i] =  str.sliced(0, str.indexOf(".csv")+4);
            qDebug()<< array[i];
            str.remove(0,str.indexOf(".csv")+5);
            qDebug()<< "Processed" << i+1 << "of"<< length;
            QThread::sleep(1);
        }
         qDebug() << "Finished processing Url list.";

        for(int i = 0; i < length;i++){
            if(QThread::currentThread()->isInterruptionRequested()){
                qDebug()<<"Canceled.";
                    return;
            }
            QNetworkAccessManager *manager = new QNetworkAccessManager(this);
            QNetworkReply *reply = manager->get(QNetworkRequest(array[i]));

            QEventLoop loop;
            connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();

            QByteArray data = reply ->readAll();
            QString str = QString::fromLatin1(data);
            qDebug() << str;
            qDebug()<< "Downloaded"<< i+1 << "of "<< length;
            QThread::sleep(1);

        }
    }



};
#endif // TEST_H

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Main thread started with" << QThread::currentThreadId() << ".";

    MainWindow w;
    w.show();
    return a.exec();
//    test* test;
//    test->startDownload();
//    delete test;
//    return 0;

}

