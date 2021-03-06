#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

class Download : public QObject
{
    Q_OBJECT
public:
    explicit Download(QObject *parent = nullptr);
    Q_INVOKABLE void startCalculation(QString url);

signals:
    void downloadFinished();
    void progressUpdated(int, int);
};

#endif // DOWNLOAD_H
