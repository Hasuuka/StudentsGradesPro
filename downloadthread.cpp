#include "downloadthread.h"

DownloadThread::DownloadThread(QObject *parent) : QThread(parent)
{

}

void DownloadThread::run()
{
    qDebug() << "Running thread" << QThread::currentThreadId();
    for(int i = 0; i < 10; i++)
    {
        qDebug() << " Progress of " << QThread::currentThreadId() << " is "
                 << (i+1) << "/" << 10;
        long l = 0;
        for(int j = 0; j < 100000; j++)
        {
            for(int k = 0; k < 1000; k++)
            {
                    l += j*k;
            }
        }
    }
    qDebug() << "Thread" << QThread::currentThreadId() << "finished.";
}
