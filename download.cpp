#include "download.h"
#include <QThread>
#include <QEventLoop>
#include <string.h>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include "students.h"
#include <QList>



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
        //QThread::sleep(1);
    }
     qDebug() << "Finished processing Url list.";

    QList <students> studentList;
    for(int i = 0; i < length;i++){
        if(QThread::currentThread()->isInterruptionRequested()){
            qDebug()<<"Canceled.";
                return;
        }
        reply = manager->get(QNetworkRequest(array[i]));

        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        QByteArray list[length];

        list[i] = reply ->readAll();
        QString str = QString::fromLatin1(list[i]);
        string output = str.toStdString();


        for(int i = 0;i <5;i++){
            str.remove(0,str.indexOf(",")+1);
        }
        str.remove(0,2);

        float math, english, progra1, progra2, statistics;
        QString name;
        QVariant buffer;

        while(str.length()){
            name = str.sliced(0,str.indexOf(","));
            str.remove(0,str.indexOf(",")+1);

            buffer= str.sliced(0,str.indexOf(","));
            math = buffer.toFloat();
            str.remove(0,str.indexOf(",")+1);

            buffer= str.sliced(0,str.indexOf(","));
            english = buffer.toFloat();
            str.remove(0,str.indexOf(",")+1);

            buffer= str.sliced(0,str.indexOf(","));
            progra1 = buffer.toFloat();
            str.remove(0,str.indexOf(",")+1);

            buffer= str.sliced(0,str.indexOf(","));
            progra2 = buffer.toFloat();
            str.remove(0,str.indexOf(",")+1);

            if(str.indexOf("\xd")==1){
                buffer= str.sliced(0,1);
                statistics = buffer.toFloat();
                str.remove(0,str.indexOf("\xd")+2);
            }
            else{
                buffer= str.sliced(0,2);
                statistics = buffer.toFloat();
                str.remove(0,str.indexOf("\xd")+2);
            }
            studentList.append(students(name.toStdString(), math, english, progra1, progra2, statistics));

        }

        for(int i = 0 ; i<studentList.size();i++)
        {
            studentList[i].printInfo();
        }
        int index = i +1;
        string fileName = "grades_";
        fileName.append(to_string(index)+".csv");


        emit progressUpdated(1,length*2);
        qDebug()<< "Downloaded"<< i+1 << "of "<< length;
        QThread::sleep(1);
    }

    emit downloadFinished();
    qDebug() << "Thread" << QThread::currentThread() << "finished.";
}



