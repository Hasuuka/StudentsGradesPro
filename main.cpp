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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Main thread started with" << QThread::currentThreadId() << ".";
    MainWindow w;
    w.show();
    return a.exec();
}

