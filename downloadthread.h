#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H
#include "QCoreApplication"
#include "qthread.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class DownloadThread : public QThread
{
    Q_OBJECT

public:
    explicit DownloadThread(QObject *parent = nullptr);

    void run();


signals:
    void hello();

public slots:
    void replyFinished(QNetworkReply *reply);




private:



};

#endif // DOWNLOADTHREAD_H
