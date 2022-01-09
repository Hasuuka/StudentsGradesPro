#include "mainwindow.h"
#include "QDebug"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Main thread started with" << QThread::currentThreadId() << ".";

    MainWindow w;
    w.show();
    return a.exec();
}
