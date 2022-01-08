#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H
#include "QCoreApplication"
#include "qthread.h"

class DownloadThread : public QThread
{
public:
    explicit DownloadThread(QObject *parent = nullptr);

    void run();
};

#endif // DOWNLOADTHREAD_H
