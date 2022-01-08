#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "csvlistmodel.h"
#include "downloadthread.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void informUrl(QString);
    void informButton();

public slots:

    void on_downloadButton_clicked();

    void on_calculateButton_clicked();

    void changeUrl(QString);

    void changeButton();



private slots:
    void on_cancelButton_clicked();
    void doSomething();

private:
    Ui::MainWindow *ui;
    CsvListModel* m_csvListModel;
    QString m_url;

    DownloadThread *m_thread;

};
#endif // MAINWINDOW_H
