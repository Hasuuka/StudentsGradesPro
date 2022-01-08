#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shareddata.h"
#include "QDebug"
#include "downloadthread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SharedData::instance()->addCsv("Dicke Eier", "69PB", "70", "Donald Duck");
    m_csvListModel = new CsvListModel(SharedData::instance()->csvs(), this);
    ui->csvList->setModel(m_csvListModel);

}

void MainWindow::enableCalculateButton(){
    ui->calculateButton->setDisabled(false);
}

void MainWindow::disableCalculateButton(){
    ui->calculateButton->setDisabled(true);
}

void MainWindow::enableCancleButton(){
    ui->cancelButton->setDisabled(true);
}

void MainWindow::disableCancleButton(){
    ui->cancelButton->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_downloadButton_clicked()
{
    DownloadThread* downloadthread = new DownloadThread();
    downloadthread->start();

    qDebug() << "Thread: " << downloadthread->currentThread() << " started.";
    downloadthread->wait(); // Wait for end of thread

    qDebug() << "thread: " << downloadthread->currentThread() << " is finished";
    downloadthread->quit();
    m_csvListModel = new CsvListModel(SharedData::instance()->csvs(), this);
    ui->csvList->setModel(m_csvListModel);
    delete downloadthread;
}

