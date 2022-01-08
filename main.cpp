#include "mainwindow.h"
#include "QDebug"
#include "downloadthread.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Main thread started with" << QThread::currentThreadId() << ".";
    DownloadThread* thread1 = new DownloadThread();
    thread1->start();

    qDebug() << "Thread is started. Main program continues.";
    qDebug() << "Waiting for end of thread.";
    thread1->wait(); // Wait for end of thread

    MainWindow w;
    w.show();

    qDebug() << "Done.";

    return a.exec();
}
