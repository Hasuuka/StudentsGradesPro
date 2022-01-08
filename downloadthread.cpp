#include "downloadthread.h"
#include <QDebug>
#include "shareddata.h"

DownloadThread::DownloadThread(QObject *parent) : QThread(parent)
{

}

void DownloadThread::run()
{
    qDebug() << "Running thread" << QThread::currentThreadId();
    //SharedData::instance()->addCsv("Dicke Eier", "69PB", "70", "Donald Duck");

    QThread::msleep(1000);
}
